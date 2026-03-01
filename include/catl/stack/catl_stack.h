#ifndef CATL_STACK_H
#define CATL_STACK_H

#include "catl/catl_internal/catl_exit_status.h"
#include "catl/linked-list/catl_linked_list.h"
#include <stdbool.h>

typedef struct {
  catl_linked_list_t* list;
  size_t length;
  void (* delete_function )(void*);
} catl_stack_t;

/**
 * @brief  Create a new stack
 * @details  Uses free() if delete_function == NULL
 * @param size  Size of data
 * @param delete_function  Pointer to function used by catl_stack_destroy() and catl_stack_pop()
 * @return  catl_stack_t pointer or NULL if failed to allocate memory
 */
catl_stack_t* catl_stack_create(size_t size, void (* delete_function )(void*));

/**
 * @brief  Frees the memory allocated by catl_stack_create()
 * @details  This function uses stack->delete_function to free data
 * @param list  Pointer to the stack to be freed
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the list memory was successfully freed
 *         - CATL_STATUS_INVALID_MEMORY if list pointer is NULL
 */
CatlExitStatus catl_stack_destroy(catl_stack_t* stack);

/**
 * @brief  Verify if stack is empty
 * @param list  Pointer to the stack to be verified
 * @return true if the stack is empty, false otherwise
 */
bool catl_stack_is_empty(catl_stack_t* stack);

/**
 * @brief  Removes the top element from the stack
 * @param stack  Pointer to the stack
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the element was successfully removed
 *         - CATL_STATUS_INVALID_MEMORY if stack pointer is NULL
 *         - CATL_STATUS_INVALID_POSITION if the stack is empty
 * @details  Calls stack->delete_function on the removed element if delete_function is set
 */
CatlExitStatus catl_stack_pop(catl_stack_t* stack);

/**
 * @brief  Pushes a new element onto the top of the stack
 * @param stack  Pointer to the stack
 * @param value  Pointer to the data to be added
 * @return CatlExitStatus indicating the result of the operation:
 *         - CATL_STATUS_OK if the element was successfully added
 *         - CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY if memory allocation failed
 *         - CATL_STATUS_INVALID_MEMORY if stack or value pointer is NULL
 */
CatlExitStatus catl_stack_push(catl_stack_t* stack, void* value);

/**
 * @brief  Returns a pointer to the top element of the stack without removing it
 * @param stack  Pointer to the stack
 * @return void* pointer to the top element, or NULL if stack is empty or stack pointer is NULL
 */
void* catl_stack_top(catl_stack_t* stack);

#endif //  !CATL_STACK_H

