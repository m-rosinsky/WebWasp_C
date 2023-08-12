/*!
 * @file parser.c
 *
 * @brief This file contains functions for handling user commands,
 *          including parsing and actual function behavior.
 */

#include "parser.h"

/*!
 * @brief This function creates a new empty parser context.
 *
 * @return Pointer to new parser context. NULL on error.
 */
parser_t *
parser_create (void)
{
    parser_t * p_parser = calloc(1, sizeof(parser_t));
    if (NULL == p_parser)
    {
        goto EXIT;
    }
    p_parser->argc = 0;
    p_parser->pp_argv = NULL;

    EXIT:
        return p_parser;
}

/*!
 * @brief This function destroys a parse context.
 *
 * @param[in] p_parser The parse context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_destroy (parser_t * p_parser)
{
    int status = -1;
    if ((NULL == p_parser) ||
        (-1 == parser_clear(p_parser)))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if (NULL != p_parser)
        {
            free(p_parser);
            p_parser = NULL;
        }
        return status;
}

/*!
 * @brief This function parses a raw command into a parser context.
 *
 * @param[out] p_parser The parser context to parse the raw command into.
 * @param[in] p_str The raw command to process.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_parse (parser_t * p_parser, const char * p_str)
{
    int status = -1;
    char * p_cpy = NULL;
    if ((NULL == p_parser) ||
        (NULL == p_str))
    {
        goto EXIT;
    }

    // Backup the string.
    size_t str_len = strlen(p_str);
    p_cpy = calloc(str_len + 1, sizeof(char));
    if (NULL == p_cpy)
    {
        goto EXIT;
    }
    strcpy(p_cpy, p_str);

    // Split the string into individual arguments.
    char * p_token = strtok(p_cpy, " ");
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
        p_parser->pp_argv = realloc(p_parser->pp_argv,
                                     (p_parser->argc + 1) * sizeof(char *));
        p_parser->pp_argv[p_parser->argc] = p_arg;

        // Increment the argument count.
        p_parser->argc++;

        // Get the next token.
        p_token = strtok(NULL, " ");
    }

    status = 0;

    EXIT:
        if (NULL != p_cpy)
        {
            free(p_cpy);
            p_cpy = NULL;
        }
        return status;
}

/*!
 * @brief This function clears any currently stored command information
 *          within the context, without destroying the context itself.
 * 
 * @param[in] p_parser The parser context to clear.
 * 
 * @return 0 on success, -1 on error.
 */
int
parser_clear (parser_t * p_parser)
{
    int status = -1;
    if (NULL == p_parser)
    {
        goto EXIT;
    }

    for (size_t i = 0; i < p_parser->argc; ++i)
    {
        free(p_parser->pp_argv[i]);
    }
    free(p_parser->pp_argv);

    p_parser->argc = 0;
    p_parser->pp_argv = NULL;

    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
