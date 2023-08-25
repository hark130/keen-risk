#include "8-04-hash_table-solution.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


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
    return_value result = RET_SUCCESS;  // Out parameter for certain library calls
    any_data key;                       // Temp key struct
    any_data value;                     // Temp value struct
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
        else
        {
            printf("The table now has %d entries.\n", table->entries);
        }
    }
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
        else
        {
            printf("The table now has %d entries.\n", table->entries);
        }
    }
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
        else
        {
            printf("The table now has %d entries.\n", table->entries);
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
