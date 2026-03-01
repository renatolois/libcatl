#ifndef CATL_ARRAY_LIST_H
#define CATL_ARRAY_LIST_H

#include "catl/catl_internal/catl_exit_status.h"
#include <stddef.h>

#define CATL_ARRAY_LIST_INITIAL_CAPACITY 8

typedef struct {
  void** array;
  size_t length;
  size_t capacity;
  size_t data_size;
  void (* delete_function )(void*);
} catl_array_list_t;

/**
 * @brief  Create a new array list
 * @param data_size  Size of data
 * @param delete_function  Pointer to function used by catl_array_list_destroy() and catl_array_list_delete()
 * @param initial_capacity  Initial capacity of the array. Set 0 to use defautl (typically 8)
 * @details  Uses free() if delete_function == NULL
 * @return  catl_array_list_t pointer or NULL if failed to allocate memory
 */
catl_array_list_t* catl_array_list_create(size_t data_size, void (* delete_function )(void*), size_t initial_max_lenght);

/**
 * @brief  Frees the memory allocated by catl_array_list_create()
 * @details  This function uses list->delete_function to free array data
 * @param list  Pointer to the list to be freed
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the list memory was successfully freed
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 */
CatlExitStatus catl_array_list_destroy(catl_array_list_t* list);

/**
 * @brief  Push data to the back of the list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_array_list_pushback(catl_array_list_t* list, void* data);

/**
 * @brief  Push data to the front of the list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_array_list_pushfront(catl_array_list_t* list, void* data);

/**
 * @brief  Insert data into the list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index that data will be added into the list
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data was successfully inserted
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_array_list_insert(catl_array_list_t* list, size_t idx, void* data);

/**
 * @brief  Delete data from the list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the data that will be deleted from the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data at the index was successfully deleted
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_array_list_delete(catl_array_list_t* list, size_t idx);

/**
 * @brief  Set data to an array item
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the data that will be modified
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data at the index was successfully set
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_array_list_set(catl_array_list_t* list, size_t idx, void* data);

/**
 * @brief  Get data from an array item
 * @param list  Pointer to the list that will be accessed
 * @param idx  Index of the data pointer that will be returned
 * @return void* pointer or NULL if list == NULL or index is out of bounds
 */
void* catl_array_list_get(catl_array_list_t* list, size_t idx);

#endif // CATL_ARRAY_LIST_H
