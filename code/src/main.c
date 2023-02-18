#include "harklemem.h"	// give_me_memory(), take_my_memory()
#include <string.h>		// strncpy()


int main(void)
{
	// LOCAL VARIABLES
	int exitCode = 0;      // 0 for success, 1 for failure
	size_t buffLen = 256;  // Harklemem memory length
	void *hmem = NULL;     // Harklemem pointer

	// DO SOMETHING
	hmem = give_me_memory(256);
	if (hmem != NULL)
	{
		strncpy(hmem, "Hello, world!", buffLen - 1);
		printf("%s is stored at 0x%p\n", hmem, hmem);
		take_my_memory(&hmem);
		printf("Now my pointer is 0x%p\n", hmem);
	}
	else
	{
		exitCode = 1;
	}

	// DONE
	return exitCode;
}
