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

#ifndef _WEBWASP_SRC_COMMAND_COMMAND_AST_H
#define _WEBWASP_SRC_COMMAND_COMMAND_AST_H

#include <stdlib.h>

#include "node.h"
#include "../common/string_utils.h"

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
 * @brief This datatype defines a result of tab completion.
 *
 * @param argc The number of suggestions in the result.
 * @param argv An array of strings with the results.
 */
typedef struct _command_ast_output
{
    size_t argc;
    char ** argv;
} command_ast_output_t;

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

/*!
 * @brief This function attempts tab completion using an ast
 *          context and a parsed command in the form of
 *          a parser context.
 * 
 * @param[in] p_ast The ast context.
 * @param[in] p_split The string split context.
 * 
 * @return Pointer to new command ast output context that will
 *          need to be free'd with a call to command_ast_clean.
 * 
 *          NULL on error or no suggestions.
 */
command_ast_output_t *
command_ast_complete (const command_ast_t * p_ast,
                      const string_split_t * p_split);

/*!
 * @brief This function cleans an output context.
 *
 * @param[in/out] p_result The output context to clean.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_ast_clean (command_ast_output_t * p_result);

#endif // _WEBWASP_SRC_COMMAND_COMMAND_AST_H

/***   end of file   ***/