/*!
 * @file console.h
 *
 * @brief This file contains the implementation for the console. It
 *          is responsible for gathering user input and passing
 *          commands of to respective modules.
 */

#ifndef WW_CONSOLE_CONSOLE_H
#define WW_CONSOLE_CONSOLE_H

#include <stdlib.h>
#include <termios.h>

#include "config.h"
#include "history.h"
#include "../common/string_utils.h"
#include "../command/command_ast.h"

#define MAX_CMD_SIZE 1024

/*!
 * @brief This datatype defines a console context.
 *
 * @param p_history The command history queue.
 * @param p_split The string split context to hold a parsed command.
 * @param p_ast The abstract syntax tree for the commands.
 * @param old_console The old termios console config.
 * @param new_console The new termios console config.
 */
typedef struct _console
{
    history_t * p_history;
    string_split_t * p_split;
    command_ast_t * p_ast;
    struct termios old_console;
    struct termios new_console;
} console_t;

/*!
 * @brief This function creates a new console context.
 * 
 * @return Pointer to new console context. NULL on error.
 */
console_t *
console_create (void);

/*!
 * @brief This function destroys a console context.
 *
 * @param[in] p_console The console context.
 * 
 * @return 0 on success, -1 on error.
 */
int
console_destroy (console_t * p_console);

/*!
 * @brief This function runs a console context.
 *
 * @param[in] p_console The console context.
 * 
 * @return No return value expected.
 */
void
console_run (console_t * p_console);

#endif // WW_CONSOLE_CONSOLE_H

/***   end of file   ***/