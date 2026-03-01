#include "catl/stack/catl_stack.h"

#include <stddef.h>
#include <stdlib.h>

catl_stack_t* catl_stack_create(size_t data_size, void (* delete_function )(void*)) {
  catl_stack_t* stack = (catl_stack_t*) malloc(sizeof(catl_stack_t));
  if(!stack) return NULL;
  stack->list = catl_linked_list_create(data_size, delete_function);
  if(!stack->list) {
    free(stack);
    return NULL;
  }
  stack->length = 0;
  return stack;
}

CatlExitStatus catl_stack_destroy(catl_stack_t* stack) {
  if(!stack) return CATL_STATUS_INVALID_MEMORY;
  CatlExitStatus status = catl_linked_list_destroy(stack->list);
  if(status != CATL_STATUS_OK) return status;
  free(stack);
  return CATL_STATUS_OK;
}

bool catl_stack_is_empty(catl_stack_t* stack) {
  return stack->list->head == NULL;
}

CatlExitStatus catl_stack_pop(catl_stack_t* stack) {
  if(!stack) return CATL_STATUS_INVALID_MEMORY;
  if(catl_stack_is_empty(stack)) return CATL_STATUS_INVALID_MEMORY;
  if(stack->list->tail->data) stack->list->delete_function(stack->list->tail->data);
  catl_linked_list_node_t* new_tail = stack->list->tail->previous;
  free(stack->list->tail);
  stack->list->tail = new_tail;
  if(new_tail) new_tail->next = NULL;
  else stack->list->head = NULL;
  stack->list->length--;
  stack->length--;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_stack_push(catl_stack_t* stack, void* value) {
  if(!stack) return CATL_STATUS_INVALID_MEMORY;
  CatlExitStatus status = catl_linked_list_pushback(stack->list, value);
  if(status != CATL_STATUS_OK) return status;
  stack->length++;
  return status;
}

void* catl_stack_top(catl_stack_t* stack) {
  if(!stack || catl_stack_is_empty(stack)) return NULL;
  return stack->list->tail->data;
}


