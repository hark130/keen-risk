/*
 * One With Everything (OWE) Memory usage
 */

#include <harklemem.h>		// give_me_memory(), take_my_memory()
#include <stdio.h>			// printf(), getchar()

int dataGlobal = 0xDEADBEEF;  // Stored in .DATA


int main(void)
{
	// LOCAL VARIABLES
	int retVal = 0;       // Stored on the stack
	int *someNum = NULL;  // Also on the stack

	// DO SOMETHING
	someNum = give_me_memory(sizeof(int));  // Returns a pointer to the heap

	if (NULL == someNum)
	{
		retVal = 1;  // PRO TIP: Always Be Checking pointers
	}
	else
	{
		*someNum = dataGlobal;
		printf("Somewhere in the stack is retVal at %p\n", &retVal);
		printf("The stack also stores someNum's value at %p\n", &someNum);
		printf("However, someNum's value points to the heap at %p storing value 0x%X\n", someNum, *someNum);
		printf("Somewhere in .DATA is dataGlobal at %p\n\n\n", &dataGlobal);
		take_my_memory((void**)&someNum, sizeof(int));  // Zeroizes and frees the heap memory
		getchar();  // Pause exeucution so I can inspect /proc/PID/maps
	}

	// DONE
	return retVal;
}
