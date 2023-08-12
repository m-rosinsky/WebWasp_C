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

#include "command_ast.h"
#include "../common/vector.h"

/***   static function forward delcares   ***/

static int
initialize (command_ast_t * p_ast);

static int
finalize (command_ast_t * p_ast);

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

/***   end of file   ***/
