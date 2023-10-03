/*
 *  Unit tests for void_lib's void_cat().
 *  This is version 0.0.5.
 *  
 *  Version 0.0.1
 *      - Normal 1 & 2
 *  Version 0.0.2
 *      - Error 1 & 2
 *      - Normal 1 & 2 BUG fix
 *  Version 0.0.3
 *      - Boundary 1
 *      - Special 1
 *      - More BUG fix
 *  Version 0.0.4
 *      - Final(?) BUG fix
 *  Version 0.0.5
 *      - Special 2-4
 *      - Necessary calls to void_free()
 *      - Removed invalid reference
 *      - Implemented call to void_free() (no more memory leaks?)
 */

#include <stdio.h>   // printf(), fprintf()
#include <stdlib.h>  // srand()
#include <string.h>  // memcmp()
#include <time.h>    // time()
#include "void_lib.h"  // void_cat()

#define FAIL_MSG "<<<FAIL>>>"
#define GOOD_MSG "SUCCESS"
#define FAILURE(testnum, expected, result) do { fprintf(stderr, "%s Test number %s expected %s but received %s\n", FAIL_MSG, #testnum, #expected, #result); } while(0);
#define SUCCESS(msg) do { printf("%s: %s\n", GOOD_MSG, #msg); } while(0);
#define BUF_SIZE 1024


/*
 *  ARGS:
 *      old_buf_ptr - void_free()'s old_buf_ptr
 *      buf_size - void_free()'s buf_size
 *      exp_ret - void_free()'s expected return value
 */
void call_void_free(void *old_buf_ptr, size_t buf_size, int exp_ret);


int main()
{
    // LOCAL VARIABLES
    int buf1_input[BUF_SIZE] = {0};     // Pass this to void_cat()
    int buf1_orig[BUF_SIZE] = {0};      // "Control" version of buf1_input
    size_t size1 = 0;                   // void_cat(size1)
    size_t size2 = 0;                   // void_cat(size2)
    int size1_offset = 0;               // Number of buf1 elements to use in the test
    int size2_offset = 0;               // Number of buf2 elements to use in the test
    int expected_buff[BUF_SIZE] = {0};  // Expected result
    void *ret_ptr = NULL;  // Return value from void_cat()

    // SETUP
    srand(time(NULL));  // Seed the psuedo-random generator
    for (int i = 0; i < BUF_SIZE; i++)
    {
        buf1_orig[i] = rand();
        buf1_input[i] = buf1_orig[i];
        expected_buff[i] = 0x0;  // While we're looping, just go ahead and zeroize it
    }

    // TESTING
    // Normal Test 1
    size1_offset = 3;
    size2_offset = 3;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, buf1_input + size1_offset, size2);
    if (!ret_ptr)
    {
        FAILURE(Normal 1, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Normal 1, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Normal 1, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Normal Test 1);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Normal Test 2
    size1_offset = 3;
    size2_offset = 72;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, buf1_input + size1_offset, size2);
    if (!ret_ptr)
    {
        FAILURE(Normal 2, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Normal 2, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Normal 2, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Normal Test 2);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Error Test 1
    size1_offset = 3;
    size2_offset = 72;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(NULL, size1, NULL, size2);
    if (ret_ptr)
    {
        FAILURE(Error 1, NULL, a pointer);
    }
    else
    {
        SUCCESS(Error Test 1);
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Error Test 2
    size1_offset = 0;
    size2_offset = 0;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, buf1_input + size1_offset, size2);
    if (ret_ptr)
    {
        FAILURE(Error 2, NULL, a pointer);
    }
    else
    {
        SUCCESS(Error Test 2);
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Boundary Test 1
    size1_offset = 1;
    size2_offset = 1;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, buf1_input + size1_offset, size2);
    if (!ret_ptr)
    {
        FAILURE(Boundary 1, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Boundary 1, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Boundary 1, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Boundary Test 1);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Special 1
    size1_offset = 13;
    size2_offset = 0;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, NULL, size2);
    if (!ret_ptr)
    {
        FAILURE(Special 1, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Special 1, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Special 1, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Special Test 1);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Special 2
    size1_offset = 0;
    size2_offset = 13;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(NULL, size1, buf1_input, size2);
    if (!ret_ptr)
    {
        FAILURE(Special 2, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Special 2, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Special 2, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Special Test 2);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Special 3
    size1_offset = 3;
    size2_offset = 55;
    size1 = size1_offset * sizeof(int);
    size2 = size2_offset * sizeof(int);
    ret_ptr = void_cat(buf1_input, size1, NULL, size2);
    if (!ret_ptr)
    {
        FAILURE(Special 3, a pointer, NULL);
    }
    else if (memcmp(buf1_input, buf1_orig, BUF_SIZE))
    {
        FAILURE(Special 3, no change in the input buffer, evidence the input buffer was altered);
    }
    else
    {
        memcpy(expected_buff, buf1_orig, size1 + size2);
        memset(expected_buff + size1_offset, 0x0, size2);
        if (memcmp(ret_ptr, expected_buff, size1 + size2))
        {
            FAILURE(Special 3, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Special Test 3);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // Special 4
    size1_offset = 3;
    size2_offset = 5;
    size1 = size1_offset * sizeof(char);
    size2 = size2_offset * sizeof(char);
    ret_ptr = void_cat("abc123", size1, "hello world", size2);
    if (!ret_ptr)
    {
        FAILURE(Special 4, a pointer, NULL);
    }
    else
    {
        if (strncmp(ret_ptr, "abchello", size1 + size2))
        {
            FAILURE(Special 4, matching results, a mismatch);
        }
        else
        {
            SUCCESS(Special Test 4);
        }
    }
    call_void_free(ret_ptr, size1 + size2, 0);
    ret_ptr = NULL;

    // DONE
    return 0;
}


void call_void_free(void *old_buf_ptr, size_t buf_size, int exp_ret)
{
    // LOCAL VARIABLES
    int ret_val = 0;  // Return value from void_free()

    // CALL IT
    if (old_buf_ptr)
    {
        // ret_val = void_free(old_buf_ptr, buf_size);
        free(old_buf_ptr);  // DEBUGGING
        if (ret_val != exp_ret)
        {
            fprintf(stderr, "void_free() failed.  Expected %d but received %d\n", exp_ret, ret_val);
        }
    }
}
