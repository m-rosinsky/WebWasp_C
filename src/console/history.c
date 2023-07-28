/*!
 * @file history.c
 *
 * @brief This file contains an implementation for handling the console's
 *          command history.
 */

#include "history.h"

/*!
 * @brief This function creates a new history context.
 *
 * @param[in] cap The maximum number of commands the context can hold.
 * 
 * @return Pointer to new history context. NULL on error.
 */
history_t *
history_create (const size_t cap)
{
    int status = -1;
    history_t * p_history = calloc(1, sizeof(history_t));
    if (NULL == p_history)
    {
        goto EXIT;
    }
    p_history->pp_data = NULL;
    p_history->size = 0;
    p_history->cap = cap;

    // Allocate the data array.
    p_history->pp_data = calloc(cap, sizeof(char *));
    if (NULL == p_history->pp_data)
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if ((-1 == status) &&
            (NULL != p_history))
        {
            history_destroy(p_history);
            p_history = NULL;
        }
        return p_history;
}

/*!
 * @brief This function destroys a history context and deallocates
 *          associated memory.
 * 
 * @param[in] p_history The history context.
 * 
 * @return 0 on success, -1 on error.
 */
int
history_destroy (history_t * p_history)
{
    int status = -1;
    if (NULL == p_history)
    {
        goto EXIT;
    }

    // Free all commands the in the context.
    for (size_t i = 0; i < p_history->size; ++i)
    {
        free(p_history->pp_data[i]);
        p_history->pp_data[i] = NULL;
    }

    // Free the command array.
    free(p_history->pp_data);
    p_history->pp_data = NULL;

    status = 0;

    EXIT:
        if (NULL != p_history)
        {
            free(p_history);
            p_history = NULL;
        }
        return status;
}

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
history_push (history_t * p_history, const char * p_cmd)
{
    int status = -1;
    if ((NULL == p_history) ||
        (NULL == p_history->pp_data) ||
        (NULL == p_cmd))
    {
        goto EXIT;
    }

    // Heap allocate a copy of the new command.
    size_t cmd_len = strlen(p_cmd);
    char * p_new = calloc(cmd_len + 1, sizeof(char));
    strncpy(p_new, p_cmd, cmd_len);

    // If the array is full, free the last command in the array.
    if (p_history->size == p_history->cap)
    {
        free(p_history->pp_data[p_history->cap - 1]);
    }
    else
    {
        p_history->size++;
    }

    // Shift all entries back.
    for (size_t i = p_history->cap - 1; i > 0; --i)
    {
        p_history->pp_data[i] = p_history->pp_data[i - 1];
    }

    // Push the new command into the first entry of the array and adjust size.
    p_history->pp_data[0] = p_new;

    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
