#ifndef CATL_LINKED_LIST_H
#define CATL_LINKED_LIST_H

#include "catl/catl_internal/catl_exit_status.h"
#include <stddef.h>

typedef struct catl_linked_list_node_t{
  void* data;
  struct catl_linked_list_node_t* previous;
  struct catl_linked_list_node_t* next;
} catl_linked_list_node_t;

typedef struct {
  catl_linked_list_node_t* head;
  catl_linked_list_node_t* tail;
  size_t length;
  size_t data_size;
  void (* delete_function )(void*);
} catl_linked_list_t;

/**
 * @brief  Create a new linked list
 * @details  The memory must be freed by catl_linked_list_destroy()
 *           Uses free() if delete_function == NULL
 * param data_size  Size of data
 * @param delete_function  Pointer to function used by catl_linked_list_destroy() and catl_linked_list_delete()
 * @return  catl_linked_list_t pointer or NULL if failed to allocate memory
 */
catl_linked_list_t* catl_linked_list_create(size_t size, void (* delete_function )(void*));

/**
 * @brief  Frees the memory allocated by catl_linked_list_create()
 * @details  This function uses list->delete_function to free each node's data
 * @param list  Pointer to the list to be freed
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the list memory was successfully freed
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 */
CatlExitStatus catl_linked_list_destroy(catl_linked_list_t* list);

/**
 * @brief  Push data to the back of the list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the node was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_linked_list_pushback(catl_linked_list_t* list, void* data);

/**
 * @brief  Push data to the front of the list
 * @param list  Pointer to the list that will be affected
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the node was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 */
CatlExitStatus catl_linked_list_pushfront(catl_linked_list_t* list, void* data);

/**
 * @brief  Insert a node into the list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the node that will be added into the list
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the node was successfully inserted
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds
 */
CatlExitStatus catl_linked_list_insert(catl_linked_list_t* list, size_t idx, void* data);

/**
 * @brief  Delete a node from the list
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the node that will be deleted from the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the node in the index was successfully deleted
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_linked_list_delete(catl_linked_list_t* list, size_t idx);

/**
 * @brief  Set data to a linked list item
 * @param list  Pointer to the list that will be affected
 * @param idx  Index of the data that will be modified
 * @param data  Address to data to be copied into the list
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the data in the index was successfully set
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if list or data pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the index is out of bounds.
 */
CatlExitStatus catl_linked_list_set(catl_linked_list_t* list, size_t idx, void* data);

/**
 * @brief  Get data from a linked list item
 * @param list  Pointer to the list that will be accessed
 * @param idx  Index of the data to be returned
 * @return void* pointer or NULL if list == NULL or index is out of bounds
 */
void* catl_linked_list_get(catl_linked_list_t* list, size_t idx);

#endif // !CATL_LINKED_LIST_H
