/*!
 * @file parser.h
 *
 * @brief This file contains functions for handling user commands,
 *          including parsing and actual function behavior.
 */

#ifndef WW_CONSOLE_PARSER_H
#define WW_CONSOLE_PARSER_H

#include <stdlib.h>
#include <string.h>

/*!
 * @brief This datatype defines a parse context, which contains a parsed
 *          command.
 *
 * @param argc The number of arguments in the command.
 * @param pp_argv The list of arguments in string form.
 */
typedef struct _parser
{
    size_t argc;
    char ** pp_argv;
} parser_t;

/*!
 * @brief This function creates a new empty parser context.
 *
 * @return Pointer to new parser context. NULL on error.
 */
parser_t *
parser_create (void);

/*!
 * @brief This function destroys a parse context.
 *
 * @param[in] p_parser The parse context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_destroy (parser_t * p_parser);

/*!
 * @brief This function parses a raw command into a parser context.
 *
 * @param[out] p_parser The parser context to parse the raw command into.
 * @param[in] p_str The raw command to process.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_parse (parser_t * p_parser, const char * p_str);

/*!
 * @brief This function clears any currently stored command information
 *          within the context, without destroying the context itself.
 * 
 * @param[in] p_parser The parser context to clear.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_clear (parser_t * p_parser);

#endif // WW_CONSOLE_PARSER_H

/***   end of file   ***/
