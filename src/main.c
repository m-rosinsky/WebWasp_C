/*!
 * @file main.c
 *
 * @brief This is the main file for the program.
 */

#include <stdio.h>

#include "console/console.h"

/*!
 * @brief This is the main entry point of the program.
 *
 * @return The status of the program.
 */
int
main ()
{
    console_t * p_console = console_create();
    if (NULL == p_console)
    {
        printf("create\n");
        return 1;
    }

    console_run(p_console);

    if (-1 == console_destroy(p_console))
    {
        printf("destroy\n");
        return 1;
    }

    printf("success\n");
    return 0;
}

/***   end of file   ***/
