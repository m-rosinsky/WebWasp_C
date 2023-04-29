/*!
 * @file queue.c
 *
 * @brief This file contains a generic queue implementation using
 *          a singly-linked list.
 */

#include "../../include/utils/queue.h"

/*!
 * @brief This function creates a new queue context.
 *
 * @return Pointer to new queue context. NULL on error.
 */
queue_t *
queue_create (void)
{
    queue_t * p_queue = calloc(1, sizeof(queue_t));
    if (NULL == p_queue)
    {
        goto EXIT;
    }
    p_queue->p_head = NULL;
    p_queue->p_tail = NULL;
    p_queue->size = 0;

    EXIT:
        return p_queue;
}

/*!
 * @brief This function destroys a queue context.
 *
 * @param[in] p_queue The queue context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
queue_destroy (queue_t * p_queue)
{
    int status = -1;
    if (NULL == p_queue)
    {
        goto EXIT;
    }

    qnode_t * p_curr = p_queue->p_head;
    qnode_t * p_next = NULL;

    while (NULL != p_curr)
    {
        p_next = p_curr->p_next;
        free(p_curr);
        p_curr = p_next;
    }

    status = 0;

    EXIT:
        if (NULL != p_queue)
        {
            free(p_queue);
            p_queue = NULL;
        }
        return status;
}

/*!
 * @brief This function enqueues a new item onto a queue context.
 *
 * @param[in] p_queue The queue context.
 * @param[in] p_data The data to enqueue.
 * 
 * @return 0 on success, -1 on error.
 */
int
queue_enq (queue_t * p_queue, void * p_data)
{
    int status = -1;
    if ((NULL == p_queue) ||
        (NULL == p_data))
    {
        goto EXIT;
    }

    qnode_t * p_new = calloc(1, sizeof(qnode_t));
    if (NULL == p_new)
    {
        goto EXIT;
    }
    p_new->p_data = p_data;
    p_new->p_next = NULL;

    if (NULL == p_queue->p_head)
    {
        p_queue->p_head = p_new;
    }
    else
    {
        p_queue->p_tail->p_next = p_new;
    }
    p_queue->p_tail = p_new;
    p_queue->size++;

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function dequeues an item from a queue context.
 *
 * @param[in] p_queue The queue context.
 * 
 * @return The dequeue'd item. NULL on error or empty queue.
 */
void *
queue_deq (queue_t * p_queue)
{
    void * p_data = NULL;
    if ((NULL == p_queue) ||
        (NULL == p_queue->p_head))
    {
        goto EXIT;
    }

    // Bookmark the new head node.
    qnode_t * p_next = p_queue->p_head->p_next;

    // Extract the head's data.
    p_data = p_queue->p_head->p_data;

    // If the tail is the same as the head, set tail to NULL.
    if (p_queue->p_head == p_queue->p_tail)
    {
        p_queue->p_tail = NULL;
    }

    // Destroy the head and set to new head node.
    free(p_queue->p_head);
    p_queue->p_head = p_next;

    // Resize.
    p_queue->size--;

    EXIT:
        return p_data;
}

/***   end of file   ***/
