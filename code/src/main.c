#include "harklemem.h"	// give_me_memory(), take_my_memory()
#include <stdio.h>		// printf()
#include <string.h>		// strncpy()


int main(void)
{
	// LOCAL VARIABLES
	int exitCode = 0;      // 0 for success, 1 for failure
	size_t buffLen = 256;  // Harklemem memory length
	void *hmem = NULL;     // Harklemem pointer

	// DO SOMETHING
	hmem = give_me_memory(buffLen);
	if (hmem != NULL)
	{
		strncpy(hmem, "Hello, world!", buffLen - 1);
		printf("%s is stored at %p\n", (char*)hmem, hmem);
		take_my_memory(&hmem, buffLen);
		printf("Now my pointer is %p\n", hmem);
	}
	else
	{
		exitCode = 1;
	}

	// DONE
	return exitCode;
}
