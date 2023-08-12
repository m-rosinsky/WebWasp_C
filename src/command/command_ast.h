/*!
 * @file src/command/command_ast.h
 *
 * @brief This file contains an implementation for an abstract
 *          syntax tree containing the command syntax
 *          for the program's console.
 * 
 *          This allows for tab completion of commands in a
 *          structured format.
 */

#ifndef WW_COMMAND_AST_H
#define WW_COMMAND_AST_H

#include <stdlib.h>

#include "node.h"

/*!
 * @brief This defines the command AST structure.
 *
 * @param p_root The root node of the AST.
 */
typedef struct _command_ast
{
    node_t * p_root;
} command_ast_t;

/*!
 * @brief This function creates and subsequently initializes
 *          the abstract syntax tree.
 * 
 * @return Pointer to new ast context. NULL on error.
 */
command_ast_t *
command_ast_create (void);

/*!
 * @brief This function destroys an ast context.
 *
 * @param[out] p_ast The ast context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_ast_destroy (command_ast_t * p_ast);

#endif // WW_COMMAND_AST_H

/***   end of file   ***/