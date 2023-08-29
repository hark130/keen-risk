#include "8-04-hash_table-solution.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


#define GOOD_JOB "\xE2\x9C\x94"  // Check mark?
#define BAD_JOB "X"              // Fail


void _print_results(return_value result, const char *message);

void _set_char(any_data_ptr data_struct, char *data);

void _set_double(any_data_ptr data_struct, double *data);

void _set_float(any_data_ptr data_struct, float *data);

void _set_int(any_data_ptr data_struct, int *data);

void _set_string(any_data_ptr data_struct, char *data);


int main()
{
    // LOCAL VARIABLES
    hash_table_ptr table = NULL;        // Hash table
    int start_cap = 20;                 // Hash table starting capacity
    float start_thresh = 0.75;          // Hash table threshold
    return_value result = RET_SUCCESS;  // Out parameter for certain library calls
    any_data key;                       // Temp key struct
    any_data value;                     // Temp value struct
    any_data_ptr found_value = NULL;    // Temp value struct
    char temp_char = 0;                 // Temp var to use for any_data.d_ptr
    double temp_dble = 0;               // Temp var to use for any_data.d_ptr
    float temp_float = 0;               // Temp var to use for any_data.d_ptr
    int temp_int1 = 0;                  // Temp var to use for any_data.d_ptr
    int temp_int2 = 0;                  // Temp var to use for any_data.d_ptr
    unsigned int num_entries = 0;       // Store the number of table entries at run-time

    // SETUP
    fprintf(stdout, "Running tests from %s\n", __FILE__);

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
        _set_string(&key, "What is 6 x 7?");
        temp_int2 = 42;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        _print_results(result, "Adding a key");
    }
    // Key 2
    if (RET_SUCCESS == result)
    {
        temp_int1 = 16;
        _set_int(&key, &temp_int1);
        temp_int2 = 90;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        _print_results(result, "Adding a second key");
    }
    // Key 3
    if (RET_SUCCESS == result)
    {
        temp_float = 1/(float)3;
        _set_float(&key, &temp_float);
        temp_dble = 1/(double)7;
        _set_double(&value, &temp_dble);
        result = add_key(table, &key, &value);
        _print_results(result, "Adding a third key");
    }
    // FIND (Key 2)
    if (RET_SUCCESS == result)
    {
        temp_int1 = 16;
        _set_int(&key, &temp_int1);
        temp_int2 = 90;
        _set_int(&value, &temp_int2);
        found_value = find_value(table, &key, &result);
        if (!found_value || RET_NOT_FOUND == result)
        {
            fprintf(stderr, "The call to find_value() failed to find (key %d:value %d)\n",
                    temp_int1, temp_int2);
        }
        else if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to find_value() failed with: %d\n", result);
        }
        else
        {
            temp_int1 = *((int*)found_value->d_ptr);
            if (temp_int1 != temp_int2
                || found_value->d_type != value.d_type
                || found_value->d_size != value.d_size)
            {
                fprintf(stderr, "The value found doesn't match the orignal key's value");
            }
        }
        _print_results(result, "Finding the second key");
    }
    // DELETE AND FIND (Key 3)
    if (RET_SUCCESS == result)
    {
        num_entries = table->entries;  // Store the current number of entries
        _set_string(&key, "What is 6 x 7?");
        // Delete
        result = delete_key(table, &key);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "Call to delete_key() failed to delete key %s\n", (char*)key.d_ptr);
        }
        else if (table->entries != num_entries - 1)
        {
            fprintf(stderr, "The tables entry counter did not decrement after delete_key()\n");
        }
        else
        {
            found_value = find_value(table, &key, &result);
            if (found_value)
            {
                fprintf(stderr, "The previous call to delete_key() appears to have lied\n");
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
        _print_results(result, "Deleting the third key");
    }
    // DELETE ALL ENTRIES
    if (RET_SUCCESS == result)
    {
        result = delete_all_keys(table);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to delete_all_keys() failed with: %d\n", result);
        }
        else if (table->entries > 0)
        {
            fprintf(stderr, "How are there are still %d entries\n", table->entries);
            result = RET_ERROR;  // Manually set
        }
        _print_results(result, "Deleting all hash table entries");
    }
    // FIND (a needle in an empty haystack)
    if (RET_SUCCESS == result)
    {
        temp_int1 = 16;
        _set_int(&key, &temp_int1);
        found_value = find_value(table, &key, &result);
        if (found_value)
        {
            fprintf(stderr, "The call to find_value() found an entry in an 'empty'(?) table\n");
        }
        else if (RET_NOT_FOUND != result)
        {
            fprintf(stderr, "The call to find_value() shoud have resulted in %d instead of %d\n",
                    RET_NOT_FOUND, result);
        }
        else
        {
            result = RET_SUCCESS;  // Manually set
        }
        _print_results(result, "*NOT* finding a needle in an empty haystack");
    }

    // DONE
    if (table)
    {
        result = destroy_table(table);
        _print_results(result, "Destroying a hash table");
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
