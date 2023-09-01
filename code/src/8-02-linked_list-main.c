#include "8-02-linked_list.h"
#include <errno.h>   // errno
#include <stdio.h>   // fprintf()
#include <stdlib.h>  // calloc(), free()
#include <string.h>  // memcpy()

#define ARRAY_LEN (unsigned int)11
#define GOOD_JOB "\xE2\x9C\x94"    // Check mark?
#define BAD_JOB "X"                // Fail
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
 *  Compare an any_data_ptr (input) to the contents of a list_node_ptr (results).
 */
return_value _compare_test_results(any_data_ptr input, list_node_ptr test_result);

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
 *  Allocates a NULL-terminated array of any_data pointers on the heap.
 *  Allocates any_data struct pointers in each index (except for the last).
 */
any_data_ptr *_initialize_array(unsigned int array_len);

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
    return_value result = RET_SUCCESS;                            // Out parameter for certain calls
    list_node_ptr head_node = NULL;                               // Don't lose this
    list_node_ptr temp_node = NULL;                               // Temp linked list node ptr
    unsigned int exp_count = 0;                                   // Expected linked list count

    // VALIDATION
    if (!input_arr)
    {
        result = RET_ERROR;
        HARKLE_ERROR(main, Failed to allocate an array!);
    }

    // START TESTING
    // TEST 1 - Append nodes to a linked list
    // Create a linked list
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: NULL
        // Node 1
        head_node = append_data(NULL, input_arr[0], &result);
        if (!head_node)
        {
            fprintf(stderr, "Failed to allocate a node!\n");
            if (RET_SUCCESS == result)
            {
                result = RET_ERROR;  // This counts as a fail
            }
        }
        else
        {
            exp_count++;
        }
        _print_results(result, "TEST 1: Allocate head node in a linked list");
    }
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]
        // Node 2
        temp_node = append_data(head_node, input_arr[1], &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Failed to append node!  The new node became the head node?!\n");
            if (RET_SUCCESS == result)
            {
                result = RET_ERROR;  // This counts as a fail
            }
        }
        else
        {
            exp_count++;
        }

        _print_results(result, "TEST 1: Append a node to a head node");
    }
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]
        // Node 3
        temp_node = append_data(head_node, input_arr[2], &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Failed to append node!  The new node became the head node?!\n");
            if (RET_SUCCESS == result)
            {
                result = RET_ERROR;  // This counts as a fail
            }
        }
        else
        {
            exp_count++;
        }
        _print_results(result, "TEST 1: Append a node to a linked list");
    }
    // TEST 2 - Validate linked list length
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]
        if (exp_count != count_nodes(head_node))
        {
            result = RET_ERROR;
        }
        _print_results(result, "TEST 2: Linked list length");
    }
    // TEST 3 - Validate linked list contents (by position)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]
        temp_node = find_node_pos(head_node, 1, &result);
        if (RET_SUCCESS == result)
        {
            result = _compare_test_results(input_arr[0], temp_node);
        }
        _print_results(result, "TEST 3: Linked list contents - node 1");
    }
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]
        temp_node = find_node_pos(head_node, 2, &result);
        if (RET_SUCCESS == result)
        {
            result = _compare_test_results(input_arr[1], temp_node);
        }
        _print_results(result, "TEST 3: Linked list contents - node 2");
    }
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]
        temp_node = find_node_pos(head_node, 3, &result);
        if (RET_SUCCESS == result)
        {
            result = _compare_test_results(input_arr[2], temp_node);
        }
        _print_results(result, "TEST 3: Linked list contents - node 3");
    }
    // TEST 4 - Insert data
    // Insert front
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]
        temp_node = insert_data(head_node, input_arr[3], 1, &result);
        if (RET_SUCCESS == result)
        {
            if (temp_node == head_node)
            {
                fprintf(stderr, "Data was not inserted at the front\n");
                result = RET_ERROR;
            }
            else
            {
                head_node = temp_node;  // Store the new head node
                if (++exp_count != count_nodes(head_node))
                {
                    fprintf(stderr, "Invalid linked list node count\n");
                    result = RET_ERROR;
                }
                else
                {
                    result = _compare_test_results(input_arr[3], head_node);
                }
            }
        }
        _print_results(result, "TEST 4: Insert data - front");
    }
    // Insert middle
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [3]->[0]->[1]->[2]
        temp_node = insert_data(head_node, input_arr[4], 3, &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Why did the head node change?\n");
            result = RET_ERROR;
        }
        else if (RET_SUCCESS == result)
        {
            if (++exp_count != count_nodes(head_node))
            {
                fprintf(stderr, "Invalid linked list node count\n");
                result = RET_ERROR;
            }
            else
            {
                temp_node = find_node_pos(head_node, 3, &result);
                result = _compare_test_results(input_arr[4], temp_node);
            }
        }
        _print_results(result, "TEST 4: Insert data - middle");
    }
    // Insert end
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [3]->[0]->[4]->[1]->[2]
        temp_node = insert_data(head_node, input_arr[5], 6, &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Why did the head node change?\n");
            result = RET_ERROR;
        }
        else if (RET_SUCCESS == result)
        {
            if (++exp_count != count_nodes(head_node))
            {
                fprintf(stderr, "Invalid linked list node count\n");
                result = RET_ERROR;
            }
            else
            {
                temp_node = find_node_pos(head_node, 6, &result);
                result = _compare_test_results(input_arr[5], temp_node);
            }
        }
        _print_results(result, "TEST 4: Insert data - back");
    }
    // TEST 5 - Remove node (by position)
    // Remove middle
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [3]->[0]->[4]->[1]->[2]->[5]
        temp_node = remove_node_pos(head_node, 2, &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Why did the head node change?\n");
            result = RET_ERROR;
        }
        else if (RET_SUCCESS == result)
        {
            if (--exp_count != count_nodes(head_node))
            {
                fprintf(stderr, "Invalid linked list node count\n");
                result = RET_ERROR;
            }
            else
            {
                temp_node = find_node_pos(head_node, 2, &result);
                result = _compare_test_results(input_arr[4], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove node - middle");
    }
    // Remove back
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [3]->[4]->[1]->[2]->[5]
        temp_node = remove_node_pos(head_node, 5, &result);
        if (temp_node != head_node && temp_node)
        {
            fprintf(stderr, "Why did the head node change?\n");
            result = RET_ERROR;
        }
        else if (RET_SUCCESS == result)
        {
            if (--exp_count != count_nodes(head_node))
            {
                fprintf(stderr, "Invalid linked list node count\n");
                result = RET_ERROR;
            }
            else
            {
                temp_node = find_node_pos(head_node, 4, &result);
                result = _compare_test_results(input_arr[2], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove node - back");
    }
    // Remove front
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [3]->[4]->[1]->[2]
        temp_node = remove_node_pos(head_node, 1, &result);
        if (temp_node == head_node && temp_node)
        {
            fprintf(stderr, "Why didn't the head node change?\n");
            result = RET_ERROR;
        }
        else if (RET_SUCCESS == result)
        {
            head_node = temp_node;  // Store the new head node
            if (--exp_count != count_nodes(head_node))
            {
                fprintf(stderr, "Invalid linked list node count\n");
                result = RET_ERROR;
            }
            else
            {
                temp_node = find_node_pos(head_node, 1, &result);
                result = _compare_test_results(input_arr[4], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove node - front");
    }
    // TEST 6 - Validate linked list contents (by value)
    // Find [4]
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = find_node_val(head_node, input_arr[4], &result);
        if (temp_node)
        {
            result = _compare_test_results(input_arr[4], temp_node);
        }
        else if (RET_SUCCESS == result)
        {
            result = RET_ERROR;  // Success and NULL returns don't mix
        }
        _print_results(result, "TEST 6: Find node 1 by value");
    }
    // Find [1]
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = find_node_val(head_node, input_arr[1], &result);
        if (temp_node)
        {
            result = _compare_test_results(input_arr[1], temp_node);
        }
        else if (RET_SUCCESS == result)
        {
            result = RET_ERROR;  // Success and NULL returns don't mix
        }
        _print_results(result, "TEST 6: Find node 2 by value");
    }
    // Find [2]
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = find_node_val(head_node, input_arr[2], &result);
        if (temp_node)
        {
            result = _compare_test_results(input_arr[2], temp_node);
        }
        else if (RET_SUCCESS == result)
        {
            result = RET_ERROR;  // Success and NULL returns don't mix
        }
        _print_results(result, "TEST 6: Find node 3 by value");
    }
    // TEST 7 - Verify true negatives
    // find_node_pos()
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = find_node_pos(head_node, 4, &result);
        if (temp_node || RET_NOT_FOUND != result)
        {
            fprintf(stderr, "How did it find that position?\n");
            result = RET_ERROR;
        }
        else
        {
            result = RET_SUCCESS;  // This counts as a "pass"
        }
        _print_results(result, "TEST 7: Verify true negative - find_node_pos()");
    }
    // remove_node_pos()
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = remove_node_pos(head_node, 4, &result);
        if (temp_node || RET_NOT_FOUND != result)
        {
            fprintf(stderr, "What did it remove?\n");
            result = RET_ERROR;
        }
        else
        {
            result = RET_SUCCESS;  // This counts as a "pass"
        }
        _print_results(result, "TEST 7: Verify true negative - remove_node_pos()");
    }
    // find_node_val()
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        temp_node = find_node_val(head_node, input_arr[0], &result);
        if (temp_node || RET_NOT_FOUND != result)
        {
            fprintf(stderr, "How did it find that value?\n");
            result = RET_ERROR;  // Success and NULL returns don't mix
        }
        else
        {
            result = RET_SUCCESS;  // This counts as a "pass"
        }
        _print_results(result, "TEST 7: Verify true negative - find_node_val()");
    }
    // TEST 8 - Clean up
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [4]->[1]->[2]
        result = delete_list(head_node);
        if (RET_SUCCESS == result)
        {
            head_node = NULL;
        }
        _print_results(result, "TEST 8: delete_list()");
    }

    // DONE
    if (head_node)
    {
        fprintf(stderr, "You may have failed but let's try to clean up the linked list anyway\n");
        delete_list(head_node);
        head_node = NULL;
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


return_value _compare_test_results(any_data_ptr input, list_node_ptr test_result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_any_test_data(input);
    if (RET_SUCCESS != retval)
    {
        HARKLE_ERROR(_compare_results, Bad input from the test author!);
    }
    else if (!test_result || NULL == test_result->data_ptr)
    {
        retval = RET_INV_PARAM;
    }
    else
    {
        retval = _compare_any_test_data(input, test_result->data_ptr);
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
                    // fprintf(stderr, "Got character %c\n", tmp_char);  // DEBUGGING
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
                // fprintf(stderr, "Got string %s\n", tmp_str);  // DEBUGGING
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
                // fprintf(stderr, "Got void string %s\n", tmp_str);  // DEBUGGING
                fill_me->d_type = VOID_DT;
                fill_me->d_size = strlen(tmp_str) + 1;
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
