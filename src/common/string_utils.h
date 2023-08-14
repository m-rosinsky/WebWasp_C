/*!
 * @file src/common/string_utils.h
 *
 * @brief This file contains various string utility functions.
 */

#ifndef WW_COMMON_STRING_UTILS_H
#define WW_COMMON_STRING_UTILS_H

#include <stdlib.h>

/*!
 * @brief This defines a string split context. It is used to store
 *          the results of running string_split.
 * 
 * @param len The number of substrings in pp_substrs
 * @param pp_substrs The array holding the substrings.
 */
typedef struct _string_split
{
    size_t len;
    char ** pp_substrs;
} string_split_t;

/*!
 * @brief This function splits a string into its respective substrings
 *          on a given delimiter.
 * 
 * @param[in] p_str The string to split.
 * @param[in] p_del The delimiter to split p_str on. Provide NULL to split
 *                      on spaces.
 * 
 * @return Pointer to new string_split_t context. NULL on error.
 * 
 *          On success, the caller must call string_split_destroy
 *              or string_split_clear to clean memory.
 */
string_split_t *
string_split (const char * p_str, const char * p_del);

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
string_split_clear (string_split_t * p_split);

/*!
 * @brief This function clears a string split context and free's the
 *          context itself.
 * 
 * @param[in/out] p_split The string split context.
 * 
 * @return 0 on success, -1 on error.
 */
int
string_split_destroy (string_split_t * p_split);

#endif // WW_COMMON_STRING_UTILS_H

/***   end of file   ***/
