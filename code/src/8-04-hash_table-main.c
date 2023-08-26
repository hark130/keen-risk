#include "8-04-hash_table-solution.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


void _set_char(any_data_ptr data_struct, char *data);

void _set_double(any_data_ptr data_struct, double *data);

void _set_float(any_data_ptr data_struct, float *data);

void _set_int(any_data_ptr data_struct, int *data);

void _set_string(any_data_ptr data_struct, char *data);

// NORMAL
// 1 Create & destroy
// 2 find_value() empty table
// 3 add_key() empty table
// 4 add_key() a few entries
// 5 add_key() a few entries, delete one
// 6 add_key() a few entries, delete_all_keys()
// 7 add_key() a few entries, delete_all_keys(), add_key() a few entries
// 8 find_value() on an empty table
// 9 find_value() on a non-empty table (key is missing)
// 10 find_value() on a non-empty table (key is found)

// ERROR
// 1 create() invalid capacity
// 2 create() NULL pointer
// 3 find_value() NULL table
// 4 find_value() NULL table->table_ptr
// 5 find_value() NULL result
// 6 add_key() NULL table
// 7 add_key() NULL table->table_ptr
// 8 add_key() NULL key
// 9 add_key() NULL key->d_ptr
// 10 add_key() 0 key->d_size
// 11 add_key() NULL value
// 12 add_key() NULL value->d_ptr
// 13 add_key() 0 value->d_size
// 14 delete_key() NULL table
// 15 delete_key() NULL table->table_ptr
// 16 delete_key() NULL key
// 17 delete_key() NULL key->d_ptr
// 18 delete_key() 0 key->d_size
// 19 delete_all_keys() NULL table
// 20 delete_all_keys() NULL table->table_ptr
// 21 destroy_table() NULL table
// 22 destroy_table() NULL table->table_ptr


int main()
{
    // LOCAL VARIABLES
    hash_table_ptr table = NULL;        // Hash table
    int start_cap = 20;                 // Hash table starting capacity
    return_value result = RET_SUCCESS;  // Out parameter for certain library calls
    any_data key;                       // Temp key struct
    any_data value;                     // Temp value struct
    any_data_ptr found_value = NULL;    // Temp value struct
    char temp_char = 0;                 // Temp var to use for any_data.d_ptr
    double temp_dble = 0;               // Temp var to use for any_data.d_ptr
    float temp_float = 0;               // Temp var to use for any_data.d_ptr
    int temp_int1 = 0;                  // Temp var to use for any_data.d_ptr
    int temp_int2 = 0;                  // Temp var to use for any_data.d_ptr

    // CREATE
    table = create_hash_table(start_cap, &result);
    if (!table)
    {
        fprintf(stderr, "The call to create_hash_table() returned NULL\n");
        if (result)
        {
            fprintf(stderr, "create_hash_table(): %s\n", strerror(result));
        }
    }

    // ADD
    // Key 1
    if (RET_SUCCESS == result)
    {
        _set_string(&key, "What is 6 x 7?");
        temp_int2 = 42;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
    }
    // Key 2
    if (RET_SUCCESS == result)
    {
        temp_int1 = 16;
        _set_int(&key, &temp_int1);
        temp_int2 = 90;
        _set_int(&value, &temp_int2);
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
    }
    // Key 3
    if (RET_SUCCESS == result)
    {
        temp_float = 1/(float)3;
        _set_float(&key, &temp_float);
        temp_dble = 1/(double)7;
        _set_double(&value, &temp_dble);
        result = add_key(table, &key, &value);
        if (RET_SUCCESS != result)
        {
            fprintf(stderr, "The call to add_key() failed with: %d\n", result);
        }
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
        }
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
