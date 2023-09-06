#include "8-02-sort_functions.h"
#include <string.h>  // strncmp()


/**************************************************************************************************/
/********************************* INTERNAL FUNCTION DECLARATIONS *********************************/
/**************************************************************************************************/

/*
 *  Compares memory, up to d_size bytes, between left_data and right_data.
 *  Returns true if left_data < right_data.  Returns false for all other conditions.
 */
bool _compare_data_size(void *left_data, void *right_data, unsigned int d_size);

/*
 *  Intelligently compares left_data to right_data based on d_type.  The size is used to compare
 *  data of variable length (e.g., char*, void*).  Returns true if left_data < right_data.
 *  Returns false for all other conditions.
 */
bool _compare_data_type(void *left_data, void *right_data, data_type d_type, unsigned int d_size);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


bool compare_any_data_ptr(any_data_ptr left_data, any_data_ptr right_data)
{
    // LOCAL VARIABLES
    bool results = false;  // Return true if left_data < right_data

    // INPUT VALIDATION
    if (left_data && right_data)
    {
        // COMPARE THEM
        if (left_data->d_ptr < right_data->d_ptr)
        {
            results = true;
        }
    }

    // DONE
    return results;
}


bool compare_any_data_siz(any_data_ptr left_data, any_data_ptr right_data)
{
    // LOCAL VARIABLES
    bool results = false;         // Return true if left_data < right_data

    // INPUT VALIDATION
    if (left_data && right_data)
    {
        // COMPARE THEM
        if (left_data->d_size == right_data->d_size)
        {
            results = _compare_data_size(left_data->d_ptr, right_data->d_ptr, left_data->d_size);
        }
        else if (left_data->d_size < right_data->d_size)
        {
            results = true;  // Left data is smaller than right data
        }
    }

    // DONE
    return results;
}


bool compare_any_data_val(any_data_ptr left_data, any_data_ptr right_data)
{
    // LOCAL VARIABLES
    bool results = false;         // Return true if left_data < right_data
    unsigned int small_size = 0;  // Smallest size between variable-length data types

    // INPUT VALIDATION
    if (left_data && right_data)
    {
        // COMPARE THEM
        small_size = (left_data->d_size <= right_data->d_size) ? \
                     left_data->d_size : right_data->d_size;
        // Same data type
        if (left_data->d_type == right_data->d_type)
        {
            results = _compare_data_type(left_data->d_ptr, right_data->d_ptr, left_data->d_type,
                                         small_size);
        }
        else
        {
            results = _compare_data_size(left_data->d_ptr, right_data->d_ptr, small_size);
        }
    }

    // DONE
    return results;
}


void swap_data(any_data_ptr *left_data, any_data_ptr *right_data)
{
    any_data_ptr temp_data = NULL;  // Use this var for swapping
    if (left_data && right_data)
    {
        temp_data = *left_data;
        *left_data = *right_data;
        *right_data = temp_data;
    }
}


void swap_node(list_node_ptr *left_node, list_node_ptr *right_node)
{
    list_node_ptr temp_node = NULL;  // Use this var for swapping
    if (left_node && right_node)
    {
        temp_node = *left_node;
        *left_node = *right_node;
        *right_node = temp_node;
    }
}


/**************************************************************************************************/
/*************************************** INTERNAL FUNCTIONS ***************************************/
/**************************************************************************************************/


bool _compare_data_size(void *left_data, void *right_data, unsigned int d_size)
{
    // LOCAL VARIABLES
    bool results = false;  // Return true if left_data < right_data

    // INPUT VALIDATION
    if (left_data && right_data && d_size > 0)
    {
        if (0 > memcmp(left_data, right_data, d_size))
        {
            results = true;
        }
    }

    // DONE
    return results;
}


bool _compare_data_type(void *left_data, void *right_data, data_type d_type, unsigned int d_size)
{
    // LOCAL VARIABLES
    bool results = false;  // Return true if left_data < right_data

    // INPUT VALIDATION
    if (left_data && right_data && d_size > 0)
    {
        // COMPARE IT
        switch (d_type)
        {
            case CHAR_DT:
                if (*((char*)left_data) < *((char*)right_data))
                {
                    results = true;
                }
                break;
            case DOUBLE_DT:
                if (*((double*)left_data) < *((double*)right_data))
                {
                    results = true;
                }
                break;
            case FLOAT_DT:
                if (*((float*)left_data) < *((float*)right_data))
                {
                    results = true;
                }
                break;
            case INT_DT:
                if (*((float*)left_data) < *((float*)right_data))
                {
                    results = true;
                }
                break;
            case STRING_DT:
                if (0 > strncmp(left_data, right_data, d_size))
                {
                    results = true;
                }
                break;
            case VOID_DT:
                if (0 > _compare_data_size(left_data, right_data, d_size))
                {
                    results = true;
                }
                break;
            default:
                break;  // Unsupported data type
        }
    }

    // DONE
    return results;
}
