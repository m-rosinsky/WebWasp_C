/*!
 * @file command_node.c
 *
 * @brief This file contains a defintion for a node in a command
 *          syntax tree.
 */

#include <string.h>

#include "node.h"

/*!
 * @brief This function creates a new node context.
 *
 * @param[in] p_data The data for the node.
 * 
 * @return Pointer to the new node context. NULL on error.
 */
node_t *
node_create (const char * p_data)
{
    int status = -1;
    node_t * p_node = calloc(1, sizeof(node_t));
    if (NULL == p_node)
    {
        goto EXIT;
    }
    p_node->p_data = NULL;
    p_node->p_children = NULL;

    // Create the child vector.
    p_node->p_children = vector_create();
    if (NULL == p_node->p_children)
    {
        goto EXIT;
    }

    // Create the data.
    if (NULL == p_data)
    {
        // Data is allowed to be null.
        status = 0;
        goto EXIT;
    }

    // Allocate space.
    size_t data_len = strlen(p_data);
    p_node->p_data = calloc(data_len + 1, sizeof(char));
    if (NULL == p_node->p_data)
    {
        goto EXIT;
    }
    strcpy(p_node->p_data, p_data);

    status = 0;

    EXIT:
        if ((-1 == status) &&
            (NULL != p_node))
        {
            node_destroy(p_node);
            p_node = NULL;
        }
        return p_node;
}

/*!
 * @brief This function destroys a node context.
 *
 * @param[in/out] p_node The node to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
node_destroy (node_t * p_node)
{
    int status = -1;
    if (NULL == p_node)
    {
        goto EXIT;
    }

    // Destroy the data.
    if (NULL != p_node->p_data)
    {
        free(p_node->p_data);
        p_node->p_data = NULL;
    }

    // Destroy the child vector.
    vector_destroy(p_node->p_children);

    status = 0;

    EXIT:
        if (NULL != p_node)
        {
            free(p_node);
            p_node = NULL;
        }
        return status;
}

/*!
 * @brief This function assigns a node as a child of another node.
 *
 * @param[in/out] p_parent The parent node.
 * @param[in/out] p_child The child node.
 * 
 * @return 0 on success, -1 on error.
 */
int
node_adopt (node_t * p_parent, node_t * p_child)
{
    int status = -1;
    if ((NULL == p_parent) ||
        (NULL == p_parent->p_children) ||
        (NULL == p_child))
    {
        goto EXIT;
    }

    if (-1 == vector_push_back(p_parent->p_children, p_child))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
