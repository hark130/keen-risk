#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy(), memset()
#include "gimme_mem.h"      // gimme_mem_malloc()
#include "mimo_wrappers.h"  // setup_mimo(), teardown_mimo()

#define BUF_SIZE 8


void do_what(char *buf)
{
    // PRINT
    free(buf);
    printf("%s", buf);
}


int main(void)
{
    // LOCAL VARIABLES
    char *buff = (char *)calloc((BUF_SIZE * sizeof(char)) + 1);

    // COPY
    strcpy(buff, "Hello World!\n");

    // PRINT
    do_what(buff);

    // CLEAN UP
    free(buff);

    // DONE
    return 0;
}
