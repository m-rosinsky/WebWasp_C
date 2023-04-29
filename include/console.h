/*!
 * @file console.h
 *
 * @brief This file contains the implementation for the console. It
 *          is responsible for gathering user input and passing
 *          commands of to respective modules.
 */

#include <stdlib.h>

#include "utils/queue.h"

#define MAX_CMD_SIZE 1024

/*!
 * @brief This datatype defines a console context.
 *
 * @param history_max The maximum number of commands to remember.
 * @param p_history The command history queue.
 */
typedef struct _console
{
    size_t history_max;
    queue_t * p_history;
} console_t;

/*!
 * @brief This function creates a new console context.
 *
 * @param[in] history_max The maximum number of commands to remember.
 * 
 * @return Pointer to new console context. NULL on error.
 */
console_t *
console_create (const size_t history_max);

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

/***   end of file   ***/