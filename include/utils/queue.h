/*!
 * @file queue.h
 *
 * @brief This file contains a generic queue implementation using
 *          a singly-linked list.
 */

#ifndef UTILS_QUEUE_H
#define UTILS_QUEUE_H

#include <stdlib.h>

/*!
 * @brief This datatype defines a queue node.
 *
 * @param p_data The node's data.
 * @param p_next The next node in the queue.
 */
typedef struct _qnode qnode_t;
struct _qnode
{
    void * p_data;
    qnode_t * p_next;
};

/*!
 * @brief This datatype defines a queue context.
 *
 * @param p_head The first node in the queue.
 * @param p_tail The last node in the queue.
 * @param size The number of nodes in the queue.
 */
typedef struct _queue
{
    qnode_t * p_head;
    qnode_t * p_tail;
    size_t size;
} queue_t;

/*!
 * @brief This function creates a new queue context.
 *
 * @return Pointer to new queue context. NULL on error.
 */
queue_t *
queue_create (void);

/*!
 * @brief This function destroys a queue context.
 *
 * @param[in] p_queue The queue context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
queue_destroy (queue_t * p_queue);

/*!
 * @brief This function enqueues a new item onto a queue context.
 *
 * @param[in] p_queue The queue context.
 * @param[in] p_data The data to enqueue.
 * 
 * @return 0 on success, -1 on error.
 */
int
queue_enq (queue_t * p_queue, void * p_data);

/*!
 * @brief This function dequeues an item from a queue context.
 *
 * @param[in] p_queue The queue context.
 * 
 * @return The dequeue'd item. NULL on error or empty queue.
 */
void *
queue_deq (queue_t * p_queue);

#endif // UTILS_QUEUE_H

/***   end of file   ***/
