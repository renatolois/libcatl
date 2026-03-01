#include "catl/hash-algorithms/djb2.h"

size_t castl_hash_djb2(char* data, size_t length) {
  if(!data) return 0;
  size_t hash = 5381;
  unsigned char *current = (unsigned char*) data;
  if(length == 0) {
    while(*current) {
      hash = 33 * hash + *current;
      current++;
    }
  } else {
    for(size_t i=0; i<length; i++) {
      hash = *current + hash * 33;
      current++;
    }
  }
  return hash;
}
