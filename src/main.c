/*!
 * @file main.c
 *
 * @brief This is the main file for the program.
 */

#include <stdio.h>

#include "console/console.h"

/*!
 * @brief This is a temporary function for the initial commit.
 *
 * @return The status of the program.
 */
int
main ()
{
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

    printf("Exited with success\n");
    return 0;
}

/***   end of file   ***/
