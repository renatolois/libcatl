#ifndef CATL_ARENA_H
#define CATL_ARENA_H

#include "catl/catl_internal/catl_exit_status.h"
#include <stddef.h>

typedef struct catl_arena_t {
  void* buffer;
  size_t capacity;
  size_t offset;
} catl_arena_t;

catl_arena_t* catl_arena_create(size_t data_size, size_t length);
CatlExitStatus catl_arena_destroy(catl_arena_t* arena);
void* catl_arena_alloc(catl_arena_t* arena, size_t data_size, size_t length);

#endif //  !CASTL_ARENA_H
