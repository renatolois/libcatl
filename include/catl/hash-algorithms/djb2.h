#ifndef CATL_HASH_DJB2_H
#define CATL_HASH_DJB2_H

#include <stddef.h>

/**
 * @brief  Computes a DJB2 hash for a given data buffer or null-terminated string
 * @details  If length > 0, the function hashes exactly 'length' bytes of 'data'.
 *           If length == 0, the function treats 'data' as a null-terminated string
 *           and hashes until the '\0' character is found.
 * @param data  Pointer to the data to be hashed
 * @param length  Number of bytes to hash; if 0, treats 'data' as null-terminated string
 * @return  hash value of the input data, or 0 if data pointer is NULL
 */
size_t castl_hash_djb2(char* data, size_t length);

#endif // !CATL_HASH_DJB2_H

