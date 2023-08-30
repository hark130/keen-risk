/*
 *  DESCRIPTION:
 *      This source file contains unit tests for student lab 8-04-2.
 *
 *  BUILD:
 *      The easiest way to build these unit tests is to copy all the files into a dir and:
 *      gcc -o 8-04-2-lab.bin 8-04-2-hash_table-main.c 8-04-hash_functions.c 8-04-hash_table-lab.c
 *
 *      BONUS: Stop copy pasting gcc commands and create a Makefile.  See: JQS 6-17.
 *
 *  TEST:
 *      ./8-04-2-lab.bin  # Read the output.  Failures go to stderr.  Read the test code.
 *      # Be sure to build and run the solution through ASAN.  See: JQS 6-16 and 6-21.
 *      # Also use Valgrind to identify issues with memory management.  See: JQS 6-21.
 */

#include "8-04-hash_table.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


#define GOOD_JOB "\xE2\x9C\x94"          // Check mark?
#define BAD_JOB "X"                      // Fail
#define COLLISION_VALUE (int)0xFEEDC0DE  // Key value used to create hash collisions


void _print_results(return_value result, const char *message);

void _set_char(any_data_ptr data_struct, char *data);

void _set_double(any_data_ptr data_struct, double *data);

void _set_float(any_data_ptr data_struct, float *data);

void _set_int(any_data_ptr data_struct, int *data);

void _set_string(any_data_ptr data_struct, char *data);


int main()
{
    // LOCAL VARIABLES
    hash_table_ptr table = NULL;            // Hash table
    int start_cap = 10;                     // Hash table starting capacity
    float start_thresh = 0.75;              // Hash table threshold
    return_value result = RET_SUCCESS;      // Out parameter for certain library calls
    any_data key;                           // Temp key struct
    any_data value;                         // Temp value struct
    any_data_ptr found_value = NULL;        // Temp value struct
    float temp_float = 0;                   // Temp var to use for any_data.d_ptr
    int temp_int1 = 0;                      // Temp var to use for any_data.d_ptr
    int temp_int2 = 0;                      // Temp var to use for any_data.d_ptr
    unsigned int num_entries = 0;           // Store the number of table entries at run-time
    int busy_int = 0;                       // Set this up once, use many
    any_data busy_key;                      // Set this up once, use many
    any_data busy_value;                    // Set this up once, use many
    char busy_str[sizeof(int) + 1] = {0};   // Char array for hash collisions

    // SETUP
    fprintf(stdout, "Running tests from %s\n", __FILE__);
    // Busy key:value pair
    busy_int = COLLISION_VALUE;  // Use this value, in memory, to create a hash collision
    memcpy(busy_str, &busy_int, sizeof(int));  // Copy the raw memory into the char buffer
    _set_string(&busy_key, busy_str);  // String memory should now match int memory
    busy_key.d_size -= 1;  // Accounting for _set_string()'s nul-char inclusion
    _set_string(&busy_value, "This input value is being used to create and test hash collisions!");

    // CREATE
    table = create_hash_table(start_cap, start_thresh, &result);
    if (!table)
    {
        fprintf(stderr, "The call to create_hash_table() returned NULL\n");
        if (RET_SUCCESS == result)
        {
            result = RET_ERROR;  // Manually failing this test since the call didn't do it
        }
    }
    _print_results(result, "Creating a hash table");

    // ADD
    // Key 1
    if (RET_SUCCESS == result)
    {
        temp_int1 = COLLISION_VALUE;
        _set_int(&key, &temp_int1);
        temp_int2 = 0xDEADC0DE;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
        _print_results(result, "Adding a key");
    }
    // Add a duplicate key (expect error)
    if (RET_SUCCESS == result)
    {
        num_entries = table->entries;  // Store the current number of entries
        // Same key, different value
        temp_int1 = COLLISION_VALUE;
        _set_int(&key, &temp_int1);
        temp_int2 = 0xBADC0DE5;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        if (RET_DUPE_ENTRY != result)
        {
            fprintf(stderr, "add_key() failed to detect a duplicate key with %d\n", result);
            fprintf(stderr, "It returned %d instead\n", result);
            result = RET_ERROR;  // Let's stop testing
        }
        else
        {
            result = RET_SUCCESS;  // That was the expected result so let's continue
        }
        if (num_entries != table->entries)
        {
            fprintf(stderr, "add_key() erroneously added a duplicate entry\n");
            result = RET_ERROR;  // Let's stop testing
        }
        _print_results(result, "Attempting to add a duplicate key");
    }
    // Add a hash collision (expect success)
    if (RET_SUCCESS == result)
    {
        num_entries = table->entries;  // Store the current number of entries
        result = add_key(table, &busy_key, &busy_value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "add_key() failed to handle a hash collision with %d\n", result);
        }
        if (table->entries != (num_entries + 1))
        {
            fprintf(stderr, "add_key() failed to add a new entry\n");
            result = RET_ERROR;  // Let's stop testing
        }
        _print_results(result, "Handling one hash collision");
    }
    // Add ANOTHER hash collision (expect success)
    if (RET_SUCCESS == result)
    {
        num_entries = table->entries;  // Store the current number of entries
        temp_int1 = COLLISION_VALUE;  // Use this value, in memory, to create a hash collision
        memcpy(&temp_float, &temp_int1, sizeof(int));  // Copy the raw memory into the float var
        _set_float(&key, &temp_float);  // Float memory should now match int memory
        _set_string(&value, "This input should *also* create a HASH COLLISION!");
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "add_key() failed to handle a hash collision with %d\n", result);
            result = RET_ERROR;  // Let's stop testing
        }
        if (table->entries != (num_entries + 1))
        {
            fprintf(stderr, "add_key() failed to add a new entry\n");
            result = RET_ERROR;  // Let's stop testing
        }
        _print_results(result, "Handling a second hash collision");
    }
    // FIND
    // Managing hash-collision insertions is one thing.  But can we find it?
    if (RET_SUCCESS == result)
    {
        found_value = find_value(table, &busy_key, &result);
        if (!found_value || RET_NOT_FOUND == result)
        {
            fprintf(stderr, "find_value() failed to retrieve the hash collision entry\n");
        }
        else if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to find_value(hash_collision) failed with: %d\n", result);
        }
        else if (found_value->d_type != busy_value.d_type
                 || found_value->d_size != busy_value.d_size
                 || 0 != strncmp(found_value->d_ptr, busy_value.d_ptr, busy_value.d_size))
        {
            fprintf(stderr, "The value found doesn't match the orignal key's value\n");
        }
        _print_results(result, "Retrieving the first hash collision");
    }
    // DELETE AND FIND (hash collision 1-of-2)
    if (RET_SUCCESS == result)
    {
        num_entries = table->entries;  // Store the current number of entries
        // Delete
        result = delete_key(table, &busy_key);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "Call to delete_key() didn't delete the hash collision key\n");
        }
        else if (table->entries != num_entries - 1)
        {
            fprintf(stderr, "The tables entry counter did not decrement after delete_key()\n");
        }
        else
        {
            found_value = find_value(table, &busy_key, &result);
            if (found_value)
            {
                fprintf(stderr, "The previous call to delete_key(hash_collision) lied\n");
            }
            else if (RET_NOT_FOUND != result)
            {
                fprintf(stderr, "Result was %d instead of 'not found'.\n", result);
            }
            else
            {
                result = RET_SUCCESS;  // NULL found value? 'Not found' result?  Perfect.
            }
        }
        _print_results(result, "Deleting the first hash collision");
    }

    // DONE
    if (table)
    {
        result = destroy_table(table);
        if (result)
        {
            fprintf(stderr, "destroy_table() failed with %d\n", result);
        }
        table = NULL;
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
