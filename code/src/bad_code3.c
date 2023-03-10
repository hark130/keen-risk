#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy(), memset()
#include "gimme_mem.h"      // gimme_mem_malloc()
#include "mimo_wrappers.h"  // setup_mimo(), teardown_mimo()

#define BUF_SIZE 64

/*
 * Purpose - Free and memset memory
 */
void clear_mem(void *old_ptr);

/*
 * Purpose - Use malloc to allocate heap memory
 */
void* gimme_mem_malloc(size_t bufSize);

int main(void)
{
    // LOCAL VARIABLES
    char *buff = (char *)gimme_mem_malloc((BUF_SIZE * sizeof(char)) + 1);

    // COPY
    strcpy(buff, "Hello World!\n\0");

    // PRINT
    printf("%s", buff);

    // CLEAN UP
    clear_mem(buff);

    // DONE
    return 0;
}

void clear_mem(void *old_ptr)
{
    free(buff);
    memset(buff, 0x0, (BUF_SIZE * sizeof(char)) + 1);
}

void* gimme_mem_malloc(size_t bufSize)
{
    return malloc(bufSize);
}
