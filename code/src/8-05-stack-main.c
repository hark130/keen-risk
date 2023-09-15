/*
 *  DESCRIPTION:
 *      This source file contains unit tests for the 8-05 student labs.  These unit tests should
 *      suffice regardless of the stack implementation used to defined the 8-05-stack functions.
 *
 *  BUILD:
 *      The easiest way to build these unit tests is to copy all the files into a dir and:
 *      gcc -o 8-05-1-lab.bin 8-05-stack-main.c 8-02-1-linked_list-lab.c 8-05-1-list_stack-lab.c
 *      -or-
 *      gcc -o 8-05-2-lab.bin 8-05-stack-main.c 8-02-1-linked_list-lab.c 8-05-2-array_stack-lab.c
 *
 *      BONUS: Stop copy pasting gcc commands and create a Makefile.  See: JQS 6-17.
 *
 *  TEST:
 *      ./8-05-1-lab.bin  # Read the output.  Failures go to stderr.  Read the test code.
 *      ./8-05-2-lab.bin  # Read the output.  Failures go to stderr.  Read the test code.
 *      # Be sure to build and run the solution through ASAN.  See: JQS 6-16 and 6-21.
 *      # Also use Valgrind to identify issues with memory management.  See: JQS 6-21.
 */

#include "8-05-stack.h"
#include <errno.h>   // errno
#include <stdio.h>   // fprintf()
#include <stdlib.h>  // calloc(), free()
#include <string.h>  // memcpy()
#include <time.h>    // time()

#define ARRAY_LEN (unsigned int)43  // (6 * 7) + 1 for NULL termination
#define GOOD_JOB "\xE2\x9C\x94"     // Check mark?
#define BAD_JOB "X"                 // Fail
#define HARKLE_ERROR(funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", \
                                                 __FILE__, #funcName, #msg); } while (0);
#define HARKLE_ERRNO(funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - \
                                                                 %s() returned errno:\t%s\n", \
                                                                 __FILE__, #funcName, \
                                                                 strerror(errorNum)); }


/*
 *  Compare input to test_data_result.  Does not validate input.
 */
return_value _compare_any_test_data(any_data_ptr input, any_data_ptr test_data_result);

/*
 *  Compares all aspects of s1 data against s2, starting with the bookkeeping.  Immediately
 *  returns RET_ERROR on the first difference detected.  S1 is not validated.
 */
return_value _compare_test_data(any_data_ptr s1_data, void *s2_data, data_type s2_data_type,
                                unsigned int s2_data_size);

/*
 *  Allocate a NULL-terminated array of any_data_ptrs and fill each one.  Array_len will be used
 *  as the total array length, NULL terminator included.
 */
any_data_ptr *_create_and_fill_array(unsigned int array_len);

/*
 *  Free and zeroize d_ptr, d_type, and d_size.  Then free() old_data.
 */
void _clear_any_data(any_data_ptr old_data);

/*
 *  For each any_data_ptr in the array, free()s the memory and frees the struct.
 *  Then, the array gets free()d.
 */
void _clear_array(any_data_ptr *old_arr);

/*
 *  Allocates heap memory to copy in data, based on selection, into fill_me.  Selection - 1
 *  should line up to the data_type enum values.
 */
void _fill_any_data(any_data_ptr fill_me, int selection);

/*
 *  Randomize a number ranging from 1 (new head node) to cur_count + 1 (new tail node).
 *  Returns 1 if cur_count is 0.
 */
unsigned int _get_rand_pos(unsigned int cur_count);

/*
 *  Allocates a NULL-terminated array of any_data pointers on the heap.
 *  Allocates any_data struct pointers in each index (except for the last).
 */
any_data_ptr *_initialize_array(unsigned int array_len);

/*
 *  On success, prints data details to stdout.  On error, prints message to stderr.
 */
void _print_any_data(any_data_ptr data);

/*
 *  Provide human-readable and actionable test case feedback to the user.
 */
void _print_results(return_value result, const char *message);

/*
 *  Validates any_data structs on behalf of the library.
 */
return_value _validate_any_test_data(any_data_ptr data);

/*
 *  Validates raw data on behalf of the library.
 */
return_value _validate_raw_test_data(void *raw_data, data_type raw_data_type,
                                     unsigned int raw_data_size);


int main()
{
    // LOCAL VARIABLES
    any_data_ptr *input_arr = _create_and_fill_array(ARRAY_LEN);  // Array of test case input
    any_data_ptr tmp_data = NULL;                                 // Temp data variable
    return_value result = RET_SUCCESS;                            // Out parameter for certain calls
    stack_adt_ptr stack = NULL;                                   // Stack struct pointer
    unsigned int exp_count = 0;                                   // Expected stack size
    unsigned int act_count = 0;                                   // Actual stack size
    unsigned int init_cap = 4;                                    // Starting capacity
    bool empty = false;                                           // is_empty() return value

    // SETUP
    fprintf(stdout, "Running tests from %s\n", __FILE__);

    // VALIDATION
    if (!input_arr)
    {
        result = RET_ERROR;
        HARKLE_ERROR(main, Failed to allocate an array!);
    }

    // START TESTING
    // TEST 1 - Create a stack
    // Create a stack struct
    if (RET_SUCCESS == result)
    {
        stack = allocate_stack(init_cap, &result);
        if (!stack && RET_SUCCESS == result)
        {
            fprintf(stderr, "Failed to allocate a stack struct\n");
            result = RET_ERROR;  // This counts as a fail
        }
        _print_results(result, "TEST 1: Create a stack");
    }
    // TEST 2 - Push some data
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: EMPTY STACK
        for (int i = 0; i < 3; i++)
        {
            result = push_data(stack, (*(input_arr + i)));
            if (RET_SUCCESS != result)
            {
                fprintf(stderr, "Failed to push_data(input_arr[%d])\n", i);
                break;  // Let's stop now
            }
            exp_count++;
        }
        _print_results(result, "TEST 2: Push some data onto the stack");
    }
    // TEST 3 - Validate stack size
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[2][1][0]
        act_count = get_size(stack, &result);
        if (exp_count != act_count)
        {
            fprintf(stderr, "Expected a count of %d but received a count of %d\n",
                    exp_count, act_count);
            if (RET_SUCCESS == result)
            {
                fprintf(stderr, "The get_size() result was incorrect but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
        }
        _print_results(result, "TEST 3: Stack size");
    }
    // TEST 4 - LIFO Get top
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[2][1][0]
        tmp_data = get_top(stack, &result);
        if (RET_SUCCESS == result)
        {
            result = _compare_any_test_data(input_arr[2], tmp_data);
        }
        if (RET_SUCCESS == result)
        {
            act_count = get_size(stack, &result);
            if (exp_count != act_count)
            {
                fprintf(stderr, "Expected a count of %d but received a count of %d\n",
                        exp_count, act_count);
                if (RET_SUCCESS == result)
                {
                    fprintf(stderr, "The get_size() result was incorrect but reported success\n");
                    result = RET_ERROR;  // This counts as a fail
                }
            }
        }
        tmp_data = NULL;  // Forget the pointer since we don't own it
        _print_results(result, "TEST 4: Verify LIFO - get_top()");
    }
    // TEST 5 - LIFO Pop data
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[2][1][0]
        tmp_data = pop_data(stack, &result);
        if (RET_SUCCESS == result)
        {
            result = _compare_any_test_data(input_arr[2], tmp_data);
            if (tmp_data)
            {
                destroy_any_data(tmp_data);  // This return value gets a pass
                tmp_data = NULL;
            }
        }
        if (RET_SUCCESS == result)
        {
            act_count = get_size(stack, &result);
            if (--exp_count != act_count)
            {
                fprintf(stderr, "Expected a count of %d but received a count of %d\n",
                        exp_count, act_count);
                if (RET_SUCCESS == result)
                {
                    fprintf(stderr, "The get_size() result was incorrect but reported success\n");
                    result = RET_ERROR;  // This counts as a fail
                }
            }
        }
        _print_results(result, "TEST 5: Verify LIFO - pop_data()");
    }
    // TEST 6 - Is empty
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[1][0]
        empty = is_empty(stack, &result);
        if (RET_SUCCESS == result && true == empty)
        {
            fprintf(stderr, "This stack is not empty\n");
        }
        _print_results(result, "TEST 6: Is it empty?");
    }
    // TEST 7 - Empty the stack
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[1][0]
        result = empty_stack(stack);
        if (RET_SUCCESS == result)
        {
            exp_count = 0;
            empty = is_empty(stack, &result);
            if (false == empty)
            {
                fprintf(stderr, "empty_stack() succeeded but is_empty() disagrees\n");
            }
        }
        _print_results(result, "TEST 7: Is it empty?");
    }
    // TEST 8 - Overflow initial capacity
    // Overflow
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: EMPTY STACK
        for (int i = 0; i < ARRAY_LEN - 1; i++)
        {
            result = push_data(stack, (*(input_arr + i)));
            if (RET_SUCCESS != result)
            {
                fprintf(stderr, "Failed to push_data(input_arr[%d])\n", i);
                break;  // Let's stop now
            }
            exp_count++;
        }
        _print_results(result, "TEST 8: Verify the stack can grow - spam push()es");
    }
    // Verify size
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: top->[42][41]...[1][0]
        act_count = get_size(stack, &result);
        if (exp_count != act_count)
        {
            fprintf(stderr, "Expected a count of %d but received a count of %d\n",
                    exp_count, act_count);
            if (RET_SUCCESS == result)
            {
                fprintf(stderr, "The get_size() result was incorrect but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
        }
        _print_results(result, "TEST 8: Verify the stack can grow - new size");
    }
    // Verify LIFO
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: EMPTY STACK
        for (int i = ARRAY_LEN - 2; i >= 0; i--)
        {
            tmp_data = pop_data(stack, &result);
            if (RET_SUCCESS == result)
            {
                result = _compare_any_test_data(input_arr[i], tmp_data);
                if (tmp_data)
                {
                    destroy_any_data(tmp_data);  // This return value gets a pass
                    tmp_data = NULL;
                }
            }
            if (RET_SUCCESS == result)
            {
                act_count = get_size(stack, &result);
                if (--exp_count != act_count)
                {
                    fprintf(stderr, "Expected a count of %d but received a count of %d\n",
                            exp_count, act_count);
                    if (RET_SUCCESS == result)
                    {
                        fprintf(stderr, "The get_size() result was wrong but reported success\n");
                        result = RET_ERROR;  // This counts as a fail
                    }
                }
            }
            if (RET_SUCCESS != result)
            {
                break;  // Stop testing
            }
        }
        _print_results(result, "TEST 8: Verify the stack can grow - verify LIFO");
    }
    // TEST 9 - Verify true negatives
    /* TO DO: DON'T DO NOW... Implement these unit tests */
    // TEST 10 - Clean up
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: Doesn't matter because it's all getting deleted
        result = destroy_stack(stack);
        if (RET_SUCCESS == result)
        {
            stack = NULL;
        }
        _print_results(result, "TEST 10: Final clean up");
    }

    // DONE
    if (stack)
    {
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "You may have failed but let's clean up the linked list anyway\n");
        }
        destroy_stack(stack);
        stack = NULL;
    }
    if (input_arr)
    {
        _clear_array(input_arr);
        input_arr = NULL;
    }
}


void _clear_any_data(any_data_ptr old_data)
{
    if (old_data)
    {
        if (old_data->d_ptr)
        {
            free(old_data->d_ptr);
            old_data->d_ptr = NULL;
        }
        old_data->d_type = NULL_DT;
        old_data->d_size = 0;
        free(old_data);
    }
}


void _clear_array(any_data_ptr *old_arr)
{
    any_data_ptr *tmp_ptr = old_arr;
    if (old_arr && *old_arr)
    {
        while(tmp_ptr && *tmp_ptr)
        {
            _clear_any_data(*tmp_ptr);
            tmp_ptr++;
        }
    }
    if (old_arr)
    {
        free(old_arr);
    }
}


return_value _compare_any_test_data(any_data_ptr s1_data, any_data_ptr s2_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    // s2
    retval = _validate_any_test_data(s2_data);

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        retval = _compare_test_data(s1_data, s2_data->d_ptr, s2_data->d_type, s2_data->d_size);
    }

    // DONE
    return retval;
}


return_value _compare_test_data(any_data_ptr s1_data, void *s2_data, data_type s2_data_type,
                                unsigned int s2_data_size)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    // s2
    retval = _validate_raw_test_data(s2_data, s2_data_type, s2_data_size);

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        if (s2_data_size != s1_data->d_size)
        {
            retval = RET_ERROR;  // Different sizes
        }
        else if (s2_data_type != s1_data->d_type)
        {
            retval = RET_ERROR;  // Different data types
        }
        else if (memcmp(s2_data, s1_data->d_ptr, s2_data_size))
        {
            retval = RET_ERROR;  // Memory doesn't match
        }
    }

    // DONE
    return retval;
}


any_data_ptr *_create_and_fill_array(unsigned int array_len)
{
    any_data_ptr *any_data_arr = _initialize_array(array_len);
    if (any_data_arr)
    {
        for (int i = 0; i < array_len - 1; i++)
        {
            _fill_any_data(any_data_arr[i], i);
        }
    }
    return any_data_arr;
}


void _fill_any_data(any_data_ptr fill_me, int selection)
{
    int num_options = 6;                   // Number of available selections implemented below
    int choice = selection % num_options;  // Switch on this value (to avoid overruns)
    static int call_num = 0;               // Track the number of calls to iterate through input
    // Array of char* (or void*) inputs to cycle through
    char *str_selections[] = {"Why are you reading this?", "This is a string", "I am test input",
                              "Something something char array", "These can also be used for void*",
                              "Do I have enough?", "NULL is different than nul", NULL};
    char tmp_char = '\0';                               // Temp char var
    double tmp_dble = (double)selection / num_options;  // Temp double var
    float tmp_float = (float)selection / num_options;   // Temp float var
    char *tmp_str = NULL;                               // Temp string

    if (fill_me)
    {
        call_num++;
        switch (choice)
        {
            case 0:
                fill_me->d_type = CHAR_DT;
                fill_me->d_size = sizeof(char);
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    tmp_char = str_selections[0][call_num % strlen(str_selections[0])];
                    memcpy(fill_me->d_ptr, &tmp_char, fill_me->d_size);
                }
                break;
            case 1:
                fill_me->d_type = DOUBLE_DT;
                fill_me->d_size = sizeof(double);
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    memcpy(fill_me->d_ptr, &tmp_dble, fill_me->d_size);
                }
                break;
            case 2:
                fill_me->d_type = FLOAT_DT;
                fill_me->d_size = sizeof(float);
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    memcpy(fill_me->d_ptr, &tmp_float, fill_me->d_size);
                }
                break;
            case 3:
                fill_me->d_type = INT_DT;
                fill_me->d_size = sizeof(int);
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    memcpy(fill_me->d_ptr, &call_num, fill_me->d_size);
                }
                break;
            case 4:
                // Select a string from the array, without running out-of-bounds, using the
                // call_num as a seed value
                tmp_str = str_selections[call_num % \
                          ((sizeof(str_selections) / sizeof(*str_selections)) - 1)];
                fill_me->d_type = STRING_DT;
                fill_me->d_size = strlen(tmp_str) + 1;
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    memcpy(fill_me->d_ptr, tmp_str, fill_me->d_size);
                }
                break;
            case 5:
                // Select a string from the array, without running out-of-bounds, using the
                // call_num as a seed value
                tmp_str = str_selections[call_num % \
                          ((sizeof(str_selections) / sizeof(*str_selections)) - 1)];
                fill_me->d_type = VOID_DT;
                fill_me->d_size = strlen(tmp_str);
                fill_me->d_ptr = calloc(1, fill_me->d_size);
                if (fill_me->d_ptr)
                {
                    memcpy(fill_me->d_ptr, tmp_str, fill_me->d_size);
                }
                break;
            default:
                fprintf(stderr, "How did we get here?!");
                break;
        }
    }
}


unsigned int _get_rand_pos(unsigned int cur_count)
{
    // LOCAL VARIABLES
    unsigned int retval = 1;  // Position to insert

    // INPUT VALIDATION
    if (cur_count > 0)
    {
        // Generates a pseudo-random integer between 1 and cur_count + 1
        retval = (rand() % (cur_count + 1)) + 1;
    }

    // DONE
    return retval;
}


any_data_ptr *_initialize_array(unsigned int array_len)
{
    any_data_ptr *any_data_arr = calloc(array_len, sizeof(any_data_ptr));
    int errnum = 0;  // Store errno here
    if (any_data_arr)
    {
        for (int i = 0; i < (array_len - 1); i++)
        {
            (*(any_data_arr + i)) = calloc(1, sizeof(any_data));
            if (NULL == (*(any_data_arr + i)))
            {
                errnum = errno;
                fprintf(stderr, "Failed to allocate index %d\n", i);
                HARKLE_ERRNO(calloc, errnum);
                break;
            }
        }
    }
    else
    {
        errnum = errno;
        HARKLE_ERROR(_initialize_array, Failed to allocate array);
        HARKLE_ERRNO(calloc, errnum);
    }

    return any_data_arr;
}


void _print_any_data(any_data_ptr data)
{
    if (data && data->d_ptr && NULL_DT != data->d_type && data->d_size > 0)
    {
        // CHAR_DT, DOUBLE_DT, FLOAT_DT, INT_DT, STRING_DT, VOID_DT
        switch (data->d_type)
        {
            case CHAR_DT:
                printf("Any_data type of %d (size %d): '%c' [%X]\n", data->d_type, data->d_size,
                       *((char*)data->d_ptr), *((int*)data->d_ptr));
                break;
            case DOUBLE_DT:
                printf("Any_data type of %d (size %d): %f\n", data->d_type, data->d_size,
                       *((double*)data->d_ptr));
                break;
            case FLOAT_DT:
                printf("Any_data type of %d (size %d): %lf\n", data->d_type, data->d_size,
                       *((float*)data->d_ptr));
                break;
            case INT_DT:
                printf("Any_data type of %d (size %d): %d\n", data->d_type, data->d_size,
                       *((int*)data->d_ptr));
                break;
            case STRING_DT:
                printf("Any_data type of %d (size %d): ", data->d_type, data->d_size);
                for (int i = 0; i < data->d_size; i++)
                {
                    printf("%c", ((char*)data->d_ptr)[i]);
                }
                printf("\n");
                break;
            case VOID_DT:
                printf("Any_data type of %d (size %d): ", data->d_type, data->d_size);
                for (int i = 0; i < data->d_size; i++)
                {
                    printf("0x%02X ", 0xFF & ((char*)data->d_ptr)[i]);
                }
                printf("\n");
                printf("Any_data VOID_DT as a string: %s\n", ((char*)data->d_ptr));
                break;
            default:
                fprintf(stderr, "Unsupported data->d_type of %d (size: %d)\n", data->d_type,
                        data->d_size);
        }
    }
    else
    {
        fprintf(stderr, "Bad input for %p\n", data);
    }
}


void _print_results(return_value result, const char *message)
{
    // Success
    if (RET_SUCCESS == result)
    {
        fprintf(stdout, "[%s] %s passed\n", GOOD_JOB, message);
    }
    else
    {
        fprintf(stderr, "[%s] %s <<<FAILED>>> with a return value of %d\n", BAD_JOB, message,
                result);
    }
}


return_value _validate_any_test_data(any_data_ptr data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!data)
    {
        retval = RET_INV_PARAM;
    }
    else
    {
        retval = _validate_raw_test_data(data->d_ptr, data->d_type, data->d_size);
    }

    // DONE
    return retval;
}


return_value _validate_raw_test_data(void *raw_data, data_type raw_data_type,
                                     unsigned int raw_data_size)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!raw_data)
    {
        retval = RET_INV_PARAM;
    }
    else if (NULL_DT == raw_data_type)
    {
        retval = RET_INV_PARAM;
    }
    else if (raw_data_size < 1)
    {
        retval = RET_INV_PARAM;
    }

    // DONE
    return retval;
}
