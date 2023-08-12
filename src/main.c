/*!
 * @file main.c
 *
 * @brief This is the main file for the program.
 */

#include <stdio.h>

#include "console/console.h"
#include "command/node.h"
#include "common/vector.h"

void
bfs(node_t * p_node)
{
    vector_t * p_q = vector_create();
    if (NULL == p_q)
    {
        goto EXIT;
    }

    if (-1 == vector_push_front(p_q, p_node))
    {
        goto EXIT;
    }

    while (0 != p_q->size)
    {
        node_t * p_curr = vector_pop_front(p_q);
        if (NULL == p_curr)
        {
            goto EXIT;
        }

        if (NULL != p_curr->p_data)
        {
            printf("%s ", p_curr->p_data);
        }

        for (size_t i = 0; i < p_curr->p_children->size; ++i)
        {
            if (-1 == vector_push_back(p_q, p_curr->p_children->pp_data[i]))
            {
                goto EXIT;
            }
        }
    }

    printf("\n");

    EXIT:
        if (NULL != p_q)
        {
            vector_destroy(p_q);
            p_q = NULL;
        }
        return;
}

/*!
 * @brief This is a temporary function for the initial commit.
 *
 * @return The status of the program.
 */
int
main ()
{
    /*
    console_t * p_console = console_create(5);
    if (NULL == p_console)
    {
        printf("Failed to create console context...\n");
        return 1;
    }

    console_run(p_console);

    if (-1 == console_destroy(p_console))
    {
        printf("Failed to destroy console context...\n");
        return 1;
    }
    */

    node_t * p_n1 = node_create("1");
    node_t * p_n2 = node_create("2");
    node_t * p_n3 = node_create("3");
    node_t * p_n4 = node_create("4");
    node_t * p_n5 = node_create("5");
    node_t * p_n6 = node_create("6");

    if ((NULL == p_n1) ||
        (NULL == p_n2) ||
        (NULL == p_n3) ||
        (NULL == p_n4) ||
        (NULL == p_n5) ||
        (NULL == p_n6))
    {
        printf("create\n");
        return 1;
    }

   if ((-1 == node_adopt(p_n1, p_n2)) ||
       (node_adopt(p_n1, p_n3)) ||
       (node_adopt(p_n2, p_n4)) ||
       (node_adopt(p_n3, p_n5)) ||
       (node_adopt(p_n3, p_n6)))
    {
        printf("adopt\n");
        return 1;
    }

    bfs(p_n1);

    if ((-1 == node_destroy(p_n1)) ||
        (-1 == node_destroy(p_n2)) ||
        (-1 == node_destroy(p_n3)) ||
        (-1 == node_destroy(p_n4)) ||
        (-1 == node_destroy(p_n5)) ||
        (-1 == node_destroy(p_n6)))
    {
        printf("destroy\n");
        return 1;
    }

    printf("Exited with success\n");
    return 0;
}

/***   end of file   ***/
