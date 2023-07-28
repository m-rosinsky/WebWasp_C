/*!
 * @file command_node.h
 *
 * @brief This file contains a defintion for a node in a command
 *          syntax tree.
 */

#ifndef WW_COMMAND_NODE_H
#define WW_COMMAND_NODE_H

#include <stdlib.h>

#include "../common/vector.h"

/*!
 * @brief This datatype defines a node for a command syntax tree.
 *
 * @param p_data The data for the node.
 * @param p_children A vector containing the child nodes.
 */
typedef struct _node
{
    char * p_data;
    vector_t * p_children;
} node_t;

/*!
 * @brief This function creates a new node context.
 *
 * @param[in] p_data The data for the node.
 * 
 * @return Pointer to the new node context. NULL on error.
 */
node_t *
node_create (const char * p_data);

/*!
 * @brief This function destroys a node context.
 *
 * @param[in/out] p_node The node to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
node_destroy (node_t * p_node);

#endif // WW_COMMAND_NODE_H

/***   end of file   ***/
