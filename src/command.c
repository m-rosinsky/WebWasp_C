/*!
 * @file command.c
 *
 * @brief This file contains functions for handling user commands,
 *          including parsing and actual function behavior.
 */

#include "../include/command.h"

/*!
 * @brief This function creates a new empty command_t context.
 *
 * @return Pointer to new commant_t context. NULL on error.
 */
command_t *
command_create (void)
{
    command_t * p_command = calloc(1, sizeof(command_t));
    if (NULL == p_command)
    {
        goto EXIT;
    }
    p_command->argc = 0;
    p_command->pp_argv = NULL;

    EXIT:
        return p_command;
}

/*!
 * @brief This function destroys a command_t context.
 *
 * @param[in] p_command The command_t context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_destroy (command_t * p_command)
{
    int status = -1;
    if ((NULL == p_command) ||
        (-1 == command_clear(p_command)))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if (NULL != p_command)
        {
            free(p_command);
            p_command = NULL;
        }
        return status;
}

/*!
 * @brief This function parses a raw command into a command_t context.
 *
 * @param[out] p_command The command_t context to parse the raw command into.
 * @param[in] p_str The raw command to process. This string is consumed
 *                      in the process.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_parse (command_t * p_command, char * p_str)
{
    int status = -1;
    if ((NULL == p_command) ||
        (NULL == p_str))
    {
        goto EXIT;
    }

    // Split the string into individual arguments.
    char * p_token = strtok(p_str, " ");
    while (NULL != p_token)
    {
        // Allocate memory for the current argument.
        char * p_arg = calloc(strlen(p_token) + 1, sizeof(char));
        if (NULL == p_arg)
        {
            goto EXIT;
        }
        strcpy(p_arg, p_token);

        // Add the argument to the result.
        p_command->pp_argv = realloc(p_command->pp_argv,
                                     (p_command->argc + 1) * sizeof(char *));
        p_command->pp_argv[p_command->argc] = p_arg;

        // Increment the argument count.
        p_command->argc++;

        // Get the next token.
        p_token = strtok(NULL, " ");
    }

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function clears any currently stored command information
 *          within the context, without destroying the context itself.
 * 
 * @param[in] p_command The command context to clear.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_clear (command_t * p_command)
{
    int status = -1;
    if (NULL == p_command)
    {
        goto EXIT;
    }

    for (size_t i = 0; i < p_command->argc; ++i)
    {
        free(p_command->pp_argv[i]);
    }
    free(p_command->pp_argv);

    p_command->argc = 0;
    p_command->pp_argv = NULL;

    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
