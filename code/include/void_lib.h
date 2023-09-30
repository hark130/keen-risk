#include <stdlib.h>  // size_t

/*
 *	Concatenate buf2 onto buf1 in a heap-allocated buffer of size size1 + size2.
 *
 *	The caller is responsible for calling void_free() on the heap-allocated
 *	buffer returned by this function.  Buf1 and buf2 will not be modified in
 *	the execution of this function.  Either buf1 or buf2, but not both, may be
 *	NULL when this function is called.  Any slack space in the dynamic buffer
 *	will be zeroized. 
 *
 *	ARGS:
 *		buf1_ptr - Address of the original buffer
 *		size1 - Size of buf1
 *		buf2_ptr - Address of the buffer to append to buf1
 *		size2 - Size of buf2
 *
 *	RETURNS: Dynamic memory address to a buffer of size equal to size1 + size2
 *	that contains buf1 && buf2.
 */
void *void_cat(void *buf1_ptr, size_t size1, void *buf2_ptr, size_t size2);


/*
 *	Zeroize old_buf and free it.
 *	
 *	ARGS:
 *		old_buf_ptr - Memory address that was returned by void_cat().
 *		buf_size - Size of old_buf to set to 0x0.
 *
 *	RETURNS: 0 on success.  -1 on bad input.  Errno on failure.
 */
int void_free(void *old_buf_ptr, size_t buf_size);


/*
 *	Find needle in haystack.
 *
 *	The haystack_ptr and the needle_ptr may not be the same memory address.
 *
 *	ARGS:
 *		haystack_ptr - Address of the buffer to search
 *		hsize - Size of the haystack bufffer
 *		needle_ptr - Address of the buffer containing data to find in haystack
 *		nsize - Size of needle
 *
 *	RETURNS: If needle is found in haystack, the haystack address offset.
 *	Any address returned will found in haystack.  If not found,
 *	or error, returns NULL.
 */
void *void_search(void *haystack_ptr, size_t hsize, void *needle_ptr, size_t nsize);
