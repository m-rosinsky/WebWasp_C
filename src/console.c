/*!
 * @file console.c
 *
 * @brief This file contains the implementation for the console. It
 *          is responsible for gathering user input and passing
 *          commands of to respective modules.
 */

#include <signal.h>
#include <stdio.h>
#include <string.h>

#include "../include/console.h"

/*!
 * @brief This is a helper function to handle signals.
 *
 * @param[in] sig The number for the signal caught.
 *
 * @return No return value expected.
 */
static void
sigint_handler (int sig)
{
    printf("\nReceived signal %d: (%s)...\n", sig, strsignal(sig));
    return;
}

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
    p_console->history_max = history_max;
    p_console->p_history = NULL;

    // Create the history queue.
    p_console->p_history = queue_create();
    if (NULL == p_console->p_history)
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
        (-1 == queue_destroy(p_console->p_history)))
    {
        goto EXIT;
    }
    p_console->p_history = NULL;

    status = 0;

    EXIT:
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

    // Create the signal handler to catch sigints.
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (-1 == sigaction(SIGINT, &sa, NULL))
    {
        printf("ERROR: Failed to create signal handler...\n");
        goto EXIT;
    }

    // User input loop.
    char cmd_buff[MAX_CMD_SIZE];
    for (;;)
    {
        memset(cmd_buff, '\0', MAX_CMD_SIZE);

        printf("> ");
        if (NULL == fgets(cmd_buff, MAX_CMD_SIZE, stdin))
        {
            break;
        }

        printf("%s", cmd_buff);

        // Add command to history.
    }

    EXIT:
        return;
}

/***   end of file   ***/