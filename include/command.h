/*!
 * @file command.h
 *
 * @brief This file contains function definitions for the various
 *          functions within the program.
 * 
 *          All functions must accept a parser_t context, and
 *              return -1 on a fatal failure.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

/*!
 * @brief This function dispatches a command based on a parser context.
 *
 * @param[in] p_parser The parser context.
 * 
 * @return 0 on success, 1 on graceful exit, -1 on fatal failure.
 */
int
command_dispatch (parser_t * p_parser);

#endif // COMMAND_H

/***   end of file   ***/
