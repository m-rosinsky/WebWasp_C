/*!
 * @file src/common/string_utils.c
 *
 * @brief This file contains various string utility functions.
 */

#include <string.h>

#include "string_utils.h"

/*!
 * @brief This function splits a string into its respective substrings
 *          on a given delimiter.
 * 
 * @param[in] p_str The string to split.
 * @param[in] p_del The delimiter to split p_str on.
 * 
 * @return Pointer to new string_split_t context. NULL on error.
 * 
 *          On success, the caller must call string_split_destroy
 *              or string_split_clear to clean memory.
 */
string_split_t *
string_split (const char * p_str, const char * p_del)
{
    int status = -1;
    string_split_t * p_split = NULL;
    char * p_cpy = NULL;
    if (NULL == p_str)
    {
        goto EXIT;
    }

    // If the given delimiter is NULL, default it to a space.
    const char * p_delim = p_del;
    if (NULL == p_delim)
    {
        p_delim = " ";
    }

    // Copy the string.
    size_t str_len = strlen(p_str);
    p_cpy = calloc(str_len + 1, sizeof(char));
    if (NULL == p_cpy)
    {
        goto EXIT;
    }
    strcpy(p_cpy, p_str);

    // Create the string split context.
    p_split = calloc(1, sizeof(string_split_t));
    if (NULL == p_split)
    {
        goto EXIT;
    }
    p_split->len = 0;
    p_split->pp_substrs = NULL;

    // Perform split using strtok loop.
    char * p_token = strtok(p_cpy, p_delim);
    while (NULL != p_token)
    {
        // Allocate memory for current substring.
        char * p_sub = calloc(strlen(p_token) + 1, sizeof(char));
        if (NULL == p_sub)
        {
            goto EXIT;
        }
        strcpy(p_sub, p_token);

        // Add substring to context.
        p_split->pp_substrs = realloc(p_split->pp_substrs, (p_split->len + 1) * sizeof(char *));
        p_split->pp_substrs[p_split->len] = p_sub;

        // Increment context length.
        p_split->len++;

        // Get next token.
        p_token = strtok(NULL, p_delim);
    }

    status = 0;

    EXIT:
        // Clean string copy.
        if (NULL != p_cpy)
        {
            free(p_cpy);
            p_cpy = NULL;
        }
        // On fail, destroy context.
        if ((-1 == status) &&
            (NULL != p_split))
        {
            string_split_destroy(p_split);
            p_split = NULL;
        }
        return p_split;
}

/*!
 * @brief This function free's all substrings contained in a
 *          string_split_t context, but does not free the context
 *          itself.
 * 
 *          This is useful if the context will be reused in another
 *              string_split operation.
 * 
 * @param[in/out] p_split The string split context.
 *
 * @return 0 on success, -1 on error.
 */
int
string_split_clear (string_split_t * p_split)
{
    int status = -1;
    if (NULL == p_split)
    {
        goto EXIT;
    }

    // Destroy individual substrings in array.
    for (size_t idx = 0; idx < p_split->len; ++idx)
    {
        free(p_split->pp_substrs[idx]);
        p_split->pp_substrs[idx] = NULL;
    }

    // Free substring array.
    free(p_split->pp_substrs);
    p_split->pp_substrs = NULL;

    // Set length to 0.
    p_split->len = 0;

    status = 0;

    EXIT:
        return status;
}

/*!
 * @brief This function clears a string split context and free's the
 *          context itself.
 * 
 * @param[in/out] p_split The string split context.
 * 
 * @return 0 on success, -1 on error.
 */
int
string_split_destroy (string_split_t * p_split)
{
    int status = -1;
    if (NULL == p_split)
    {
        goto EXIT;
    }

    // Clear context.
    if (-1 == string_split_clear(p_split))
    {
        goto EXIT;
    }

    status = 0;

    EXIT:
        if (NULL != p_split)
        {
            free(p_split);
            p_split = NULL;
        }
        return status;
}

/***   end of file   ***/
