/*!
 * @file http.h
 *
 * @brief This file contains defintions for making HTTP requests
 *          and receiving responses.
 * 
 *          It also contains the http_t datatype which holds the
 *              HTTP header fields.
 */

#ifndef HTTP_H
#define HTTP_H

#include <stdlib.h>
#include <stdio.h>

#define HTTP_ALL  -1
#define HTTP_HOST 0
#define HTTP_AUTH 1
#define HTTP_MF   2
#define HTTP_REF  3
#define HTTP_UA   4

/*!
 * @brief This datatype defines the HTTP header fields that are stored
 *          for the user.
 * 
 *          The user may alter these fields, and then send them in HTTP
 *              requests.
 * 
 * @param p_host The "host" HTTP header field.
 * @param p_auth The "auth" HTTP header field.
 * @param p_mf   The "max-forwards" HTTP header field.
 * @param p_ref  The "referer" HTTP header field.
 * @param p_ua   The "user-agent" HTTP header field.
 */
typedef struct _http
{
    char * p_host;
    char * p_auth;
    char * p_mf;
    char * p_ref;
    char * p_ua;
} http_t;

/*!
 * @brief This function creates a new http context.
 *
 * @return Pointer to new http context. NULL on error.
 */
http_t *
http_create (void);

/*!
 * @brief This function destroys an http context.
 *
 * @param[in] p_http The http context.
 * 
 * @return 0 on success, -1 on error.
 */
int
http_destroy (http_t * p_http);

/*!
 * @brief This function displays a specified HTTP header field.
 *
 * @param[in] p_http The http context.
 * @param[in] field The field number to display. -1 for all.
 * 
 * @return No return value expected.
 */
void
http_show (const http_t * p_http, const int field);

#endif // HTTP_H

/***   end of file   ***/
