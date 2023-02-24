/*
 * USAGE:
 *  size_t buffLen = 256;  // How many bytes do you need?
 *  void *hmem = give_me_memory(buffLen);  // Get some memory
 *  strncpy(hmem, "Hello, world!", buffLen - 1);  // Do something to it
 *  printf("%s is stored at %p\n", (char*)hmem, hmem);  // Use it
 *  take_my_memory(&hmem, buffLen);  // Zeroize, free, and NULLify hmem
 */

#ifndef _HARKLEMEM_
#define _HARKLEMEM_

#include <stddef.h>     // size_t

/*
 *  Purpose - Allocate a buffer of size length.
 *  Input
 *      length - The length of what you want to store.
 *  Ouput - Heap-allocated, zeroized, buffer of size length.
 *  Notes:
 *      It is the caller's responsibility to free the void* returned by this function.
 *      Prints errors to stderr.
 */
void *give_me_memory(size_t length);

/*
 *  Purpose - This function represents an attempt at wrapping memset in such a way that it will
 *      not get optimized out when memset is used on a pointer about to be free()d.
 *  Input
 *       s - Memory area to memset.
 *       c - Constant byte to set the memory area "s" to.
 *       n - Number of bytes to set.
 *  Output - A pointer to the memory area "s" on success.
 *  Notes:
 *      Prints errors to stderr.
 */
void *harkleset(void *s, int c, size_t n);

/*
 *  Purpose - Zeroize, free, and NULLify a heap-allocated buffer of size length found at oldMem.
 *  Input
 *      oldMem - A pointer to a heap-allocated pointer.
 *      length - The size of the original heap-allocated buffer.
 *  Output - None.
 *  Notes:
 *      Prints errors to stderr.
 *      The only thing that stops this function from free()ing the pointer found in oldMem is
 *          if oldMem or *oldMem are NULL.
 */
void take_my_memory(void **oldMem, size_t length);

#endif  // _HARKLEMEM_
