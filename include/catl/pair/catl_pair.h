#ifndef CATL_PAIR_H
#define CATL_PAIR_H

#include "catl/catl_internal/catl_exit_status.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct {
  void* first;
  void* second;
  size_t size_first;
  size_t size_second;
  void (* first_delete_function)(void*);
  void (* second_delete_function)(void*);
} catl_pair_t;

/**
 * @brief  Create a new pair
 * @details  Allocates memory for a new pair. Must be freed with catl_pair_destroy()
 * @param size_first   Size in bytes of the first element
 * @param size_second  Size in bytes of the second element
 * @param first_delete_function  Function to free first element (uses free() if NULL)
 * @param second_delete_function Function to free second element (uses free() if NULL)
 * @return Pointer to catl_pair_t or NULL if allocation failed
 */
catl_pair_t* catl_pair_create(
  size_t size_first,
  size_t size_second,
  void (* first_delete_function)(void*),
  void (* second_delete_function)(void*)
);

/**
 * @brief  Destroy a pair
 * @details  Frees memory of the pair and its elements using the delete functions
 * @param pair  Pointer to the pair
 * @return CATL_STATUS_OK if successful, CATL_STATUS_INVALID_MEMORY if pair is NULL
 */
CatlExitStatus catl_pair_destroy(catl_pair_t* pair);

/**
 * @brief  Get the first element of the pair
 * @param pair  Pointer to the pair
 * @return Pointer to the first element, or NULL if pair is NULL or first not set
 */
static inline void* catl_pair_get_first(catl_pair_t* pair);


/**
 * @brief  Get the second element of the pair
 * @param pair  Pointer to the pair
 * @return Pointer to the second element, or NULL if pair is NULL or second not set
 */
static inline void* catl_pair_get_second(catl_pair_t* pair);

/**
 * @brief  Set the first element of the pair
 * @param pair  Pointer to the pair
 * @param data  Pointer to data to copy into the first element
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the element was successfully set
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if pair or data is NULL
 */
CatlExitStatus catl_pair_set_first(catl_pair_t* pair, void* data);

/**
 * @brief  Set the second element of the pair
 * @param pair  Pointer to the pair
 * @param data  Pointer to data to copy into the second element
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the element was successfully set
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if pair or data is NULL
 */
CatlExitStatus catl_pair_set_second(catl_pair_t* pair, void* data);


// inline functiones implementation
static inline void* catl_pair_get_first(catl_pair_t* pair) { 
  return (pair && pair->first) ? pair->first : NULL;
}

static inline void* catl_pair_get_second(catl_pair_t* pair) {
  return (pair && pair->second) ? pair->second : NULL;
}

#endif // !CATL_PAIR_H
