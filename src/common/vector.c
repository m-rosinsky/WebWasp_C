/*!
 * @file vector.c
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

#include "vector.h"

/*!
 * @brief This function instantiates a new vector context.
 *
 * @return Pointer to new vector context. NULL on error.
 */
vector_t *
vector_create (void)
{
    vector_t * p_vector = calloc(1, sizeof(vector_t));
    if (NULL == p_vector)
    {
        goto EXIT;
    }
    p_vector->pp_data = NULL;
    p_vector->size = 0;
    p_vector->cap = 0;
    
    EXIT:
        return p_vector;
}

/*!
 * @brief This function destroys a vector context.
 *
 *          Any data referenced by the vector will NOT be freed by
 *              this function. The client is responsible for creation
 *              and deletion of any data.
 *
 *          This function only destroys the vector container itself.
 *
 * @param[in/out] p_vector The vector context.
 *
 * @return No return value expected.
 */
void
vector_destroy (vector_t * p_vector)
{
    if ((NULL == p_vector) ||
        (NULL == p_vector->pp_data))
    {
        goto EXIT;
    }
    
    // Free the data reference array.
    free(p_vector->pp_data);
    p_vector->pp_data = NULL;
    
    EXIT:
        if (NULL != p_vector)
        {
            free(p_vector);
            p_vector = NULL;
        }
}

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
vector_reserve (vector_t * p_vector, const size_t amt)
{
    int status = -1;
    if (NULL == p_vector)
    {
        goto EXIT;
    }
    
    // Perform a reallocation of the vector's data array.
    size_t new_size = (p_vector->cap + amt) * sizeof(void *);
    p_vector->pp_data = realloc(p_vector->pp_data, new_size);
    
    if (NULL == p_vector->pp_data)
    {
        goto EXIT;
    }
    
    // Adjust the vector's capacity parameter.
    p_vector->cap += amt;
    
    status = 0;
    
    EXIT:
        return status;
}

/*!
 * @brief This function appends an element to the back of the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in/out] p_data The data reference.
 *
 * @return 0 on success, -1 on error.
 */
int
vector_push_back (vector_t * p_vector, void * p_data)
{
    int status = -1;
    if ((NULL == p_vector) ||
        (NULL == p_data))
    {
        goto EXIT;
    }
    
    // If the vector is full, allocate more space.
    if ((p_vector->size >= p_vector->cap) &&
        (-1 == vector_reserve(p_vector, 1)))
    {
        goto EXIT;
    }
    
    // Append the new data.
    p_vector->pp_data[p_vector->size] = p_data;
    
    // Increase the vector's size parameter.
    p_vector->size++;
    
    status = 0;
    
    EXIT:
        return status;
}

/*!
 * @brief This function prepends an element to the front of the vector.
 *
 * @param[in/out] p_vector The vector context.
 * @param[in/out] p_data The data reference.
 *
 * @return 0 on success, -1 on error.
 */
int
vector_push_front (vector_t * p_vector, void * p_data)
{
    int status = -1;
    if ((NULL == p_vector) ||
        (NULL == p_data))
    {
        goto EXIT;
    }
    
    // If the vector is full, allocate more space.
    if ((p_vector->size >= p_vector->cap) &&
        (-1 == vector_reserve(p_vector, 1)))
    {
        goto EXIT;
    }
    
    // Shift all elements of the vector back one position.
    for (size_t idx = p_vector->size; idx > 0; --idx)
    {
        p_vector->pp_data[idx] = p_vector->pp_data[idx-1];
    }
    
    // Prepend the new data.
    p_vector->pp_data[0] = p_data;
    
    // Increase the vector's size parameter.
    p_vector->size++;
    
    status = 0;
    
    EXIT:
        return status;
}

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
vector_pop_back (vector_t * p_vector)
{
    void * p_result = NULL;
    if ((NULL == p_vector) ||
        (NULL == p_vector->pp_data) ||
        (0 == p_vector->size))
    {
        goto EXIT;
    }
    
    // Save the reference to the data of the last element in the vector.
    p_result = p_vector->pp_data[p_vector->size - 1];
    
    // Remove the element by simply decrementing the size. No
    // reallocations need occur.
    p_vector->size--;
    
    EXIT:
        return p_result;
}

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
vector_pop_front (vector_t * p_vector)
{
    void * p_result = NULL;
    if ((NULL == p_vector) ||
        (NULL == p_vector->pp_data) ||
        (0 == p_vector->size))
    {
        goto EXIT;
    }
    
    // Save the reference to the data of the last element in the vector.
    p_result = p_vector->pp_data[0];
    
    // Shift all elements of the vector forward one position.
    for (size_t idx = 0; idx < p_vector->size - 1; ++idx)
    {
        p_vector->pp_data[idx] = p_vector->pp_data[idx + 1];
    }
    
    // Remove the element by simply decrementing the size. No
    // reallocations need occur.
    p_vector->size--;
    
    EXIT:
        return p_result;
}

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
vector_at (vector_t * p_vector, const size_t idx)
{
    void * p_result = NULL;
    if ((NULL == p_vector) ||
        (NULL == p_vector->pp_data) ||
        (idx >= p_vector->size))
    {
        goto EXIT;
    }
    
    // Save the element at the specified index.
    p_result = p_vector->pp_data[idx];
    
    EXIT:
        return p_result;
}

/***   end of file   ***/