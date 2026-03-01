#include "catl/linked-list/catl_linked_list.h"

#include "stdlib.h"
#include "string.h"
#include <stddef.h>

// return NULL if failed to allocate memory
// assumes data != NULL and data_size > 0
static catl_linked_list_node_t* catl_linked_list_node_create(void* data, size_t data_size) {
  catl_linked_list_node_t* node = (catl_linked_list_node_t*) malloc(sizeof(catl_linked_list_node_t));
  if(!node) return NULL;
  node->data = malloc(data_size);
  if(!node->data) {
    free(node);
    return NULL;
  }
  memcpy(node->data, data, data_size);
  node->next = node->previous = NULL;
  return node;
}

catl_linked_list_t* catl_linked_list_create(size_t size, void (* delete_function )(void*)) {
  catl_linked_list_t* list = (catl_linked_list_t*) malloc(sizeof(catl_linked_list_t));
  if(!list) return NULL;
  list->head = list->tail = NULL;
  list->length = 0;
  list->delete_function = delete_function ? delete_function : free;
  list->data_size = size;
  return list;
}

CatlExitStatus catl_linked_list_destroy(catl_linked_list_t* list) {
  if(!list) return CATL_STATUS_INVALID_MEMORY;
  catl_linked_list_node_t* current_node = list->head;
  while(current_node) {     
    catl_linked_list_node_t* next_node = current_node->next;
    if(current_node->data) list->delete_function(current_node->data);
    free(current_node);
    current_node = next_node;
  }
  free(list);
  return CATL_STATUS_OK;
}

CatlExitStatus catl_linked_list_pushback(catl_linked_list_t* list, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  catl_linked_list_node_t* node = catl_linked_list_node_create(data, list->data_size);
  if(!node) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  node->next = NULL;
  if(list->tail == NULL) {
    node->previous = NULL;
    list->head = list->tail = node;
  } else {
    node->previous = list->tail;
    list->tail->next = node;
    list->tail = node;
  }
  list->length++;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_linked_list_pushfront(catl_linked_list_t* list, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  catl_linked_list_node_t* node = catl_linked_list_node_create(data, list->data_size);
  if(!node) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  node->previous = NULL;
  if(list->head == NULL) {
    node->next = NULL;
    list->head = list->tail = node;
  } else {
    node->next = list->head;
    list->head->previous = node;
    list->head = node;
  }
  list->length++;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_linked_list_insert(catl_linked_list_t* list, size_t idx, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(idx == 0) {
    return catl_linked_list_pushfront(list, data);
  } else if(idx == list->length) {
    return catl_linked_list_pushback(list, data);
  } else if(idx > list->length) {
    return CATL_STATUS_INVALID_POSITION;
  }

  catl_linked_list_node_t* node = catl_linked_list_node_create(data, list->data_size);
  if(!node) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;

  catl_linked_list_node_t* current_node = list->head;
  for (size_t i = 0; i < idx - 1; i++) {
    current_node = current_node->next;
  }

  current_node->next->previous = node;
  node->next = current_node->next;
  node->previous = current_node;
  current_node->next = node;
  list->length++;
  
  return CATL_STATUS_OK;
}

CatlExitStatus catl_linked_list_delete(catl_linked_list_t* list, size_t idx) {
  if(!list) return CATL_STATUS_INVALID_MEMORY;
  if(idx >= list->length) return CATL_STATUS_INVALID_POSITION;
  catl_linked_list_node_t* current_node = list->head;
  while(idx-- != 0) {
    current_node = current_node->next;
  }
  if(current_node->data) list->delete_function(current_node->data);
  if(current_node != list->tail) {
    current_node->next->previous = current_node->previous;
  } else {
    list->tail = current_node->previous;
  }
  
  if(current_node != list->head) {
    current_node->previous->next = current_node->next;
  } else {
    list->head = current_node->next;
  }
  free(current_node);
  list->length--;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_linked_list_set(catl_linked_list_t* list, size_t idx, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(idx >= list->length) return CATL_STATUS_INVALID_POSITION;
  void* new_data = malloc(list->data_size);
  if(!new_data) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  memcpy(new_data, data, list->data_size);
  catl_linked_list_node_t* current_node = list->head;
    while(idx-- != 0) {
    current_node = current_node->next;
  }
  if(current_node->data) list->delete_function(current_node->data);
  current_node->data = new_data;
  return CATL_STATUS_OK;
}

void* catl_linked_list_get(catl_linked_list_t* list, size_t idx) {
  if(!list) return NULL;
  if(idx >= list->length) return NULL;
  catl_linked_list_node_t* current_node = list->head;
    while(idx-- != 0) {
    current_node = current_node->next;
  }
  return current_node->data;
}
