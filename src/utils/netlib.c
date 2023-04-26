/*!
 * @file netlib.c
 *
 * @brief This file contains various abstractions for
 *          networking functions.
 */

#include "../../include/utils/netlib.h"

/*!
 * @brief This function creates a new IPv4 TCP socket.
 *
 * @return The FD of the new socket. -1 on error.
 */
int
nlib_create (void)
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

/*!
 * @brief This function closes a socket.
 *
 * @param[in] s_fd The socket FD.
 * 
 * @return 0 on success, -1 on error.
 */
int
nlib_close (const int s_fd)
{
    return close(s_fd);
}

/*!
 * @brief This function attempts to connect to a remote host.
 *
 * @param[in] s_fd The socket file descriptor.
 * @param[in] p_addr The remote host address in string format.
 * @param[in] port The remote host port.
 * 
 * @return 0 on success, -1 on error.
 */
int
nlib_connect (const int s_fd, const char * p_addr, const short port)
{
    int status = -1;
    if ((-1 == s_fd) ||
        (NULL == p_addr))
    {
        goto EXIT;
    }

    // Pack remote host info.
    struct sockaddr_in host_info;
    socklen_t host_len = sizeof(host_info);
    host_info.sin_family = AF_INET;
    host_info.sin_port = htons(port);

    // Pack string address into host info.
    if (-1 == inet_pton(AF_INET, p_addr, &(host_info.sin_addr)))
    {
        goto EXIT;
    }

    // Connect.
    if (-1 == connect(s_fd, (struct sockaddr *) &host_info, host_len))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function sends data over a socket.
 *
 * @param[in] s_fd The socket file descriptor.
 * @param[in] p_data The data to send.
 * @param[in] len The length of p_data in bytes.
 * @param[in] timeo_ms The maximum number of milliseconds to attempt
 *                      to send data before returning. 0 for no timeout.
 * 
 * @return The number of bytes successfully sent. -1 on error.
 */
ssize_t
nlib_send (const int s_fd,
           const char * p_data,
           const size_t len,
           const uint32_t timeo_ms)
{
    ssize_t bytes_sent = -1;
    if ((-1 == s_fd) ||
        (NULL == p_data))
    {
        goto EXIT;
    }

    // Set the timeout value.
    struct timeval tv;
    tv.tv_sec = timeo_ms % 1000;
    tv.tv_usec = (timeo_ms % 1000) * 1000;
    socklen_t tv_len = sizeof(tv);
    if (-1 == setsockopt(s_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, tv_len))
    {
        goto EXIT;
    }

    // Send data.
    bytes_sent = send(s_fd, p_data, len, 0);

    EXIT:
        return bytes_sent;
}

/*!
 * @brief This function receives data over a socket.
 *
 * @param[in] s_fd The socket file descriptor.
 * @param[out] p_data The buffer to store the data.
 * @param[in] len The maximum number of bytes to receive.
 * @param[in] timeo_ms The maximum number of milliseconds to attempt
 *                      to receive data before returning. 0 for no timeout.
 * 
 * @return The number of bytes successfully received. -1 on error.
 */
ssize_t
nlib_recv (const int s_fd,
           char * p_data,
           const size_t len,
           const uint32_t timeo_ms)
{
    ssize_t bytes_recv = -1;
    if ((-1 == s_fd) ||
        (NULL == p_data))
    {
        goto EXIT;
    }

    // Set the timeout value.
    struct timeval tv;
    tv.tv_sec = timeo_ms % 1000;
    tv.tv_usec = (timeo_ms % 1000) * 1000;
    socklen_t tv_len = sizeof(tv);
    if (-1 == setsockopt(s_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, tv_len))
    {
        goto EXIT;
    }

    // Receive data.
    bytes_recv = recv(s_fd, p_data, len, 0);

    EXIT:
        return bytes_recv;
}

/***   end of file   ***/
