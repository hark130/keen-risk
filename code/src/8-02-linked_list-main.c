#include "8-02-linked_list.h"
#include <stdio.h>   // fprintf()
#include <stdlib.h>  // calloc(), free()
#include <string.h>  // memcpy()

#define ARRAY_LEN (unsigned int)11


/*
 *  Allocates a NULL-terminated array of any_data pointers on the heap.
 *  Allocates any_data struct pointers in each index (except for the last).
 */
any_data_ptr *_initialize_array(unsigned int array_len);

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


int main()
{
    // LOCAL VARIABLES
    any_data_ptr *input_arr = _create_and_fill_array(ARRAY_LEN);

    // DONE
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

/*
 *  Free all any_data_ptrs in the array.  Then free the array.
 */
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
                    fprintf(stderr, "Got character %c\n", tmp_char);  // DEBUGGING
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
    if (any_data_arr)
    {
        for (int i = 0; i < (array_len - 1); i++)
        {
            (*(any_data_arr + i)) = calloc(1, sizeof(any_data));
            if (NULL == (*(any_data_arr + i)))
            {
                break;
            }
        }
    }

    return any_data_arr;
}