#include "catl/linked-list/catl_unrolled_linked_list.h"


catl_unrolled_linked_list_t* catl_unrolled_linked_list_create(size_t data_size, void (* delete_function )(void*)) {
  catl_unrolled_linked_list_t* u_list = malloc(sizeof(catl_unrolled_linked_list_t));
  if(!u_list) return NULL;
  u_list->blocks = catl_linked_list_create()
  // i will see this later.
}
