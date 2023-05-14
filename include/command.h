/*!
 * @file command.h
 *
 * @brief This file contains functions for handling user commands,
 *          including parsing and actual function behavior.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <string.h>

/*!
 * @brief This datatype defines a parsed command.
 *
 * @param argc The number of arguments in the command.
 * @param pp_argv The list of arguments in string form.
 */
typedef struct _command
{
    size_t argc;
    char ** pp_argv;
} command_t;

/*!
 * @brief This function creates a new empty command_t context.
 *
 * @return Pointer to new commant_t context. NULL on error.
 */
command_t *
command_create (void);

/*!
 * @brief This function destroys a command_t context.
 *
 * @param[in] p_command The command_t context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_destroy (command_t * p_command);

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
command_parse (command_t * p_command, char * p_str);

/*!
 * @brief This function clears any currently stored command information
 *          within the context, without destroying the context itself.
 * 
 * @param[in] p_command The command context to clear.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_clear (command_t * p_command);

#endif // COMMAND_H

/***   end of file   ***/
