#include "8-04-hash_functions.h"
#include "8-04-hash_table-solution.h"
#include <errno.h>    // errno
#include <stdbool.h>  // bool, true, false
#include <stdio.h>    // fprintf(), printf()
#include <stdlib.h>   // calloc(), malloc()
#include <string.h>   // strerror()

#define BAD_INDEX (unsigned int)0xFFFFFFFF
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
 *  Duplicates all contents of key and value in heap-allocated memory.  Does not validate input.
 */
return_value _add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value);

/*
 *  Determine the index of a given input.  Returns BAD_INDEX on error.
 */
unsigned int _calc_index(void *d_ptr, unsigned int d_size, unsigned int capacity);

/*
 *  Compares all aspects of s1 data against s2, starting with the bookkeeping.  Immediately
 *  returns false on the first difference detected.
 */
bool _compare_data(void *s1_data, data_type s1_data_type, unsigned int s1_data_size,
                   any_data_ptr s2_data, return_value_ptr result);

/*
 *  Allocates a new any_data struct on the heap, copies over the source bookkeeping values,
 *  allocates a heap-buffer for the new any_data.d_ptr, and memcpy()s source->d_ptr into the
 *  new buffer.  If any part of the process fails, this function will free() all allocated memory,
 *  updated result, and return NULL.
 */
any_data_ptr _copy_any_data(any_data_ptr source, return_value_ptr result);

/*
 *  Allocate a hash table of a given capacity.  Hash table will contain an array of entry_pair
 *  objects.  This function does not validate input, only results.
 */
hash_table_ptr _create_hash_table(int capacity, return_value_ptr result);

/*
 *  Deletes all entries found in the hash table.
 */
return_value _delete_all_keys(hash_table_ptr table);

/*
 *  Zeroize the data and free the data pointer.  Then zeroize the pointer, type and size.  Then
 *  free the any_data struct pointer.
 */
return_value _destroy_any_data(any_data_ptr old_data);

/*
 *  Free the any_data key, any_data value, and then the entry_pair.
 */
return_value _destroy_entry_pair(entry_pair_ptr old_entry);

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
 *  Finds a key, represented as an any_data struct pointer, in table.  See result for errors.
 */
any_data_ptr _find_any_data_value(hash_table_ptr table, any_data_ptr data, return_value_ptr result);

/*
 *  Calculates the hash (and index) for the input, fetches it from the hash table and validates
 *  the results.  Does not validate input.
 *
 *  RETURNS: The value associated with key (AKA raw_data).
 */
any_data_ptr _find_value(hash_table_ptr table, void *raw_data, data_type raw_data_type,
                         unsigned int raw_data_size, return_value_ptr result);

/*
 *  Fetches an index from table->table_ptr.  Returns NULL if index is empty or on error.
 *  See result value for error reporting.
 */
entry_pair_ptr _get_index(hash_table_ptr table, unsigned int index, return_value_ptr result);

/*
 *  Validates any_data structs on behalf of the library.
 */
return_value _validate_any_data(any_data_ptr data);

/*
 *  Validates entry pair struct pointers on behalf of the library.
 */
return_value _validate_entry_pair(entry_pair_ptr entry);

/*
 *  Validates raw data on behalf of the library.
 */
return_value _validate_raw_data(void *raw_data, data_type raw_data_type,
                                unsigned int raw_data_size);

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


any_data_ptr find_value(hash_table_ptr table, any_data_ptr key, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    entry_pair_ptr entry = NULL;        // The entry pulled from the hash table
    any_data_ptr value = NULL;          // The value from the entry
    unsigned int index = 0;             // Search index

    // INPUT VALIDATION
    // Table
    retval = _validate_table(table);
    // Data
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(key);
    }
    // Result
    if (!result)
    {
        retval = RET_INV_PARAM;
    }

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        value = _find_any_data_value(table, key, &retval);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return value;
}


return_value add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(key);
    }
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(value);
    }

    // ADD IT
    if (RET_SUCCESS == retval)
    {
        retval = _add_key(table, key, value);
    }

    // DONE
    return retval;
}


return_value delete_key(hash_table_ptr table, any_data_ptr key)
{

}


return_value delete_all_keys(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_table(table);

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        retval = _delete_all_keys(table);
    }

    // DONE
    return retval;
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
 *  Adds new_entry to table by hashing new_entry->value, calculating the index based on the hash,
 *  and then adding new_entry to the table->table_ptr.  The new_entry memory will belong to table
 *  so ensure it is heap-allocated.
 */
return_value _add_entry(hash_table_ptr table, entry_pair_ptr new_entry)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    unsigned int index = 0;             // new_entry->value index, based on the hash
    any_data_ptr temp_data_ptr = NULL;  // Temp any_data_ptr for detecting collisions
    entry_pair_ptr temp_entry = NULL;   // Temp entry var used for probing

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_entry_pair(new_entry);
    }

    // ADD IT
    // Does it exist?
    if (RET_SUCCESS == retval)
    {
        temp_data_ptr = find_value(table, new_entry->key, &retval);
        if (temp_data_ptr)
        {
            fprintf(stderr, "This value already exists: %p!\n", new_entry);
            retval = RET_ERROR;
        }
    }
    // Hash collision?
    if (RET_SUCCESS == retval)
    {
        // 1. Get the data's index
        index = _calc_index(new_entry->key->d_ptr, new_entry->key->d_size, table->capacity);
        // 2. Find the data
        if (BAD_INDEX != index)
        {
            temp_entry = _get_index(table, index, &retval);
            // fprintf(stderr, "Temp entry: %p\n", temp_entry);  // DEBUGGING
        }
        if (temp_entry)
        {
            fprintf(stderr, "Hash collision detected for new entry: %p!\n", new_entry);
            retval = RET_ERROR;
        }
    }
    // Calculate the index
    if (RET_SUCCESS == retval)
    {
        index = _calc_index(new_entry->key->d_ptr, new_entry->key->d_size, table->capacity);
        // fprintf(stderr, "Calculated index is %d\n", index);  // DEBUGGING
        if (ERROR_HASH == index)
        {
            HARKLE_ERROR(_calc_index, Returned a bad hash value);
            retval = RET_ERROR;
        }
    }
    // Insert new_entry into table->table_ptr
    if (RET_SUCCESS == retval)
    {
        if (index < table->capacity)
        {
            (*((entry_pair_ptr*)(table->table_ptr) + index)) = new_entry;
            table->entries += 1;
        }
        else
        {
            HARKLE_ERROR(_add_entry, Detected an out of bounds index);
            retval = RET_ERROR;  // Invalid index
        }
    }

    // RESIZE
    // If we're going to resize the hash table at a certain "load factor" threshold, we do it here

    // DONE
    return retval;
}


return_value _add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr new_key = NULL;        // New key pointer
    any_data_ptr new_val = NULL;        // New value pointer
    entry_pair_ptr new_entry = NULL;    // New entry pointer
    int errnum = 0;                     // Errno value

    // ALLOCATION
    // entry_pair
    new_entry = calloc(1, sizeof(entry_pair));
    if (!new_entry)
    {
        errnum = errno;
        HARKLE_ERRNO(_allocate_any_data, errnum);
        HARKLE_ERROR(_add_key, Calloc failed to allocate a new entry);
        retval = RET_ERROR;
    }

    // COPY DATA
    // Key
    if (RET_SUCCESS == retval)
    {
        new_entry->key = _copy_any_data(key, &retval);
    }
    // Value
    if (RET_SUCCESS == retval)
    {
        new_entry->value = _copy_any_data(value, &retval);
    }

    // ADD TO HASH TABLE
    if (RET_SUCCESS == retval)
    {
        retval = _add_entry(table, new_entry);
    }

    // DONE
    if (RET_SUCCESS != retval && new_entry)
    {
        _destroy_entry_pair(new_entry);
    }
    return retval;
}


any_data_ptr _allocate_any_data(return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;                    // Function call results
    any_data_ptr new_data = calloc(1, sizeof(any_data));  // New any_data struct
    int errnum = errno;                                   // Errno value

    // VALIDATION
    if (!new_data)
    {
        HARKLE_ERRNO(_allocate_any_data, errnum);  // Already captured errno
        HARKLE_ERROR(_allocate_any_data, Calloc failed to allocate a new entry);
        retval = RET_ERROR;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_data;
}


/*
 *  Hash a given input.
 */
unsigned long _calc_hash(void *d_ptr, unsigned int d_size)
{
    // LOCAL VARIABLES
    unsigned long hash = 0;  // Calculated hash

    // GET IT
    hash = get_fnv_hash(d_ptr, d_size);
    // fprintf(stderr, "Calculated hash for %p is %lu\n", d_ptr, hash);  // DEBUGGING

    // DONE
    return hash;
}


unsigned int _calc_index(void *d_ptr, unsigned int d_size, unsigned int capacity)
{
    // LOCAL VARIABLES
    unsigned long hash = 0;          // Calculated hash
    unsigned int index = BAD_INDEX;  // Calculated index

    // INPUT VALIDATION
    if (capacity > 0)
    {
        // GET IT
        hash = _calc_hash(d_ptr, d_size);
        // fprintf(stderr, "Calculated hash for %p at capacity %d is %lu\n", d_ptr, capacity, hash);  // DEBUGGING
        // fprintf(stderr, "The capacity is %d\n", capacity);  // DEBUGGING
        if (ERROR_HASH != hash)
        {
            index = hash % capacity;
        }
        // fprintf(stderr, "Calculated hash for %p, size %d, at capacity %d is %lu and the index is %d\n", d_ptr, d_size, capacity, hash, index);  // DEBUGGING
    }

    // DONE
    return index;
}


bool _compare_any_data(any_data_ptr s1_data, any_data_ptr s2_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool matches = true;                // s1 matches s2

    // INPUT VALIDATION
    // s1
    retval = _validate_any_data(s1_data);
    // s2
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(s2_data);
    }
    // result
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        matches = _compare_data(s1_data->d_ptr, s1_data->d_type, s1_data->d_size, s2_data, &retval);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return matches;
}


bool _compare_data(void *s1_data, data_type s1_data_type, unsigned int s1_data_size,
                   any_data_ptr s2_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool matches = true;                // s1 matches s2

    // INPUT VALIDATION
    // s1
    retval = _validate_raw_data(s1_data, s1_data_type, s1_data_size);
    // s2
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(s2_data);
    }
    // result
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        if (s1_data_size != s2_data->d_size)
        {
            matches = false;  // Different sizes
        }
        else if (s1_data_type != s2_data->d_type)
        {
            matches = false;  // Different data types
        }
        else if (memcmp(s1_data, s2_data->d_ptr, s1_data_size))
        {
            matches = false;  // Memory doesn't match
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return matches;
}


any_data_ptr _copy_any_data(any_data_ptr source, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr new_data = NULL;       // New heap-allocated any_data struct copied from source
    int errnum = 0;                     // Errno value

    // INPUT VALIDATION
    retval = _validate_any_data(source);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COPY IT
    // Allocate
    if (RET_SUCCESS == retval)
    {
        new_data = _allocate_any_data(&retval);
    }
    // Copy
    if (RET_SUCCESS == retval)
    {
        // data_type d_type;     // The data type of the data
        new_data->d_type = source->d_type;
        // unsigned int d_size;  // Total size of the data, in memory, as bytes
        new_data->d_size = source->d_size;
        // void *d_ptr;          // Pointer to data
        new_data->d_ptr = calloc(new_data->d_size, 1);
        if (!(new_data->d_ptr))
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            HARKLE_ERROR(_copy_any_data, Failed to allocate memory);
            retval = RET_ERROR;
        }
        else
        {
            memcpy(new_data->d_ptr, source->d_ptr, new_data->d_size);
        }
    }
    // Verify
    if (RET_SUCCESS == retval)
    {
        if (false == _compare_any_data(source, new_data, &retval))
        {
            fprintf(stderr, "Failed to successfully copy %p to %p in _copy_any_data()\n",
                    source, new_data);
            retval = RET_ERROR;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval && new_data)
    {
        _destroy_any_data(new_data);
        new_data = NULL;
    }
    return new_data;
}


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
        HARKLE_ERROR(_create_hash_table, Failed to allocate malloc memory);
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
            HARKLE_ERROR(_create_hash_table, Failed to allocate calloc memory);
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


return_value _delete_all_keys(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;    // Function call results
    return_value temp_ret = RET_SUCCESS;  // Temp function call result var
    entry_pair_ptr *table_arr = NULL;     // Array of entry_pair pointers
    entry_pair_ptr temp_entry = NULL;     // Temp hash table entry var

    // INPUT VALIDATION
    retval = _validate_table(table);

    // DELETE ALL ENTRIES
    if (RET_SUCCESS == retval)
    {
        table_arr = (entry_pair_ptr*)table->table_ptr;
        // Destroy all entries
        for (int i = 0; i < table->capacity; i++)
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
        table->entries = 0;  // Reset
    }

    // DONE
    return retval;
}


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
        free(old_data);
    }

    // DONE
    return retval;
}


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
        free(old_entry);
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
            fprintf(stderr, "Index: %d\tEntry: %p\n", i, temp_entry);
            if (temp_entry)
            {
                fprintf(stderr, "Destroying %p\n", temp_entry);
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


any_data_ptr _find_any_data_value(hash_table_ptr table, any_data_ptr data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr value = NULL;          // The value from the entry

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(data);
    }
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        value = _find_value(table, data->d_ptr, data->d_type, data->d_size, &retval);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return value;
}


any_data_ptr _find_value(hash_table_ptr table, void *raw_data, data_type raw_data_type,
                         unsigned int raw_data_size, return_value_ptr result)
{
    // LOCAL VARAIBLES
    return_value retval = RET_SUCCESS;  // Function call results
    entry_pair_ptr entry = NULL;        // The entry pulled from the hash table
    any_data_ptr value = NULL;          // The value from the entry
    unsigned int index = BAD_INDEX;     // Calculated (expected) index for the key (AKA raw_data)

    // FIND IT
    // 1. Get the data's index
    index = _calc_index(raw_data, raw_data_size, table->capacity);
    // fprintf(stderr, "Calculated index is %d\n", index);  // DEBUGGING
    // 2. Find the data
    if (index < table->capacity)
    {
        entry = _get_index(table, index, &retval);
    }
    // 3. Verify the data
    if (entry && RET_SUCCESS == retval)
    {
        if (true == _compare_data(raw_data, raw_data_type, raw_data_size, entry->key, &retval))
        {
            if (RET_SUCCESS == retval)
            {
                value = entry->value;
            }
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return value;
}


entry_pair_ptr _get_index(hash_table_ptr table, unsigned int index, return_value_ptr result)
{
    // LOCAL VARAIBLES
    entry_pair_ptr entry = NULL;        // Entry found in the hash table
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval && index >= table->capacity)
    {
        retval = RET_INV_PARAM;
    }

    // GET IT
    if (RET_SUCCESS == retval)
    {
        // entry = (*((entry_pair_ptr*)table->table_ptr + (index * sizeof(entry_pair_ptr))));
        entry = (*((entry_pair_ptr*)table->table_ptr + index));
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return entry;
}


return_value _validate_any_data(any_data_ptr data)
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
        retval = _validate_raw_data(data->d_ptr, data->d_type, data->d_size);
    }

    // DONE
    return retval;
}


return_value _validate_entry_pair(entry_pair_ptr entry)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!entry)
    {
        retval = RET_INV_PARAM;
    }
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(entry->key);
    }
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(entry->value);
    }

    // DONE
    return retval;
}


return_value _validate_raw_data(void *raw_data, data_type raw_data_type, unsigned int raw_data_size)
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
