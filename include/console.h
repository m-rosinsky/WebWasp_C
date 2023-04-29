/*!
 * @file console.h
 *
 * @brief This file contains the implementation for the console. It
 *          is responsible for gathering user input and passing
 *          commands of to respective modules.
 */

#include <stdlib.h>

/*!
 * @brief This datatype defines a console context.
 *
 * @param history_max The maximum number of commands to remember.
 * @param p_history The command history queue.
 */
typedef struct _console
{
    size_t history_max;
} console_t;

/***   end of file   ***/