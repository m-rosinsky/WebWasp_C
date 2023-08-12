/*!
 * @file main.c
 *
 * @brief This is the main file for the program.
 */

#include <stdio.h>

#include "command/command_ast.h"
#include "common/vector.h"

void
print_ast (command_ast_t * p_ast)
{
    if ((NULL == p_ast) ||
        (NULL == p_ast->p_root))
    {
        goto EXIT;
    }

    vector_t * p_vec = vector_create();
    if (NULL == p_vec)
    {
        goto EXIT;
    }

    vector_push_front(p_vec, p_ast->p_root);

    node_t * p_curr = NULL;
    while (0 != p_vec->size)
    {
        p_curr = (node_t *) vector_pop_front(p_vec);
        if (NULL == p_curr)
        {
            goto EXIT;
        }

        node_t * p_child = NULL;
        for (size_t idx = 0; idx < p_curr->p_children->size; ++idx)
        {
            p_child = (node_t *) vector_at(p_curr->p_children, idx);
            if (NULL == p_child)
            {
                goto EXIT;
            }

            if (-1 == vector_push_back(p_vec, p_child))
            {
                goto EXIT;
            }
        }

        if (NULL == p_curr->p_data)
        {
            printf("NULL\n");
        }
        else
        {
            printf("'%s'\n", p_curr->p_data);
        }
    }

    EXIT:
        if (NULL != p_vec)
        {
            vector_destroy(p_vec);
            p_vec = NULL;
        }
        return;
}

/*!
 * @brief This is the main entry point of the program.
 *
 * @return The status of the program.
 */
int
main ()
{
    command_ast_t * p_ast = command_ast_create();
    if (NULL == p_ast)
    {
        printf("create\n");
        return 1;
    }

    print_ast(p_ast);

    if (-1 == command_ast_destroy(p_ast))
    {
        printf("destroy\n");
        return 1;
    }

    printf("success\n");
    return 0;
}

/***   end of file   ***/
