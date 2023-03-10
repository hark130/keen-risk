#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy()

#define BUF_SIZE 64


int main(void)
{
    // LOCAL VARIABLES
    char *buff = (char *)malloc((BUF_SIZE * sizeof(char)) + 1);

    if (buff)
    {
        // COPY
        strcpy(buff, "Hello World!\n");

        // PRINT
        printf("%s", buff);
    }

    // DONE
    return 0;
}
