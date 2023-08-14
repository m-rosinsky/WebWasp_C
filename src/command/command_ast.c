/*!
 * @file src/command/command_ast.c
 *
 * @brief This file contains an implementation for an abstract
 *          syntax tree containing the command syntax
 *          for the program's console.
 * 
 *          This allows for tab completion of commands in a
 *          structured format.
 */

#include <stdbool.h>
#include <string.h>

#include "command_ast.h"
#include "../common/vector.h"

/***   static function forward delcares   ***/

static int
initialize (command_ast_t * p_ast);

static int
finalize (command_ast_t * p_ast);

static int
add_result (command_ast_output_t * p_result, char * p_token);

/***   public functions   ***/

/*!
 * @brief This function creates and subsequently initializes
 *          the abstract syntax tree.
 * 
 * @return Pointer to new ast context. NULL on error.
 */
command_ast_t *
command_ast_create (void)
{
    int status = -1;
    command_ast_t * p_ast = calloc(1, sizeof(command_ast_t));
    if (NULL == p_ast)
    {
        goto EXIT;
    }
    p_ast->p_root = NULL;

    // Initialize the ast.
    if (-1 == initialize(p_ast))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if ((-1 == status) &&
            (NULL != p_ast))
        {
            command_ast_destroy(p_ast);
            p_ast = NULL;
        }
        return p_ast;
}

/*!
 * @brief This function destroys an ast context.
 *
 * @param[out] p_ast The ast context to destroy.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_ast_destroy (command_ast_t * p_ast)
{
    int status = -1;
    if (NULL == p_ast)
    {
        goto EXIT;
    }

    // Finalize the ast.
    if (-1 == finalize(p_ast))
    {
        goto EXIT;
    }
    
    status = 0;

    EXIT:
        if (NULL != p_ast)
        {
            free(p_ast);
            p_ast = NULL;
        }
        return status;
}

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
                      const string_split_t * p_split)
{
    int status = -1;
    command_ast_output_t * p_result = NULL;
    vector_t * p_vec = NULL;
    if ((NULL == p_ast) ||
        (NULL == p_ast->p_root) ||
        (NULL == p_split))
    {
        goto EXIT;
    }

    // Allocate a new output context.
    p_result = calloc(1, sizeof(command_ast_output_t));
    if (NULL == p_result)
    {
        goto EXIT;
    }
    p_result->argc = 0;
    p_result->argv = NULL;

    // No tokens in split string dictates success, but empty result.
    if (0 == p_split->len)
    {
        status = 0;
        goto EXIT;
    }

    // This vector allows us to iterate through the tree.
    p_vec = vector_create();
    if (NULL == p_vec)
    {
        goto EXIT;
    }

    // Push all children of root into the vector to start.
    node_t * p_child = NULL;
    for (size_t idx = 0; idx < p_ast->p_root->p_children->size; ++idx)
    {
        // Get the node at index.
        p_child = vector_at(p_ast->p_root->p_children, idx);
        if (NULL == p_child)
        {
            goto EXIT;
        }

        // Push child to back of vector.
        if (-1 == vector_push_back(p_vec, p_child))
        {
            goto EXIT;
        }
    }

    // This holds the current token within the parsed command.
    char * p_token = NULL;
    size_t tok_len = 0;

    // Iterate through tree.
    node_t * p_curr = NULL;
    while (0 != p_vec->size)
    {
        // Pop the first node.
        p_curr = vector_pop_front(p_vec);
        if (NULL == p_curr)
        {
            goto EXIT;
        }

        // Get the token with the associated depth of the node.
        // -1 since root is at zero and first commands are at
        // depth 1.
        uint32_t depth = p_curr->depth - 1;
        if (depth >= p_split->len)
        {
            goto EXIT;
        }
        p_token = p_split->pp_substrs[depth];
        tok_len = strlen(p_token);

        // If this is the final token of the parsed command, compare it
        // to the first part of the current node.
        if (depth == (p_split->len - 1))
        {
            // If the token is longer than the current node, skip.
            if (tok_len > strlen(p_curr->p_data))
            {
                continue;
            }

            // Compare the token with the segment of the node.
            if (0 != strncmp(p_token, p_curr->p_data, tok_len))
            {
                continue;
            }

            // Add this node to list of viable options, but don't add
            // children since this is final token.
            if (-1 == add_result(p_result, p_curr->p_data))
            {
                goto EXIT;
            }

            continue;
        }

        // This is not the final token in the command. Look for an exact
        // match and add the children to the iterative vector.
        if (strlen(p_curr->p_data) != tok_len)
        {
            continue;
        }

        if (0 != strcmp(p_curr->p_data, p_token))
        {
            continue;
        }

        // Add children to iterative vector.
        for (size_t idx = 0; idx < p_curr->p_children->size; ++idx)
        {
            // Get the node at index.
            p_child = vector_at(p_curr->p_children, idx);
            if (NULL == p_child)
            {
                goto EXIT;
            }

            // Push child to back of vector.
            if (-1 == vector_push_back(p_vec, p_child))
            {
                goto EXIT;
            }
        }
    }

    status = 0;

    EXIT:
        // Clean the iterative vector.
        if (NULL != p_vec)
        {
            vector_destroy(p_vec);
            p_vec = NULL;
        }

        // Clean the result on error.
        if ((-1 == status) &&
            (NULL != p_result))
        {
            command_ast_clean(p_result);
            p_result = NULL;
        }
        
        return p_result;
}

/*!
 * @brief This function cleans an output context.
 *
 * @param[in/out] p_result The output context to clean.
 * 
 * @return 0 on success, -1 on error.
 */
int
command_ast_clean (command_ast_output_t * p_result)
{
    int status = -1;
    if (NULL == p_result)
    {
        goto EXIT;
    }

    // Free all strings in argv.
    for (size_t idx = 0; idx < p_result->argc; ++idx)
    {
        free(p_result->argv[idx]);
        p_result->argv[idx] = NULL;
    }

    status = 0;

    EXIT:
        if ((NULL != p_result) &&
            (NULL != p_result->argv))
        {
            free(p_result->argv);
            p_result->argv = NULL;
        }
        if (NULL != p_result)
        {
            free(p_result);
            p_result = NULL;
        }
        return status;
}

/***   static function implementations   ***/

/*!
 * @brief This function initialize an ast context. It constructs
 *          the command syntax tree with commands tailored to
 *          this program.
 * 
 * @param[in/out] p_ast The ast context to initialize.
 * 
 * @return 0 on success, -1 on error.
 */
static int
initialize (command_ast_t * p_ast)
{
    int status = -1;
    if (NULL == p_ast)
    {
        goto EXIT;
    }

    // Create and assign the root node.
    node_t * p_root = node_create(NULL);
    if (NULL == p_root)
    {
        goto EXIT;
    }
    p_ast->p_root = p_root;

    // Structure the "quit" command.
    node_t * p_quit = node_create("quit");
    if (NULL == p_quit)
    {
        goto EXIT;
    }
    node_adopt(p_ast->p_root, p_quit);

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function finalizes an ast context. It uses
 *          a vector to clean all nodes from an ast.
 * 
 * @param[in/out] p_ast The ast context to finalize.
 * 
 * @return 0 on success, -1 on error.
 */
static int
finalize (command_ast_t * p_ast)
{
    int status = -1;
    if (NULL == p_ast)
    {
        goto EXIT;
    }
    
    // Create the vector to use for iterative cleanup.
    vector_t * p_vec = vector_create();
    if (NULL == p_vec)
    {
        goto EXIT;
    }

    // Push the root node into the vector.
    if (-1 == vector_push_front(p_vec, p_ast->p_root))
    {
        goto EXIT;
    }

    // This holds the current node being cleaned.
    node_t * p_curr = NULL;

    // Loop through nodes in ast.
    while (0 != p_vec->size)
    {
        // Pop the first node in the vector.
        p_curr = (node_t *) vector_pop_front(p_vec);
        if (NULL == p_curr)
        {
            goto EXIT;
        }

        // Add the current node's children to the vector.
        node_t * p_child = NULL;
        for (size_t idx = 0; idx < p_curr->p_children->size; ++idx)
        {
            // Get the child at index.
            p_child = (node_t *) vector_at(p_curr->p_children, idx);
            if (NULL == p_child)
            {
                goto EXIT;
            }

            // Push child onto vector.
            if (-1 == vector_push_back(p_vec, p_child))
            {
                goto EXIT;
            }
        }

        // Destroy the current node.
        if (-1 == node_destroy(p_curr))
        {
            goto EXIT;
        }
    }

    status = 0;

    EXIT:
        // Destroy the cleanup vector.
        if (NULL != p_vec)
        {
            vector_destroy(p_vec);
            p_vec = NULL;
        }
        return status;
}

static int
add_result (command_ast_output_t * p_result, char * p_token)
{
    int status = -1;
    if ((NULL == p_result) ||
        (NULL == p_token))
    {
        goto EXIT;
    }

    // Reallocate the argv array.
    p_result->argc++;
    p_result->argv = realloc(p_result->argv, p_result->argc * sizeof(char *));

    // Allocate the string.
    size_t tok_len = strlen(p_token);
    char * p_str = calloc(tok_len + 1, sizeof(char));
    if (NULL == p_str)
    {
        goto EXIT;
    }
    strcpy(p_str, p_token);

    // Add string to argv.
    p_result->argv[p_result->argc - 1] = p_str;

    status = 0;

    EXIT:
        return status;
}

/***   end of file   ***/
