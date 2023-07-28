/*!
 * @file console.c
 *
 * @brief This file contains the implementation for the console. It
 *          is responsible for gathering user input and passing
 *          commands of to respective modules.
 */

#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "console.h"

/***   key macros   ***/

#define KEY_CTRL(k) ((k) & 0x1F)
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_BACKSPACE 127

/***   static function declarations   ***/

static void banner();

static int
console_initialize (console_t * p_console);

static int
console_finalize (console_t * p_console);

static int
get_cmd (console_t * p_console, char * p_cmd);

/***   public functions   ***/

/*!
 * @brief This function creates a new console context.
 *
 * @param[in] history_max The maximum number of commands to remember.
 * 
 * @return Pointer to new console context. NULL on error.
 */
console_t *
console_create (const size_t history_max)
{
    int status = -1;
    console_t * p_console = calloc(1, sizeof(console_t));
    if (NULL == p_console)
    {
        goto EXIT;
    }
    p_console->p_history = NULL;
    p_console->p_parser = NULL;

    // Create the history queue.
    p_console->p_history = history_create(history_max);
    if (NULL == p_console->p_history)
    {
        goto EXIT;
    }

    // Create the parsed command context.
    p_console->p_parser = parser_create();
    if (NULL == p_console->p_parser)
    {
        goto EXIT;
    }

    // Initialize the termios configurations.
    if (-1 == console_initialize(p_console))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if ((-1 == status) &&
            (NULL != p_console))
        {
            console_destroy(p_console);
            p_console = NULL;
        }
        return p_console;
}

/*!
 * @brief This function destroys a console context.
 *
 * @param[in] p_console The console context.
 * 
 * @return 0 on success, -1 on error.
 */
int
console_destroy (console_t * p_console)
{
    int status = -1;
    if (NULL == p_console)
    {
        goto EXIT;
    }

    // Destroy the command history queue.
    if ((NULL != p_console->p_history) &&
        (-1 == history_destroy(p_console->p_history)))
    {
        goto EXIT;
    }
    p_console->p_history = NULL;

    // Destroy the parsed command context.
    if ((NULL != p_console->p_parser) &&
        (-1 == parser_destroy(p_console->p_parser)))
    {
        goto EXIT;
    }
    p_console->p_parser = NULL;

    status = 0;

    EXIT:
        if (NULL != p_console)
        {
            console_finalize(p_console);
        }
        if (NULL != p_console)
        {
            free(p_console);
            p_console = NULL;
        }
        return status;
}

/*!
 * @brief This function runs a console context.
 *
 * @param[in] p_console The console context.
 * 
 * @return No return value expected.
 */
void
console_run (console_t * p_console)
{
    if (NULL == p_console)
    {
        goto EXIT;
    }

    banner();
    printf("\r\n");

    char cmd_buff[MAX_CMD_SIZE];
    for (;;)
    {
        memset(cmd_buff, '\0', MAX_CMD_SIZE);
        printf("> ");
        fflush(stdout);
        if (0 != get_cmd(p_console, cmd_buff))
        {
            printf("\r\n");
            fflush(stdout);
            break;
        }
        printf("\r\n");

        // Add the command to the console history.
        history_push(p_console->p_history, cmd_buff);

        // Display the command buffered.
        // printf("%s\r\n", cmd_buff);

        // Parse the command.
        if (-1 == parser_parse(p_console->p_parser, cmd_buff))
        {
            goto EXIT;
        }
        
        // Handle the command.

        // Clear the command.
        if (-1 == parser_clear(p_console->p_parser))
        {
            goto EXIT;
        }
    }

    EXIT:
        return;
}

/***   static functions   ***/

/*!
 * @brief This is a helper function to display the welcome banner.
 *
 * @return No return value expected.
 */
static void
banner()
{
    printf("\
      __        __   _      __        __\r\n\
      \\ \\      / /__| |__   \\ \\      / /_ _ ___ _ __ \r\n\
       \\ \\ /\\ / / _ \\ '_ \\   \\ \\ /\\ / / _` / __| '_ \\ \r\n\
        \\ V  V /  __/ |_) |   \\ V  V / (_| \\__ \\ |_) |   \r\n\
         \\_/\\_/ \\___|_.__/     \\_/\\_/ \\__,_|___/ .__/ \r\n\
            Get Stinging                        |_|    \r\n\
                            Author: Mike Rosinsky\r\n\r\n");
}

/*!
 * @brief This function initializes the console context, mainly taking
 *          the form of termios console configurations.
 * 
 * @param[in] p_console The console context.
 * 
 * @return 0 on success, -1 on error.
 */
static int
console_initialize (console_t * p_console)
{
    int status = -1;
    if (NULL == p_console)
    {
        goto EXIT;
    }

    // Save the current console configuration.
    if ((-1 == tcgetattr(STDIN_FILENO, &(p_console->old_console))) ||
        (-1 == tcgetattr(STDIN_FILENO, &(p_console->new_console))))
    {
        goto EXIT;
    }

    // Configure local flags.
    p_console->new_console.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    // Configure input flags.
    p_console->new_console.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // Configure output flags.
    p_console->new_console.c_oflag &= ~(OPOST);

    // Configure character size.
    p_console->new_console.c_cflag |= (CS8);

    // Set control characters.
    // p_console->new_console.c_cc[VMIN] = 0;
    // p_console->new_console.c_cc[VTIME] = 1;

    // Apply new settings to the terminal.
    if (-1 == tcsetattr(STDIN_FILENO, TCSAFLUSH, &(p_console->new_console)))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function finalizes the console context, restoring previous
 *          termios console configurations.
 * 
 * @param[in] p_console The console context.
 * 
 * @return 0 on success, -1 on error.
 */
static int
console_finalize (console_t * p_console)
{
    int status = -1;
    if (NULL == p_console)
    {
        goto EXIT;
    }

    // Restore the terminal to original settings.
    if (-1 == tcsetattr(STDIN_FILENO, TCSAFLUSH, &(p_console->old_console)))
    {
        goto EXIT;
    }
    
    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function collects user input for commands.
 *
 * @param[in] p_cmd The buffer to store the command.
 * 
 * @return 0 on success, -1 on error, 1 on exit.
 */
static int
get_cmd (console_t * p_console, char * p_cmd)
{
    int status = -1;
    if ((NULL == p_console) ||
        (NULL == p_cmd))
    {
        goto EXIT;
    }

    char c, e1, e2;
    memset(p_cmd, '\0', MAX_CMD_SIZE);

    // String to hold the current command if the user begins scrolling
    // through historical commands.
    char p_backup[MAX_CMD_SIZE];
    memset(p_backup, '\0', MAX_CMD_SIZE);

    size_t cmd_idx = 0; // The current position in the string.
    size_t cmd_len = 0; // The length of the string.
    long hist_idx = -1; // The history idx. (-1 is the current command).
    for (;;)
    {
        c = '\0';
        if (-1 == read(STDIN_FILENO, &c, 1))
        {
            goto EXIT;
        }

        // printf("%d", c);
        switch (c)
        {
            case KEY_CTRL('c'):
                printf("^C");
                status = 1;
                goto EXIT;
            break;
            case KEY_ENTER:
                status = 0;
                goto EXIT;
            break;
            case KEY_ESCAPE:
                if ((-1 == read(STDIN_FILENO, &e1, 1)) ||
                    (-1 == read(STDIN_FILENO, &e2, 1)))
                {
                    goto EXIT;
                }
                if (91 == e1)
                {
                    switch (e2)
                    {
                        // Up arrow.
                        case 65:
                            if ((size_t) (hist_idx + 1) >= p_console->p_history->size) { break; }
                            hist_idx++;

                            // Backup the current command if this is the first
                            // up arrow press.
                            if (0 == hist_idx)
                            {
                                strncpy(p_backup, p_cmd, MAX_CMD_SIZE-1);
                            }

                            // Set the current command to the historical command.
                            memset(p_cmd, '\0', MAX_CMD_SIZE);
                            strcpy(p_cmd, p_console->p_history->pp_data[hist_idx]);
                            
                            // Return cursor to start of line.
                            for (size_t i = 0; i < cmd_idx; ++i)
                            {
                                printf("\b");
                            }
                            // Blank the line.
                            for (size_t i = 0; i < cmd_len; ++i)
                            {
                                printf(" ");
                            }
                            // Return cursor to start of line.
                            for (size_t i = 0; i < cmd_len; ++i)
                            {
                                printf("\b");
                            }
                            // Print the command.
                            printf("%s", p_cmd);
                            fflush(stdout);

                            // Set variables.
                            cmd_len = strlen(p_cmd);
                            cmd_idx = cmd_len;
                        break;
                        // Down arrow.
                        case 66:
                            if (-1 == hist_idx) { break; }
                            hist_idx--;

                            // If we have returned to our backup command.
                            if (-1 == hist_idx)
                            {
                                strncpy(p_cmd, p_backup, MAX_CMD_SIZE-1);
                            }
                            else
                            {
                                // Set the current command to the historical
                                // command.
                                memset(p_cmd, '\0', MAX_CMD_SIZE);
                                strcpy(p_cmd, p_console->p_history->pp_data[hist_idx]);
                            }

                            // Return cursor to start of line.
                            for (size_t i = 0; i < cmd_idx; ++i)
                            {
                                printf("\b");
                            }
                            // Blank the line.
                            for (size_t i = 0; i < cmd_len; ++i)
                            {
                                printf(" ");
                            }
                            // Return cursor to start of line.
                            for (size_t i = 0; i < cmd_len; ++i)
                            {
                                printf("\b");
                            }
                            // Print the command.
                            printf("%s", p_cmd);
                            fflush(stdout);

                            // Set variables.
                            cmd_len = strlen(p_cmd);
                            cmd_idx = cmd_len;
                        break;
                        // Right arrow.
                        case 67:
                            if (cmd_idx >= cmd_len) { break; }
                            printf("%c", p_cmd[cmd_idx]);
                            fflush(stdout);
                            cmd_idx++;
                        break;
                        // Left arrow.
                        case 68:
                            if (cmd_idx == 0) { break; }
                            printf("\b");
                            cmd_idx--;
                        break;
                    }
                    fflush(stdout);
                }
            break;
            case KEY_BACKSPACE:
                if (0 == cmd_idx) { break; }

                // Move the cursor back.
                printf("\b");

                // Shift the characters in front of the cursor forward one.
                for (size_t i = cmd_idx; i < cmd_len; ++i)
                {
                    p_cmd[i - 1] = p_cmd[i];
                    printf("%c", p_cmd[i]);
                }

                // Clear the last character.
                printf(" ");

                // Return cursor to original position.
                for (size_t i = cmd_idx; i < cmd_len; ++i)
                {
                    printf("\b");
                }
                printf("\b");

                // Print and update variables.
                fflush(stdout);
                p_cmd[cmd_len-1] = '\0';
                cmd_idx--;
                cmd_len--;
            break;
            default:
                if (cmd_len >= MAX_CMD_SIZE) { break; }

                // Print the character.
                printf("%c", c);

                // Shift all characters in buffer back one.
                for (size_t i = cmd_len; i > cmd_idx; --i)
                {
                    p_cmd[i] = p_cmd[i-1];
                }

                // Update buffer and variables.
                p_cmd[cmd_idx] = c;
                cmd_len++;
                cmd_idx++;

                // Print the following characters in the buffer.
                for (size_t i = cmd_idx; i < cmd_len; ++i)
                {
                    printf("%c", p_cmd[i]);
                }

                // Return cursor to starting position.
                for (size_t i = cmd_idx; i < cmd_len; ++i)
                {
                    printf("\b");
                }
                fflush(stdout);
            break;
        }
    }

    EXIT:
        return status;
}

/***   end of file   ***/