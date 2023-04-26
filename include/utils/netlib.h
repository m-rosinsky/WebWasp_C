/*!
 * @file netlib.h
 *
 * @brief This file contains various abstractions for
 *          networking functions.
 */

#ifndef UTILS_NETLIB_H
#define UTILS_NETLIB_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>

/*!
 * @brief This function creates a new IPv4 TCP socket.
 *
 * @return The FD of the new socket. -1 on error.
 */
int
nlib_create (void);

/*!
 * @brief This function closes a socket.
 *
 * @param[in] s_fd The socket FD.
 * 
 * @return 0 on success, -1 on error.
 */
int
nlib_close (const int s_fd);

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
nlib_connect (const int s_fd, const char * p_addr, const short port);

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
           const uint32_t timeo_ms);

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
           const uint32_t timeo_ms);

#endif // UTILS_NETLIB_H

/***   end of file   ***/
