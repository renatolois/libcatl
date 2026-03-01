#include "array-list/catl_array_list.h"
#include <stdio.h>

int main() {
  catl_array_list_t* array_list = catl_array_list_create(sizeof(int), NULL, 0);
  catl_array_list_pushback(array_list, (void*)&(int){1});
  catl_array_list_pushback(array_list, (void*)&(int){2});
  catl_array_list_pushback(array_list, (void*)&(int){3});
  catl_array_list_pushback(array_list, (void*)&(int){4});
  catl_array_list_pushback(array_list, (void*)&(int){5});
  catl_array_list_pushback(array_list, (void*)&(int){6});
  catl_array_list_pushback(array_list, (void*)&(int){7});
  catl_array_list_pushback(array_list, (void*)&(int){8});
  catl_array_list_pushback(array_list, (void*)&(int){9});
  catl_array_list_pushback(array_list, (void*)&(int){10});
  catl_array_list_pushback(array_list, (void*)&(int){11});
  catl_array_list_pushback(array_list, (void*)&(int){12});
  catl_array_list_pushback(array_list, (void*)&(int){13});
  catl_array_list_pushback(array_list, (void*)&(int){14});
  catl_array_list_pushback(array_list, (void*)&(int){15});
  catl_array_list_pushback(array_list, (void*)&(int){16});
  catl_array_list_pushback(array_list, (void*)&(int){17});
  catl_array_list_pushback(array_list, (void*)&(int){18});
  catl_array_list_pushback(array_list, (void*)&(int){19});

  for(int i=0; i<18; i++) {
    printf("pos %d: ( %d )\n", i, *(int*)catl_array_list_get(array_list, i));
  }
}
