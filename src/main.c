/*!
 * @file main.c
 *
 * @brief This is the main file for the program.
 */

#include <stdio.h>
#include <string.h>

#include "../include/utils/netlib.h"

/*!
 * @brief This is a temporary function for the initial commit.
 *
 * @return The status of the program.
 */
int
main ()
{
    int s_fd = nlib_create();
    if (-1 == s_fd)
    {
        printf("create\n");
        return 1;
    }

    if (-1 == nlib_connect(s_fd, "127.0.0.1", 8000))
    {
        printf("connect\n");
        return 1;
    }

    char * p_data = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
    if (-1 == nlib_send(s_fd, p_data, strlen(p_data), 5000))
    {
        printf("send\n");
        return 1;
    }

    char p_resp[1024];
    memset(p_resp, '\0', 1024);
    if (-1 == nlib_recv(s_fd, p_resp, 1024, 5000))
    {
        printf("recv\n");
        return 1;
    }

    printf("%s\n\n", p_resp);

    memset(p_resp, '\0', 1024);
    if (-1 == nlib_recv(s_fd, p_resp, 1024, 5000))
    {
        printf("recv\n");
        return 1;
    }

    printf("%s\n\n", p_resp);

    if (-1 == nlib_close(s_fd))
    {
        printf("close\n");
        return 1;
    }

    printf("success\n");
    return 0;
}

/***   end of file   ***/
