#include <stdio.h>          // printf()
#include <stdlib.h>         // free()
#include <string.h>         // strcpy()


int main(void)
{
    // LOCAL VARIABLES
    char strLiteral[] = {"Hello World!\n"};
    char *buff = (char *)calloc(12);

    if (buff)
    {
        // COPY
        strcpy(buff, strLiteral);

        // PRINT
        printf("%s", buff);

        // CLEAN UP
        free(buff);
    }

    // DONE
    return 0;
}
