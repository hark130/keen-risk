/*
 *  DESCRIPTION:
 *      This source file contains unit tests for student lab 8-02-2.
 *
 *  BUILD:
 *      The easiest way to build these unit tests is to copy all the files into a dir and:
 *      gcc -o 8-02-2-lab.bin 8-02-2-circular_list-main.c 8-02-sort_functions.c 8-02-2-circular_list-lab.c
 *
 *      BONUS: Stop copy pasting gcc commands and create a Makefile.  See: JQS 6-17.
 *
 *  TEST:
 *      ./8-02-2-lab.bin  # Read the output.  Failures go to stderr.  Read the test code.
 *      # Be sure to build and run the solution through ASAN.  See: JQS 6-16 and 6-21.
 *      # Also use Valgrind to identify issues with memory management.  See: JQS 6-21.
 */

#include "8-02-2-circular_list.h"
#include "8-02-sort_functions.h"
#include <errno.h>   // errno
#include <stdio.h>   // fprintf()
#include <stdlib.h>  // calloc(), free(), rand(), srand()
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
 *  Checks the actual c_list count against the expected count.  Prints to stderr on mismatch.
 */
return_value _check_count(circular_list_ptr c_list, unsigned int exp_count);

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
 *  Compare an any_data_ptr (input) to the contents of a circular_list_ptr (results).
 */
return_value _compare_test_results(any_data_ptr input, circular_node_ptr test_result);

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
    return_value result = RET_SUCCESS;                            // Out parameter for certain calls
    circular_list_ptr c_list = NULL;                              // Don't lose this
    circular_node_ptr temp_node = NULL;                           // Temp linked list node ptr
    unsigned int exp_count = 0;                                   // Expected linked list count
    unsigned int rand_pos = 0;                                    // Random linked list pos

    // SETUP
    fprintf(stdout, "Running tests from %s\n", __FILE__);

    // VALIDATION
    if (!input_arr)
    {
        result = RET_ERROR;
        HARKLE_ERROR(main, Failed to allocate an array!);
    }

    // START TESTING
    srand(time(NULL));  // Seed the psuedo-random generator
    // TEST 1 - Create an empty circular linked list
    if (RET_SUCCESS == result)
    {
        c_list = create_circular_list(&result);
        if (!c_list && RET_SUCCESS == result)
        {
            fprintf(stderr, "The function call returned NULL but reported success\n");
            result = RET_ERROR;  // This counts as a fail
        }
        _print_results(result, "TEST 1: Create an empty circular linked list");
    }
    // TEST 2 - Add nodes to the circular linked list
    // Head Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: NULL
        result = insert_cdata(c_list, input_arr[0], 1);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, ++exp_count);
        }
        _print_results(result, "TEST 2: Add a new head node to the circular linked list");
    }
    // Tail Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[0]...
        result = insert_cdata(c_list, input_arr[2], 2);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, ++exp_count);
        }
        _print_results(result, "TEST 2: Add a new tail node to the circular linked list");
    }
    // Middle Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[2]->[0]...
        result = insert_cdata(c_list, input_arr[1], 2);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, ++exp_count);
        }
        _print_results(result, "TEST 2: Add a new node to the circular linked list");
    }
    // Verify the linked list is circular
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[0]...
        if (c_list->tail_ptr->next_ptr != c_list->head_ptr)
        {
            fprintf(stderr, "The tail node doesn't point at the head node\n");
            result = RET_ERROR;  // This counts as a fail
        }
        _print_results(result, "TEST 2: Verify the linked list is circular");
    }
    // TEST 3 - Empty the circular linked list
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[0]...
        result = empty_the_list(c_list);
        exp_count = 0;  // The circular linked list should have been cleared
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, exp_count);
        }
        _print_results(result, "TEST 3: Empty the circular linked list");
    }
    // TEST 4 - Find a node (by position)
    // Big list
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: NULL
        exp_count = 0;  // Using this as a temp var for the time being
        // Assumed Starting State: NULL
        // Insert new any_data into predictable positions
        for (int i = 0; i < ARRAY_LEN - 1; i++)
        {
            result = insert_cdata(c_list, input_arr[i], ARRAY_LEN + 2);  // Append it
            if (RET_SUCCESS == result)
            {
                result = _check_count(c_list, ++exp_count);
            }
            else
            {
                fprintf(stderr, "insert_cdata() failed with %d on index %d\n", result, i);
                break;  // We encountered an error
            }
        }
        _print_results(result, "TEST 4: Find a node (by pos) - Fill the empty circular linked list");
    }
    // Find a node
    // Head Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 1, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos(1) call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[0], temp_node);
            }
        }
        _print_results(result, "TEST 4: Find a node (by pos) - Head node");
    }
    // Middle Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 11, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos(11) call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[10], temp_node);
            }
        }
        _print_results(result, "TEST 4: Find a node (by pos) - Middle node");
    }
    // Tail Node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, ARRAY_LEN - 1, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos(%d) call returned NULL but reported success\n",
                        ARRAY_LEN - 1);
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[ARRAY_LEN - 2], temp_node);
            }
        }
        _print_results(result, "TEST 4: Find a node (by pos) - Tail node");
    }
    // TEST 5 - Remove middle node from the circular linked list
    // Remove a node - middle
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[2]->[3]->[4]->[N]->[0]...
        result = remove_cnode_pos(c_list, 3);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, --exp_count);
        }
        _print_results(result, "TEST 5: Remove middle node - Actual removal");
    }
    // Verify the prev node is unchanged
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[3]->[4]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 2, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[1], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove middle node - Verify previous node unchanged");
    }
    // Verify the new position node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[3]->[4]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 3, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[3], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove middle node - Verify node position changed");
    }
    // Verify the new next node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[3]->[4]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 4, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[4], temp_node);
            }
        }
        _print_results(result, "TEST 5: Remove middle node - Verify new next node unchanged");
    }
    // TEST 6 - Remove head node from the circular linked list
    // Remove a node - head
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [0]->[1]->[3]->[4]->[N]->[0]...
        result = remove_cnode_pos(c_list, 1);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, --exp_count);
        }
        _print_results(result, "TEST 6: Remove head node - Actual removal");
    }
    // Verify the new position node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->[N]->[0]...
        temp_node = find_cnode_pos(c_list, 1, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else if (temp_node != c_list->head_ptr)
            {
                fprintf(stderr, "The struct's head node was not updated\n");
                result = RET_ERROR;
            }
            else
            {
                result = _compare_test_results(input_arr[1], temp_node);
            }
        }
        _print_results(result, "TEST 6: Remove head node - Verify new head node");
    }
    // Verify the new next node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->[N]->[1]...
        temp_node = find_cnode_pos(c_list, 2, &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[3], temp_node);
            }
        }
        _print_results(result, "TEST 6: Remove head node - Verify new next node unchanged");
    }
    // TEST 7 - Remove tail node from the circular linked list
    // Remove a node - head
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[42]->[1]...
        result = remove_cnode_pos(c_list, exp_count);
        if (RET_SUCCESS == result)
        {
            result = _check_count(c_list, --exp_count);
        }
        _print_results(result, "TEST 7: Remove tail node - Actual removal");
    }
    // Verify new tail node
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[1]...
        temp_node = find_cnode_pos(c_list, exp_count, &result);  // Get the tail node
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_pos() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else if (temp_node != c_list->tail_ptr)
            {
                fprintf(stderr, "The struct's tail node was not updated\n");
                result = RET_ERROR;
            }
            else
            {
                result = _compare_test_results(input_arr[ARRAY_LEN - 3], temp_node);
            }
        }
        _print_results(result, "TEST 7: Remove tail node - Verify new tail node");
    }
    // TEST 8 - Find a node (by value)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[1]...
        temp_node = find_cnode_val(c_list, input_arr[12], &result);
        if (RET_SUCCESS == result)
        {
            if (!temp_node)
            {
                fprintf(stderr, "The find_cnode_val() call returned NULL but reported success\n");
                result = RET_ERROR;  // This counts as a fail
            }
            else
            {
                result = _compare_test_results(input_arr[12], temp_node);
            }
        }
        _print_results(result, "TEST 8: Find a node (by value)");
    }
    // TEST 9 - Find a missing node (by position)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[1]...
        temp_node = find_cnode_pos(c_list, exp_count * 2, &result);
        if (RET_NOT_FOUND == result)
        {
            result = RET_SUCCESS;  // Counts as a success
        }
        else if (RET_SUCCESS == result)
        {
            fprintf(stderr, "The find_cnode_pos() succeeded when it should not have\n");
            result = RET_ERROR;  // This counts as a fail
        }
        _print_results(result, "TEST 9: Find a missing node (by position)");
    }
    // TEST 10 - Find a node (by value)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[1]...
        temp_node = find_cnode_val(c_list, input_arr[0], &result);
        if (RET_NOT_FOUND == result)
        {
            result = RET_SUCCESS;  // Counts as a success
        }
        else if (RET_SUCCESS == result)
        {
            fprintf(stderr, "The find_cnode_val() succeeded when it should not have\n");
            result = RET_ERROR;  // This counts as a fail
        }
        _print_results(result, "TEST 10: Find a missing node (by value)");
    }
    // TEST 11 - Sort (by size)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: [1]->[3]->[4]->...->[41]->[1]...
        result = sort_clist(c_list, compare_any_data_siz);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to sort_clist(clist, sort-by-siz) failed\n");
        }
        else
        {
            temp_node = c_list->head_ptr;  // Check the order
            for (int i = 0; i < c_list->entries - 1; i++)  // -1 to avoid tail->head comparison
            {
                if (temp_node->data_ptr->d_size > temp_node->next_ptr->data_ptr->d_size)
                {
                    fprintf(stderr, "The circular linked list is not sorted, by size, "
                            "in ascending order\n");
                    _print_any_data(temp_node->data_ptr);
                    _print_any_data(temp_node->next_ptr->data_ptr);
                    result = RET_ERROR;
                    break;  // We encountered a failure
                }
                temp_node = temp_node->next_ptr;  // Next node
            }
            // do
            // {
            //     if (temp_node->data_ptr->d_size > temp_node->next_ptr->data_ptr->d_size)
            //     {
            //         fprintf(stderr, "The circular linked list is not sorted, by size, "
            //                 "in ascending order\n");
            //         _print_any_data(temp_node->data_ptr);
            //         _print_any_data(temp_node->next_ptr->data_ptr);
            //         result = RET_ERROR;
            //         break;  // We encountered a failure
            //     }
            //     temp_node = temp_node->next_ptr;  // Next node
            // } while (temp_node != c_list->head_ptr && temp_node);
        }
        _print_results(result, "TEST 11: Sort (by size)");
    }
    // TEST 12 - Sort (by pointer)
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: ???
        result = sort_clist(c_list, compare_any_data_ptr);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to sort_clist(clist, sort-by-ptr) failed\n");
        }
        else
        {
            temp_node = c_list->head_ptr;  // Check the order
            for (int i = 0; i < c_list->entries - 1; i++)  // -1 to avoid tail->head comparison
            {
                if (temp_node->data_ptr->d_ptr >= temp_node->next_ptr->data_ptr->d_ptr)
                {
                    fprintf(stderr, "FAILED ON %d\n", i);  // DEBUGGING
                    fprintf(stderr, "The circular linked list is not sorted, by size, "
                            "in ascending order\n");
                    _print_any_data(temp_node->data_ptr);
                    _print_any_data(temp_node->next_ptr->data_ptr);
                    result = RET_ERROR;
                    break;  // We encountered a failure
                }
                temp_node = temp_node->next_ptr;  // Next node
            }
            // do
            // {
            //     if (temp_node->data_ptr->d_ptr >= temp_node->next_ptr->data_ptr->d_ptr)
            //     {
            //         fprintf(stderr, "The circular linked list is not sorted, by pointer, "
            //                 "in ascending order\n");
            //         result = RET_ERROR;
            //         break;  // We encountered a failure
            //     }
            //     temp_node = temp_node->next_ptr;  // Next node
            // } while (temp_node != c_list->head_ptr && temp_node);
        }
        _print_results(result, "TEST 12: Sort (by pointer)");
    }
    // TEST 13 - Delete the circular linked list
    if (RET_SUCCESS == result)
    {
        // Assumed Starting State: Doesn't matter because it's getting torn down
        result = delete_clist(c_list);
        if (RET_SUCCESS == result)
        {
            c_list = NULL;
        }
        _print_results(result, "TEST 13: Delete the circular linked list");
    }

    // DONE
    if (c_list)
    {
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "You may have failed but let's clean up the linked list anyway\n");
        }
        delete_clist(c_list);
        c_list = NULL;
    }
    if (input_arr)
    {
        _clear_array(input_arr);
        input_arr = NULL;
    }
}


return_value _check_count(circular_list_ptr c_list, unsigned int exp_count)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!c_list)
    {
        retval = RET_INV_PARAM;
    }

    // CHECK COUNT
    if (RET_SUCCESS == retval)
    {
        if (c_list->entries != exp_count)
        {
            fprintf(stderr, "Entry count should be %d but it's %d\n",
                    exp_count, c_list->entries);
            retval = RET_ERROR;  // This counts as a fail
        }
    }

    // DONE
    return retval;
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


return_value _compare_test_results(any_data_ptr input, circular_node_ptr test_result)
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
