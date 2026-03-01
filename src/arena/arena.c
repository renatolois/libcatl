#include "catl/arena/arena.h"
#include "catl/catl_internal/catl_exit_status.h"
#include <stdlib.h>
#include <stdint.h>

catl_arena_t* catl_arena_create(size_t data_size, size_t length) {
  if(length != 0 && data_size > SIZE_MAX / length) return NULL;
  catl_arena_t* arena = malloc(sizeof(catl_arena_t));
  if(!arena) return NULL;
  arena->capacity = length;
  arena->buffer = malloc(data_size * arena->capacity);
  if(!arena->buffer) {
    free(arena);
    return NULL;
  }
  arena->offset=0;
  return arena;
}

CatlExitStatus catl_arena_destroy(catl_arena_t* arena) {
  if(!arena) return CATL_STATUS_INVALID_MEMORY;
  if(arena->buffer) free(arena->buffer);
  free(arena);
  return CATL_STATUS_OK;
}

void* catl_arena_alloc(catl_arena_t* arena, size_t data_size, size_t length) {
  if(arena == NULL ||
     data_size == 0 ||
     length > (arena->capacity - arena->offset) / data_size)
  {
    return NULL;
  }
  void* ptr = (unsigned char*) arena->buffer + arena->offset;
  arena->offset += length * data_size;
  return ptr;
}
