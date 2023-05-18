/*!
 * @file command.c
 *
 * @brief This file contains function definitions for the various
 *          functions within the program.
 * 
 *          All functions must accept a parser_t context, and
 *              return -1 on a fatal failure.
 */

#include "../include/command.h"

/*!
 * @brief This function dispatches a command based on a console context.
 *
 * @param[in] p_parser The parser context.
 * @param[in] p_http The http field context.
 * 
 * @return 0 on success, 1 on graceful exit, -1 on fatal failure.
 */
int
command_dispatch (parser_t * p_parser, http_t * p_http)
{
    int status = -1;
    if ((NULL == p_parser) ||
        (NULL == p_http))
    {
        goto EXIT;
    }

    if (0 == p_parser->argc)
    {
        status = 0;
        goto EXIT;
    }

    char * p_cmd = p_parser->pp_argv[0];
    
    if ((0 == strcmp("exit", p_cmd)) ||
        (0 == strcmp("quit", p_cmd)))
    {
        status = 1;
        goto EXIT;
    }

    if (0 == strcmp("show", p_cmd))
    {
        status = command_show(p_parser, p_http);
        status = 0;
        goto EXIT;
    }

    printf("Unrecognized command: '%s'\r\n", p_cmd);
    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
