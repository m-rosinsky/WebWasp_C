/*!
 * @file history.h
 *
 * @brief This file contains an implementation for handling the console's
 *          command history.
 */

#ifndef UTILS_HISTORY_H
#define UTILS_HISTORY_H

#include <stdlib.h>
#include <string.h>

/*!
 * @brief This datatype defines the history context.
 *
 * @param pp_data The array holding the command history.
 * @param size The number of commands currently being held.
 * @param cap The capacity of the array (The max number of commands
 *              that can be held).
 */
typedef struct _history
{
    char ** pp_data;
    size_t size;
    size_t cap;
} history_t;

/*!
 * @brief This function creates a new history context.
 *
 * @param[in] cap The maximum number of commands the context can hold.
 * 
 * @return Pointer to new history context. NULL on error.
 */
history_t *
history_create (const size_t cap);

/*!
 * @brief This function destroys a history context and deallocates
 *          associated memory.
 * 
 * @param[in] p_history The history context.
 * 
 * @return 0 on success, -1 on error.
 */
int
history_destroy (history_t * p_history);

/*!
 * @brief This function pushes a new command into the history context.
 *          If the context is at capacity, the oldest command will
 *          be deallocated and pushed out.
 * 
 * @param[in] p_history The history context.
 * @param[in] p_cmd The command to push.
 * 
 * @return 0 on success, -1 on error.
 */
int
history_push (history_t * p_history, const char * p_cmd);

#endif // UTILS_HISTORY_H

/***   end of file   ***/
