/*
 *  DESCRIPTION:
 *      This source file contains unit tests for student lab 8-04-3.
 *
 *  BUILD:
 *      The easiest way to build these unit tests is to copy all the files into a dir and:
 *      gcc -o 8-04-3-lab.bin 8-04-3-hash_table-main.c 8-04-hash_functions.c 8-04-hash_table-lab.c
 *
 *      BONUS: Stop copy pasting gcc commands and create a Makefile.  See: JQS 6-17.
 *
 *  TEST:
 *      ./8-04-3-lab.bin  # Read the output.  Failures go to stderr.  Read the test code.
 *      # Be sure to build and run the solution through ASAN.  See: JQS 6-16 and 6-21.
 *      # Also use Valgrind to identify issues with memory management.  See: JQS 6-21.
 */

#include "8-04-hash_table.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


#define GOOD_JOB "\xE2\x9C\x94"    // Check mark?
#define BAD_JOB "X"                // Fail
/* PRO TIP: Lower the SPAM_THRESHOLD value (e.g., 1337) if your system can't handle it. */
#define SPAM_THRESHOLD (int)31337  // Num of entries to spam when stress-testing the resize feature


void _print_results(return_value result, const char *message);

void _set_char(any_data_ptr data_struct, char *data);

void _set_double(any_data_ptr data_struct, double *data);

void _set_float(any_data_ptr data_struct, float *data);

void _set_int(any_data_ptr data_struct, int *data);

void _set_string(any_data_ptr data_struct, char *data);


int main()
{
    // LOCAL VARIABLES
    hash_table_ptr table = NULL;         // Hash table
    int tmp_cap = 23;                    // Temp var for hash table starting capacity
    float tmp_thresh = 0.75;             // Temp var for hash table threshold
    float cur_load_factor = 0.0;         // Calucate the current load factor at "test time"
    return_value result = RET_SUCCESS;   // Out parameter for certain library calls
    return_value tmp_res = RET_SUCCESS;  // Temporary result value (for cleanup)
    any_data key;                        // Temp key struct
    any_data value;                      // Temp value struct
    any_data_ptr found_value = NULL;     // Temp value struct
    int temp_int1 = 0;                   // Temp var to use for any_data.d_ptr
    int temp_int2 = 0;                   // Temp var to use for any_data.d_ptr
    unsigned int cur_entries = 0;        // Store the number of table entries at run-time
    unsigned int exp_entries = 0;        // Expected number of entries (exact)
    unsigned int cur_cap = 0;            // Store the number of table entries at run-time
    unsigned int exp_cap = 0;            // Expected hash table capacity (minimum)
    // It's ok to wait until an addition will cause a resize but it shouldn't happen twice in a row
    int num_thresh_fails = 0;            // Keep track of threshold violations

    // SETUP
    fprintf(stdout, "Running tests from %s\n", __FILE__);

    /* TEST 1: Barely trigger a resize. */
    // CREATE
    tmp_cap = 2;  // Abnormally small for "small" test
    tmp_thresh = 0.4;  // Abnormally small for "small" test
    table = create_hash_table(tmp_cap, tmp_thresh, &result);
    if (!table)
    {
        fprintf(stderr, "The call to create_hash_table() returned NULL\n");
        if (RET_SUCCESS == result)
        {
            result = RET_ERROR;  // Manually failing this test since the call didn't do it
        }
    }
    _print_results(result, "Creating a hash table (Test 1)");

    // ADD
    // This should not trigger a resize
    if (RET_SUCCESS == result)
    {
        // Store current values
        cur_entries = table->entries;  // Store the current number of entries
        cur_cap = table->capacity;  // Store the current hash table capacity
        // Add an entry`
        _set_string(&key, "Normal add");
        _set_string(&value, "This should not trigger a resize");
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
        else
        {
            if (table->entries != cur_entries + 1)
            {
                fprintf(stderr, "The call to add_key() failed to update bookkeeping\n");
                result = RET_ERROR;  // Manually failing this test
            }
            if (table->capacity != cur_cap)
            {
                fprintf(stderr, "This addition should not have triggered a resize\n");
                result = RET_ERROR;  // Manually failing this test
            }
        }
        _print_results(result, "One key should not make the load factor exceed the threshold");
    }
    // Just enough to trigger a resize
    if (RET_SUCCESS == result)
    {
        // Store current values
        cur_entries = table->entries;  // Store the current number of entries
        cur_cap = table->capacity;  // Store the current hash table capacity
        // Add an entry
        temp_int1 = 0xBE600D;
        _set_int(&key, &temp_int1);
        temp_int2 = 0xD0600D;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
        else
        {
            if (table->entries != cur_entries + 1)
            {
                fprintf(stderr, "The call to add_key() failed to update bookkeeping\n");
                result = RET_ERROR;  // Manually failing this test
            }
            if (table->capacity < (cur_entries * 2))
            {
                fprintf(stderr, "The hash table failed to at least double capacity\n");
                result = RET_ERROR;  // Manually failing this test
            }
        }
        _print_results(result, "Adding one key which should trigger a resize");
    }

    // FIND
    // Find that one entry that triggered the resize
    if (RET_SUCCESS == result)
    {
        found_value = find_value(table, &key, &result);
        if (!found_value || RET_NOT_FOUND == result)
        {
            fprintf(stderr, "find_value() failed to retrieve the recent addition\n");
        }
        else if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to find_value(new_key) failed with: %d\n", result);
        }
        else if (found_value->d_type != value.d_type
                 || found_value->d_size != value.d_size
                 || 0 != memcmp(found_value->d_ptr, value.d_ptr, value.d_size))
        {
            fprintf(stderr, "The value found doesn't match the orignal key's value\n");
        }
        _print_results(result, "Finding the key that triggered the resize");
    }

    // DESTROY THAT TABLE
    if (RET_SUCCESS == result)
    {
        result = destroy_table(table);
        table = NULL;
        _print_results(result, "Destroying a hash table (Test 1)");
    }


    /* TEST 2: Spam that table! */
    // CREATE
    if (RET_SUCCESS == result)
    {
        // This hash table creation is a bit more realistic
        tmp_cap = 23;       // Prime numbers are the best choices for capacity
        tmp_thresh = 0.75;  // Good "average" threshold
        table = create_hash_table(tmp_cap, tmp_thresh, &result);
        if (!table)
        {
            fprintf(stderr, "The call to create_hash_table() returned NULL\n");
            if (RET_SUCCESS == result)
            {
                result = RET_ERROR;  // Manually failing this test since the call didn't do it
            }
        }
        _print_results(result, "Creating another hash table (Test 2)");
    }

    // VALIDATE TEST CONDITIONS
    if (RET_SUCCESS == result)
    {
        // Validate test
        if (SPAM_THRESHOLD < (table->capacity * 4))
        {
            fprintf(stderr, "The spam threshold is too low."
                    "  It's %d but it should be greater than %d.\n"
                    "Who changed it?!\n", SPAM_THRESHOLD, table->capacity * 4);
            result = RET_ERROR;  // SPAM_THRESHOLD is too small.  Increase it!
        }
        _print_results(result, "Verifying SPAM_THRESHOLD is large enough");
    }

    // SPAM ENTRIES
    if (RET_SUCCESS == result)
    {
        // Store current values
        cur_cap = table->capacity;  // Store the current hash table capacity

        // Spam it!
        for (int i = 1; i <= SPAM_THRESHOLD; i++)
        {
            cur_entries = table->entries;  // Store the current number of entries
            // Add an entry
            temp_int1 = i;
            _set_int(&key, &temp_int1);
            temp_int2 = i + 1;
            _set_int(&value, &temp_int2);    
            result = add_key(table, &key, &value);
            if (RET_SUCCESS != result)
            {
                fprintf(stderr, "The call to add_key(spam #%d) failed with: %d\n", i, result);
            }
            else
            {
                // Verify entry count was incremented
                if (table->entries != cur_entries + 1)
                {
                    fprintf(stderr,
                            "The call to add_key(spam #%d) failed to update bookkeeping\n", i);
                    result = RET_ERROR;  // Manually failing this test
                }
                // Verify the table's load value never exceeds the threshold twice in a row
                cur_load_factor = (float)table->entries / table->capacity;
                if (cur_load_factor > tmp_thresh)
                {
                    if (num_thresh_fails > 0)
                    {
                        fprintf(stderr,
                                "The hash table's load factor %0.2f exceeds the threshold %0.2f\n",
                                cur_load_factor, tmp_thresh);
                        result = RET_ERROR;  // Manually failing this test
                    }
                    else
                    {
                        num_thresh_fails++;  // The next addition should cause a resize
                    }
                }
                else
                {
                    num_thresh_fails = 0;  // Reset the counter since the load factor is good
                }
            }
            if (RET_SUCCESS != result)
            {
                break;  // Encountered a failure so stop testing.
            }
        }
        _print_results(result, "Spamming the hash table");
    }

    // FIND THAT SPAM
    if (RET_SUCCESS == result)
    {
        // Find that spam!
        for (int i = 1; i <= SPAM_THRESHOLD; i++)
        {
            // Setup the expected key:value pair
            temp_int1 = i;
            _set_int(&key, &temp_int1);
            temp_int2 = i + 1;
            _set_int(&value, &temp_int2);
            // Find that key
            found_value = find_value(table, &key, &result);
            if (!found_value || RET_NOT_FOUND == result)
            {
                fprintf(stderr, "find_value() failed to retrieve a spam entry (%d:%d)\n",
                        temp_int1, temp_int2);
            }
            else if (RET_SUCCESS != result)
            {
                fprintf(stderr, "The call to find_value(spam_key=%d) failed with: %d\n",
                        temp_int1, result);
            }
            else if (found_value->d_type != value.d_type
                     || found_value->d_size != value.d_size
                     || 0 != memcmp(found_value->d_ptr, value.d_ptr, value.d_size))
            {
                fprintf(stderr, "The value found doesn't match the orignal spam key's value\n");
            }
        }

        _print_results(result, "Finding every last spam entry");
    }

    // DONE
    if (table)
    {
        tmp_res = destroy_table(table);
        table = NULL;
        if (RET_SUCCESS == result)
        {
            result = tmp_res;
        }
        _print_results(result, "Destroying a hash table (Test 2)");
    }
    return result;
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


void _set_char(any_data_ptr data_struct, char *data)
{
    data_struct->d_ptr = data;
    data_struct->d_type = CHAR_DT;
    data_struct->d_size = sizeof(char);
}


void _set_double(any_data_ptr data_struct, double *data)
{
    data_struct->d_ptr = data;
    data_struct->d_type = DOUBLE_DT;
    data_struct->d_size = sizeof(double);
}


void _set_float(any_data_ptr data_struct, float *data)
{
    data_struct->d_ptr = data;
    data_struct->d_type = FLOAT_DT;
    data_struct->d_size = sizeof(float);
}


void _set_int(any_data_ptr data_struct, int *data)
{
    data_struct->d_ptr = data;
    data_struct->d_type = INT_DT;
    data_struct->d_size = sizeof(int);
}


void _set_string(any_data_ptr data_struct, char *data)
{
    data_struct->d_ptr = data;
    data_struct->d_type = STRING_DT;
    data_struct->d_size = strlen(data) + 1;
}
