/*!
 * @file command_show.c
 *
 * @brief This file contains the show function behavior.
 * 
 *          Usage:
 *          > show {header field | all | url | cookie}
 */

#include "../../include/command.h"
#include "../../include/http.h"

/*!
 * @brief This function show usage details for the show command.
 *
 * @return No return value expected.
 */
static void
show_usage ()
{
    fprintf(stderr, "[?] Usage: show {'header field' | all | url | cookie}\r\n");
    return;
}

/*!
 * @brief This function handles the 'show' command.
 *
 * @param[in] p_parser The parser context.
 * @param[in] p_http The http field context.
 * 
 * @return -1 on fatal failure, 0 otherwise.
 */
int
command_show (parser_t * p_parser, http_t * p_http)
{
    int status = -1;
    if ((NULL == p_parser) ||
        (NULL == p_http))
    {
        goto EXIT;
    }
    status = 0;

    // Verify number of arguments.
    if (2 != p_parser->argc)
    {
        fprintf(stderr, "[?] Incorrect syntax for command: 'show'\r\n");
        show_usage();
        goto EXIT;
    }

    char * p_arg = p_parser->pp_argv[1];

    if (0 == strcmp("all", p_arg))
    {
        http_show(p_http, HTTP_ALL);
    }
    else if (0 == strcmp("host", p_arg))
    {
        http_show(p_http, HTTP_HOST);
    }
    else if (0 == strcmp("auth", p_arg))
    {
        http_show(p_http, HTTP_AUTH);
    }
    else if (0 == strcmp("maxforward", p_arg))
    {
        http_show(p_http, HTTP_MF);
    }
    else if (0 == strcmp("referer", p_arg))
    {
        http_show(p_http, HTTP_REF);
    }
    else if (0 == strcmp("useragent", p_arg))
    {
        http_show(p_http, HTTP_UA);
    }
    else
    {
        fprintf(stderr, "[?] Invalid argument '%s'\r\n", p_arg);
    }

    EXIT:
        return status;
}

/***   end of file   ***/
