/*!
 * @file vector.h
 *
 * @brief This file contains a generic vector implementation.
 *
 *          The vector is a contiguous, dynamic array of references
 *              to data. It provides O(1) random access.
 *
 *          Reallocations of memory occur automatically when the
 *              number of elements in the vector exceed the allocated
 *              space.
 *
 *          Functions included are as follows:
 *
 *              - vector_create()
 *              - vector_destroy()
 *              - vector_reserve()
 *              - vector_push_back()
 *              - vector_push_front()
 *              - vector_pop_back()
 *              - vector_pop_front()
 *              - vector_at()
 */

#ifndef _WEBWASP_SRC_COMMON_VECTOR_H
#define _WEBWASP_SRC_COMMON_VECTOR_H

#include <stdlib.h>

/*!
 * @brief This datatype defines a vector context.
 *
 * @param pp_data The array containing the data references.
 * @param size The number of elements in the vector.
 * @param cap The number of elements the vector has allocated space for.
 */
typedef struct _vector
{
    void ** pp_data;
    size_t size;
    size_t cap;
} vector_t;

/*!
 * @brief This function instantiates a new vector context.
 *
 * @return Pointer to new vector context. NULL on error.
 */
vector_t *
vector_create (void);

/*!
 * @brief This function destroys a vector context.
 *
 * @param[in/out] p_vector The vector context.
 *
 * @return No return value expected.
 */
void
vector_destroy (vector_t * p_vector);

/*!
 * @brief This function allocates space for a specified number of elements
 *          in the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in] amt The number of elements to allocate space for.
 *
 * @return 0 on success, -1 on error.
 */
int
vector_reserve (vector_t * p_vector, const size_t amt);

/*!
 * @brief This function appends an element to the back of the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in/out] p_data The data reference.
 *
 * @return 0 on success, -1 on error.
 */
int
vector_push_back (vector_t * p_vector, void * p_data);

/*!
 * @brief This function prepends an element to the front of the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in/out] p_data The data reference.
 *
 * @return 0 on success, -1 on error.
 */
int
vector_push_front (vector_t * p_vector, void * p_data);

/*!
 * @brief This function removes the last element from the vector and
 *          returns a reference to the data.
 *
 * @param[in/out] p_vector The vector context.
 *
 * @return Pointer to the referenced data of the removed element.
 *          NULL on error or empty vector.
 */
void *
vector_pop_back (vector_t * p_vector);

/*!
 * @brief This function removes the first element from the vector and
 *          returns a reference to the data.
 *
 * @param[in/out] p_vector The vector context.
 *
 * @return Pointer to the referenced data of the removed element.
 *          NULL on error or empty vector.
 */
void *
vector_pop_front (vector_t * p_vector);

/*!
 * @brief This function returns the data reference at a specified
 *          index in the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in] idx The index of the reference to return.
 *
 * @return Pointer to the referenced data of the element at the specified
 *          index. NULL on error or index out of range.
 */
void *
vector_at (vector_t * p_vector, const size_t idx);

#endif // _WEBWASP_SRC_COMMON_VECTOR_H

/***   end of file   ***/