/*!
 * @file command_node.h
 *
 * @brief This file contains a defintion for a node in a command
 *          syntax tree.
 */

#ifndef _WEBWASP_SRC_COMMAND_NODE_H
#define _WEBWASP_SRC_COMMAND_NODE_H

#include <stdint.h>
#include <stdlib.h>

#include "../common/vector.h"

/*!
 * @brief This datatype defines a node for a command syntax tree.
 *
 * @param p_data The data for the node.
 * @param p_children A vector containing the child nodes.
 * @param depth The depth within the tree.
 */
typedef struct _node
{
    char * p_data;
    vector_t * p_children;
    uint32_t depth;
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

/*!
 * @brief This function assigns a node as a child of another node.
 *
 *          The parent node will set the adopted node's depth
 *              to one plus its own depth.
 *
 * @param[in/out] p_parent The parent node.
 * @param[in/out] p_child The child node.
 * 
 * @return 0 on success, -1 on error.
 */
int
node_adopt (node_t * p_parent, node_t * p_child);

#endif // _WEBWASP_SRC_COMMAND_NODE_H

/***   end of file   ***/
