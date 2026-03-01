#include "catl/array-list/catl_array_list.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Duplicate list capacity by 2; return CATL_STATUS_OVERFLOW, CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY, or CATL_STATUS_OK
static CatlExitStatus catl_array_list_duplicate_capacity(catl_array_list_t* list) {
  if(list->capacity > SIZE_MAX / 2) {
    return CATL_STATUS_OVERFLOW;
  }
  size_t new_capacity = list->capacity * 2;
  void** new_array = realloc(list->array, new_capacity * sizeof(void*));
  if(!new_array) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  list->array = new_array;
  list->capacity = new_capacity;
  return CATL_STATUS_OK;
}

catl_array_list_t* catl_array_list_create(size_t data_size, void (* delete_function )(void*), size_t initial_capacity) {
  catl_array_list_t* list = (catl_array_list_t*) malloc(sizeof(catl_array_list_t));
  if(!list) return NULL;
  if (initial_capacity == 0) {
    list->capacity = CATL_ARRAY_LIST_INITIAL_CAPACITY;
  } else {
    list->capacity = initial_capacity;
  }
  list->length = 0;
  list->data_size = data_size;
  list->delete_function = delete_function ? delete_function : free;
  list->array = (void**) malloc(sizeof(void*) * list->capacity);
  if(!list->array) {
    free(list);
    return NULL;
  }
  return list;
}

CatlExitStatus catl_array_list_destroy(catl_array_list_t* list) {
  if(!list) return CATL_STATUS_INVALID_MEMORY;
  for(size_t i=0; i < list->length; i++) {
    if(list->array[i]) list->delete_function(list->array[i]);
  }
  free(list->array);
  free(list);
  return CATL_STATUS_OK;
}

CatlExitStatus catl_array_list_pushback(catl_array_list_t* list, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(list->length >= list->capacity) {
    CatlExitStatus status = catl_array_list_duplicate_capacity(list);
    if(status != CATL_STATUS_OK) return status;
  }
  void* new_data = malloc(list->data_size);
  if(!new_data) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  memcpy(new_data, data, list->data_size);
  list->array[list->length] = new_data;
  list->length++;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_array_list_pushfront(catl_array_list_t* list, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(list->length >= list->capacity) {
    CatlExitStatus status = catl_array_list_duplicate_capacity(list);
    if(status != CATL_STATUS_OK) return status;
  }
  void* new_data = malloc(list->data_size);
  if(!new_data) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  memcpy(new_data, data, list->data_size);
  memmove(list->array + 1, list->array, list->length * sizeof(void*));
  list->array[0] = new_data;
  list->length++;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_array_list_insert(catl_array_list_t* list, size_t idx, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(idx > list->length) return CATL_STATUS_INVALID_POSITION;
  if(list->length >= list->capacity) {
    CatlExitStatus status = catl_array_list_duplicate_capacity(list);
    if(status != CATL_STATUS_OK) return status;
  }
  void* new_data = malloc(list->data_size);
  if(!new_data) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  memcpy(new_data, data, list->data_size);
  
  memmove(list->array + 1 + idx, list->array + idx, (list->length - idx) * sizeof(void*));
  list->array[idx] = new_data;
  list->length++;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_array_list_delete(catl_array_list_t* list, size_t idx) {
  if(!list) return CATL_STATUS_INVALID_MEMORY;
  if(idx >= list->length) return CATL_STATUS_INVALID_POSITION;
  if(list->array[idx]) list->delete_function(list->array[idx]);
  memmove(list->array+idx, list->array+idx + 1, (list->length - idx - 1) * sizeof(void*));
  list->length--;
  return CATL_STATUS_OK;
}

CatlExitStatus catl_array_list_set(catl_array_list_t* list, size_t idx, void* data) {
  if(!list || !data) return CATL_STATUS_INVALID_MEMORY;
  if(idx >= list->length) return CATL_STATUS_INVALID_POSITION;
  void* new_data = malloc(list->data_size);
  if(!new_data) return CATL_STATUS_FAILED_TO_ALLOCATE_MEMORY;
  memcpy(new_data, data, list->data_size);
  if(list->array[idx]) list->delete_function(list->array[idx]);
  list->array[idx] = new_data;
  return CATL_STATUS_OK;
}

void* catl_array_list_get(catl_array_list_t* list, size_t idx) {
  if(!list) return NULL;
  if(idx >= list->length) return NULL;
  return list->array[idx];
}
