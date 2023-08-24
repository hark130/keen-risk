#include "8-04-hash_table-solution.h"
#include <errno.h>  // errno
#include <stdio.h>  // fprintf()
#include <stdlib.h>  // calloc(), malloc()
#include <string.h>  // strerror()

#define THIS_FILE "08-04-hash_table-solution.c"
#define HARKLE_ERROR(funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", \
                                                 THIS_FILE, #funcName, #msg); } while (0);
#define HARKLE_ERRNO(funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - \
                                                                 %s() returned errno:\t%s\n", \
                                                                 THIS_FILE, #funcName, \
                                                                 strerror(errorNum)); }
#define HARKLE_WARNG(funcName, msg) do { fprintf(stderr, "¿¿¿WARNING??? - %s - %s() - %s!\n", \
                                                 THIS_FILE, #funcName, #msg); } while (0);


typedef struct _entry_pair
{
    any_data_ptr key;
    any_data_ptr value;
} entry_pair, *entry_pair_ptr;



/**************************************************************************************************/
/********************************* INTERNAL FUNCTION DECLARATIONS *********************************/
/**************************************************************************************************/

/*
 *  Allocate a hash table of a given capacity.  Hash table will contain an array of entry_pair
 *  objects.  This function does not validate input, only results.
 */
hash_table_ptr _create_hash_table(int capacity, return_value_ptr result);

/*
 *  Free all table entries and then free the table.  Error response will be "best effort".
 */
return_value _destroy_table(hash_table_ptr old_table);

/*
 *  Frees the table_ptr and zeroizes all members.  Does not concern itself with the contents of
 *  the table_ptr member.
 */
return_value _destroy_table_struct(hash_table_ptr old_table);

/*
 *  Validate the pointer and all members of the struct.
 */
return_value _validate_table(hash_table_ptr table);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/


hash_table_ptr create_hash_table(int capacity, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    hash_table_ptr new_table = NULL;    // Dynamically allocated hash table
    int errnum = 0;                     // Errno value

    // INPUT VALIDATION
    if (capacity < 1)
    {
        retval = RET_INV_PARAM;
    }
    else if (!result)
    {
        retval = RET_INV_PARAM;
    }

    // CREATE IT
    if (RET_SUCCESS == retval)
    {
        new_table = _create_hash_table(capacity, &retval);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_table;
}


any_data_ptr find_value(hash_table_ptr table, void *raw_data, data_type raw_data_type,
                        unsigned int raw_data_size, return_value_ptr result)
{

}


return_value add_key(hash_table_ptr table, void *raw_data, data_type raw_data_type,
                     unsigned int raw_data_size)
{

}


return_value delete_key(hash_table_ptr table, any_data_ptr key)
{

}


return_value destroy_table(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;    // Function call results

    // INPUT VALIDATION
    retval = _validate_table(table);

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        retval = _destroy_table(table);
    }

    // DONE
    return retval;
}


/**************************************************************************************************/
/*************************************** INTERNAL FUNCTIONS ***************************************/
/**************************************************************************************************/


/*
 *  Allocate a hash table of a given capacity.  Hash table will contain an array of entry_pair
 *  pointers.  This function does not validate input, only results.
 */
hash_table_ptr _create_hash_table(int capacity, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    hash_table_ptr new_table = NULL;    // Dynamically allocated hash table
    int errnum = 0;                     // Errno value

    // CREATE IT
    // Allocate the struct pointer
    new_table = malloc(sizeof(hash_table));
    if (!new_table)
    {
        errnum = errno;
        HARKLE_ERRNO(malloc, errnum);
        retval = RET_ERROR;
    }
    // Fill the struct
    if (retval == RET_SUCCESS)
    {
        new_table->table_ptr = calloc(capacity, sizeof(entry_pair_ptr));
        if (!(new_table->table_ptr))
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            retval = RET_ERROR;
        }
        new_table->entries = 0;  // Empty hash table
        new_table->capacity = capacity;  // That's what the caller wants
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_table;
}


/*
 *  Zeroize the data and free the data pointer.  Then zeroize the pointer, type and size.
 */
return_value _destroy_any_data(any_data_ptr old_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!old_data)
    {
        retval = RET_INV_PARAM;
    }

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        // void *d_ptr;          // Pointer to data
        if (old_data->d_ptr)
        {
            memset(old_data->d_ptr, old_data->d_size, 0x0);
            free(old_data->d_ptr);
            old_data->d_ptr = NULL;
        }
        // data_type d_type;     // The data type of the data
        old_data->d_type = NULL_DT;
        // unsigned int d_size;  // Total size of the data, in memory, as bytes
        old_data->d_size = 0;
    }

    // DONE
    return retval;
}


/*
 *  Free the any_data key, any_data value, and then the entry_pair.
 */
return_value _destroy_entry_pair(entry_pair_ptr old_entry)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;    // Function call results
    return_value temp_ret = RET_SUCCESS;  // Temp reval var

    // INPUT VALIDATION
    if (!old_entry)
    {
        retval = RET_INV_PARAM;
    }

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        if (old_entry->key)
        {
            temp_ret = _destroy_any_data(old_entry->key);
            if (temp_ret != RET_SUCCESS)
            {
                retval = temp_ret;
            }
            old_entry->key = NULL;
        }
        if (old_entry->value)
        {
            temp_ret = _destroy_any_data(old_entry->value);
            if (temp_ret != RET_SUCCESS)
            {
                retval = temp_ret;
            }
            old_entry->value = NULL;
        }
    }

    // DONE
    return retval;
}


return_value _destroy_table(hash_table_ptr old_table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;    // Function call results
    return_value temp_ret = RET_SUCCESS;  // Temp reval var
    entry_pair_ptr *table_arr = NULL;     // Array of entry_pair pointers
    entry_pair_ptr temp_entry = NULL;     // Temp hash table entry var

    // INPUT VALIDATION
    retval = _validate_table(old_table);

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        table_arr = (entry_pair_ptr*)old_table->table_ptr;
        // Destroy all entries
        for (int i = 0; i < old_table->capacity; i++)
        {
            temp_entry = (*(table_arr + i));
            if (temp_entry)
            {
                temp_ret = _destroy_entry_pair(temp_entry);
                if (temp_ret != RET_SUCCESS)
                {
                    retval = temp_ret;
                }
            }
        }
        // Destroy the table
        temp_ret = _destroy_table_struct(old_table);
        if (temp_ret != RET_SUCCESS)
        {
            retval = temp_ret;
        }
        free(old_table);
    }

    // DONE
    return retval;
}


/*
 *  Frees the table_ptr and zeroizes all members.  Does not concern itself with the contents of
 *  the table_ptr member.
 */
return_value _destroy_table_struct(hash_table_ptr old_table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_table(old_table);

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        // void *table_ptr;  // Pointer to the array of entries
        if (old_table->table_ptr)
        {
            free(old_table->table_ptr);
            old_table->table_ptr = NULL;
        }
        // int entries;      // Number of entries in table_ptr
        old_table->entries = 0;
        // int capacity;     // Number of indices in the table_ptr array
        old_table->capacity = 0;
    }

    // DONE
    return retval;
}


return_value _validate_table(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!table)
    {
        retval = RET_INV_PARAM;
    }
    // void *table_ptr;  // Pointer to the array of entries
    else if (!(table->table_ptr))
    {
        retval = RET_INV_PARAM;
    }
    // int entries;      // Number of entries in table_ptr
    else if (table->entries < 0)
    {
        retval = RET_INV_PARAM;
    }
    // int capacity;     // Number of indices in the table_ptr array
    else if (table->capacity < 1)
    {
        retval = RET_INV_PARAM;
    }

    // DONE
    return retval;
}
