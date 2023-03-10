#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy(), memset()

#define BUF_SIZE 64

void what_it_is(char *buf)
{
    printf("%s", buf);
}

int main(void)
{
    // LOCAL VARIABLES
    char *buff = (char *)calloc((BUF_SIZE * sizeof(char)) + 1);

    if (buff)
    {
        // COPY
        strcpy(buff, "Hello World!\n");

        // PRINT
        what_it_is(buff);

        // CLEAN UP
        free(buff);
    }

    // DONE
    return 0;
}
