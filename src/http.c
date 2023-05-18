/*!
 * @file http.c
 *
 * @brief This file contains defintions for making HTTP requests
 *          and receiving responses.
 * 
 *          It also contains the http_t datatype which holds the
 *              HTTP header fields.
 */

#include "../include/http.h"

/*!
 * @brief This function creates a new http context.
 *
 * @return Pointer to new http context. NULL on error.
 */
http_t *
http_create (void)
{
    http_t * p_http = calloc(1, sizeof(http_t));
    if (NULL == p_http)
    {
        goto EXIT;
    }
    p_http->p_host = NULL;
    p_http->p_auth = NULL;
    p_http->p_mf = NULL;
    p_http->p_ref = NULL;
    p_http->p_ua = NULL;

    EXIT:
        return p_http;
}

/*!
 * @brief This function destroys an http context.
 *
 * @param[in] p_http The http context.
 * 
 * @return 0 on success, -1 on error.
 */
int
http_destroy (http_t * p_http)
{
    int status = -1;
    if (NULL == p_http)
    {
        goto EXIT;
    }

    if (NULL != p_http->p_host)
    {
        free(p_http->p_host);
        p_http->p_host = NULL;
    }

    if (NULL != p_http->p_auth)
    {
        free(p_http->p_auth);
        p_http->p_auth = NULL;
    }

    if (NULL != p_http->p_mf)
    {
        free(p_http->p_mf);
        p_http->p_mf = NULL;
    }

    if (NULL != p_http->p_ref)
    {
        free(p_http->p_ref);
        p_http->p_ref = NULL;
    }

    if (NULL != p_http->p_ua)
    {
        free(p_http->p_ua);
        p_http->p_ua = NULL;
    }

    status = 0;

    EXIT:
        if (NULL != p_http)
        {
            free(p_http);
            p_http = NULL;
        }
        return status;
}

/*!
 * @brief This function displays a specified HTTP header field.
 *
 * @param[in] p_http The http context.
 * @param[in] field The field number to display. -1 for all.
 * 
 * @return No return value expected.
 */
void
http_show (const http_t * p_http, const int field)
{
    if (NULL == p_http)
    {
        goto EXIT;
    }

    if ((-1 == field) ||
        (HTTP_HOST == field))
    {
        printf("[+] HOST: '");
        if (NULL != p_http->p_host)
        {
            printf("%s", p_http->p_host);
        }
        printf("'\r\n");
    }

    if ((-1 == field) ||
        (HTTP_AUTH == field))
    {
        printf("[+] AUTH: '");
        if (NULL != p_http->p_auth)
        {
            printf("%s", p_http->p_auth);
        }
        printf("'\r\n");
    }

    if ((-1 == field) ||
        (HTTP_MF == field))
    {
        printf("[+] MAX-FORWARDS: '");
        if (NULL != p_http->p_mf)
        {
            printf("%s", p_http->p_mf);
        }
        printf("'\r\n");
    }

    if ((-1 == field) ||
        (HTTP_REF == field))
    {
        printf("[+] REFERER: '");
        if (NULL != p_http->p_ref)
        {
            printf("%s", p_http->p_ref);
        }
        printf("'\r\n");
    }

    if ((-1 == field) ||
        (HTTP_UA == field))
    {
        printf("[+] USER-AGENT: '");
        if (NULL != p_http->p_ua)
        {
            printf("%s", p_http->p_ua);
        }
        printf("'\r\n");
    }

    EXIT:
        return;
}

/***   end of file   ***/
