#include "harklemem.h"  // harkleset()
#include <errno.h>      // errno
#include <stdbool.h>    // bool, true, false
#include <stdlib.h>     // calloc(), free()
#include <stdio.h>      // fprintf()
#include <string.h>     // strerror()

#define HARKLE_ERROR(header, funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", #header, #funcName, #msg); } while (0);
#define HARKLE_ERRNO(header, funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - %s() returned errno:\t%s\n", #header, #funcName, strerror(errorNum)); }
#define HARKLE_WARNG(header, funcName, msg) do { fprintf(stderr, "¿¿¿WARNING??? - %s - %s() - %s!\n", #header, #funcName, #msg); } while (0);

#ifndef HARKLEMEM_MAX_TRIES
// MACRO to limit repeated allocation attempts
#define HARKLEMEM_MAX_TRIES 3
#endif  // HARKLEMEM_MAX_TRIES


void *give_me_memory(size_t length)
{
    // LOCAL VARIABLES
    int numTries = 0;     // Current number of calloc attempts
    void* retVal = NULL;  // Heap-allocated buffer
    int errnum = 0;       // Store errno
    bool success = true;  // Controls the flow

    // INPUT VALIDATION
    if (length < 1)
    {
        HARKLE_ERROR(harklemem, give_me_memory, Invalid buffer length);
        success = false;
    }

    // ALLOCATION
    if (success == true)
    {
        while (retVal == NULL && numTries < HARKLEMEM_MAX_TRIES)
        {
            errno = 0;  // Manually clear it
            retVal = (void*)calloc(length, 1);
            errnum = errno;
            HARKLE_ERRNO(harklemem, calloc, errnum);
            numTries++;
        }

        if (!retVal)
        {
            HARKLE_ERROR(harklemem, give_me_memory, calloc failed);
            success = false;
        }
    }

    // DONE
    return retVal;
}


void *harkleset(void *s, int c, size_t n)
{
    // LOCAL VARIABLES
    void *tempPtr = NULL;                            // Return value from memset
    int errnum = 0;                                  // Store errno
    void *(*func_ptr)(void*, int, size_t) = memset;  // memset(s, c, n);

    // DO IT
    errno = 0;
    tempPtr = func_ptr(s, c, n);
    errnum = errno;
    HARKLE_ERRNO(harklemem, memset, errnum);
    if (tempPtr != s)
    {
        HARKLE_ERROR(harklemem, harkleset, The call to memset has failed);
    }

    // DONE
    return tempPtr;
}


void take_my_memory(void **oldMem, size_t length)
{
    // LOCAL VARIABLES
    bool success = true;   // Controls the flow
    void *heapMem = NULL;  // Pointer to zeroize, free(), and NULLify
    int errnum = 0;        // Store errno

    // INPUT VALIDATION
    // oldMem
    if (oldMem == NULL || *oldMem == NULL)
    {
        HARKLE_ERROR(harklemem, take_my_memory, NULL pointer);
        success = false;
    }
    else
    {
        heapMem = *oldMem;
    }
    // length
    if (length < 1)
    {
        HARKLE_ERROR(harklemem, take_my_memory, Invalid buffer length);
        success = false;
    }

    // DO IT
    // Zeroize
    if (success == true)
    {
        if (heapMem != harkleset(heapMem, 0x0, length))
        {
            HARKLE_ERROR(harklemem, take_my_memory, The call to harkleset has failed);
            success = false;
        }
    }
    // Free
    if (heapMem != NULL)
    {
        free(heapMem);  // Doesn't matter what has failed.  We're *free()ing* this pointer.
        heapMem = NULL;
    }
    // NULLify
    if (success == true)
    {
        *oldMem = NULL;  // Now the caller doesn't have to worry about it
    }
}
