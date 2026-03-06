#ifndef CATL_UNROLLED_LINKED_LIST_H
#define CATL_UNROLLED_LINKED_LIST_H

#include "catl/catl_internal/catl_exit_status.h"
#include "catl/linked-list/catl_linked_list.h"
#include <stddef.h>

/* fix this !!!!!!!!!!!
typedef struct catl_unrolled_linked_list_t {
  catl_linked_list_t* blocks;
  
} catl_unrolled_linked_list_t;
*/

typedef struct catl_unrolled_linked_list_t {
  size_t block_size;
  catl_linked_list_t* blocks; 
  void (* delete_function )(void*);
} catl_unrolled_linked_list_t;

/**
 * @brief  Create a new unrolled linked list
 * @details  The memory must be freed by catl_unrolled_linked_list_destroy()
 *           Uses free() if delete_function == NULL
 * @param data_size  Size of data
 * @param delete_function  Pointer to function used by destroy() and delete()
 * @return  catl_unrolled_linked_list_t pointer or NULL if failed to allocate memory
 */
catl_unrolled_linked_list_t* catl_unrolled_linked_list_create(size_t data_size, size_t block_size, void (* delete_function )(void*));

/**
 * @brief  Frees the memory allocated by catl_unrolled_linked_list_create()
 * @details  This function uses list->delete_function to free each item's data
 * @param list  Pointer to the list to be freed
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the list memory was successfully freed
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 */
CatlExitStatus catl_unrolled_linked_list_destroy(catl_unrolled_linked_list_t* list);

/**
 * @brief  Push data to the back of the unrolled linked list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the item was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_unrolled_linked_list_pushback(catl_unrolled_linked_list_t* list, void* data);

/**
 * @brief  Push data to the front of the unrolled linked list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the item was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_unrolled_linked_list_pushfront(catl_unrolled_linked_list_t* list, void* data);

/**
 * @brief  Insert an item into the unrolled linked list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the item that will be added into the list
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the item was successfully inserted
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds
 */
CatlExitStatus catl_unrolled_linked_list_insert(catl_unrolled_linked_list_t* list, size_t idx, void* data);

/**
 * @brief  Delete an item from the unrolled linked list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the item that will be deleted from the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the item at the index was successfully deleted
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_unrolled_linked_list_delete(catl_unrolled_linked_list_t* list, size_t idx);

/**
 * @brief  Set data to an item in the unrolled linked list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the data that will be modified
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data at the index was successfully set
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_unrolled_linked_list_set(catl_unrolled_linked_list_t* list, size_t idx, void* data);

/**
 * @brief  Get data from an item in the unrolled linked list
 * @param list  Pointer to the list that will be accessed
 * @param idx  Index of the data to be returned
 * @return void* pointer or NULL if list == NULL or index is out of bounds
 */
void* catl_unrolled_linked_list_get(catl_unrolled_linked_list_t* list, size_t idx);

#endif // !CATL_UNROLLED_LINKED_LIST_H
