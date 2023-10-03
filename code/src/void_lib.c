#include <stdlib.h>  // size_t
#include <string.h>  // memcpy()


void *void_cat(void *buf1_ptr, size_t size1, void *buf2_ptr, size_t size2)
{
    void *result;
    if (size1 == 0 && size2 == 0)
    {
        result = NULL;
    }

    else if (buf1_ptr == NULL && buf2_ptr == NULL)
    {
        result = NULL;
    }

    else
    {
        result = malloc(size1 + size2);
        if (buf1_ptr != NULL)
        {
            memcpy(result, buf1_ptr, size1);
        }

        if (buf2_ptr != NULL)
        {
            memcpy(result + size1, buf2_ptr, size2);
        }
    }
    return result;
}


int void_free(void *old_buf_ptr, size_t buf_size)
{
	return 1;
}


void *void_search(void *haystack_ptr, size_t hsize, void *needle_ptr, size_t nsize)
{
	return NULL;
}
