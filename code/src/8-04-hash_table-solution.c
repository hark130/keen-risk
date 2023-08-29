/*
 *  NOTE TO STUDENTS: This implementation is not perfect.
 *      The Good:
 *          - It works.
 *          - ASAN and Valgrind both give this implementation a clean bill of health.
 *      The Bad:
 *          - It might be safe to remove some of the data validation from internal functions.
 *      The Ugly:
 *          - Some library-level operations could be improved merely by changing the order of
 *            operations.  (E.g., Check for duplicate keys prior to memory allocation.)
 *          - My "hash collision" solution, chaining, might be faster to insert at the head
 *            instead of the tail.
 *          - My "is it time to resize?" algorithm doesn't take into account that, sometimes,
 *            doubling the capacity isn't enough.
 */

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
    any_data_ptr key;          // The entry's key
    any_data_ptr value;        // The entry's value
    struct _entry_pair *next;  // Next node in the linked list
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
 *  Remove old_node from the given index from the table.  Free the node after it was removed.
 *
 *  Returns RET_SUCCESS on success, RET_INV_PARAM for any NULL pointer or invalid state
 *  (e.g. bad table), RET_ERROR on a failed system call, and RET_NOT_FOUND if old_node isn't
 *  found at old_index.
 */
return_value _clear_index(hash_table_ptr table, unsigned int old_index, entry_pair_ptr old_node);

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
 *  Allocate a hash table of a given capacity and threshold.  Hash table will contain an array
 *  of entry_pair objects.  This function does not validate input, only results.
 */
hash_table_ptr _create_hash_table(int capacity, float threshold, return_value_ptr result);

/*
 *  Deletes all entries found in the hash table.
 */
return_value _delete_all_keys(hash_table_ptr table);

/*
 *  Remove one key from table and free that memory.
 */
return_value _delete_key(hash_table_ptr table, any_data_ptr key);

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
 *  This function:
 *      1. Validates table
 *      2. Checks the threshold against the load factor
 *      3. Resizes the table if the load factor exceeds the threshold
 *
 *  NOTE: Call this function sparingly.  If you're just validating input, call _validate_table()
 *  instead.  Why?  Because if you call this function when you should have just validated the
 *  input then you could wind up in an endless loop (even though _resize_table() will attempt to
 *  protect itself from such occurences).
 */
return_value _evaluate_table(hash_table_ptr table);

/*
 *  Fill in dst_table with values provided.  Also, allocate and store the internal array
 *  based on the capacity.  Barely validates input.
 */
return_value _fill_hash_table_struct(hash_table_ptr dst_table, int capacity, float threshold);

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
 *  Frees the table_ptr.  Nothing else.  Doesn't remove entries.  Doesn't zeroize memory.
 *  Only frees old_table->table_ptr.  Barely even validates input.
 */
return_value _free_table_array(hash_table_ptr old_table);

/*
 *  Fetches an index from table->table_ptr.  Returns NULL if index is empty or on error.
 *  See result value for error reporting.
 */
entry_pair_ptr _get_index(hash_table_ptr table, unsigned int index, return_value_ptr result);

/*
 *  This function:
 *      1. Validates table
 *      2. Allocates a new array with double the capacity
 *      3. Transfers all entries from table->table_ptr to the new array
 *      4. Frees the old table->table_ptr
 *
 *  NOTES:
 *      - Any errors encountered while transferring nodes from table to the new array will be
 *        ignored but reported (in the return_value).
 *      - This function defends itself against recursion
 *
 *  Returns the first error encountered.
 */
return_value _resize_table(hash_table_ptr table);

/*
 *  Insert new_entry into table regardless of table's status.  Hash collision?  Handle it.
 */
return_value _shove_entry_in(hash_table_ptr table, entry_pair_ptr new_entry);

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


hash_table_ptr create_hash_table(unsigned int capacity, float threshold, return_value_ptr result)
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
        new_table = _create_hash_table(capacity, threshold, &retval);
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
    retval = _evaluate_table(table);  // Validate table and check for resize
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
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(key);
    }

    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        retval = _delete_key(table, key);
    }

    // DONE
    return retval;
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
            retval = RET_DUPE_ENTRY;
        }
        else if (RET_NOT_FOUND == retval)
        {
            retval = RET_SUCCESS;
        }
    }
    // Shove it in
    if (RET_SUCCESS == retval)
    {
        retval = _shove_entry_in(table, new_entry);
    }

    // RESIZE
    // If we're going to resize the hash table at a certain "load factor" threshold, we do it here

    // DONE
    return retval;
}


/*
 *  Add new_entry to the end of the entry_pair linked list which begins at head_entry.
 */
return_value _add_entry_node(entry_pair_ptr head_entry, entry_pair_ptr new_entry)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;     // Function call results
    entry_pair_ptr tmp_node = head_entry;  // Temp node to walk the linked list

    // INPUT VALIDATION
    retval = _validate_entry_pair(head_entry);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_entry_pair(new_entry);
    }

    // ADD IT
    if (RET_SUCCESS == retval)
    {
        while(tmp_node->next)
        {
            tmp_node = tmp_node->next;
        }
        tmp_node->next = new_entry;
    }

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
        if (ERROR_HASH != hash)
        {
            index = hash % capacity;
        }
    }

    // DONE
    return index;
}


/*
 *  Calculate the load factor of table.  Verify success by checking result.
 */
double _calc_load_factor(hash_table_ptr table, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    double load_factor = -100;          // Calculated load factor

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // CALC IT
    if (RET_SUCCESS == retval)
    {
        load_factor = (double)table->entries / table->capacity;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return load_factor;
}


/*
 *  Check table's load factor against the table's threshold.  Returns true if the table has
 *  exceeded the load factor threshold and needs to be resized.
 */
bool _check_for_resize(hash_table_ptr table, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool needs_resize = false;          // Calculated load factor
    double load_factor = -100;          // Calculated load factor

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // CHECK IT
    // Get the load factor
    if (RET_SUCCESS == retval)
    {
        load_factor = _calc_load_factor(table, &retval);
    }
    // Check the load factor against the threshold
    if (RET_SUCCESS == retval && load_factor > table->threshold)
    {
        needs_resize = true;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return needs_resize;
}


return_value _clear_index(hash_table_ptr table, unsigned int old_index, entry_pair_ptr old_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;     // Function call results
    entry_pair_ptr tmp_head = NULL;        // Head node found at old_index
    entry_pair_ptr tmp_node = NULL;        // Temp node var to parse linked list
    entry_pair_ptr *table_entries = NULL;  // Pointer to the hash table array of entry pointers

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval && old_index >= table->capacity)
    {
        retval = RET_INV_PARAM;
    }
    if (RET_SUCCESS == retval)
    {
        retval = _validate_entry_pair(old_node);
    }

    // CLEAR IT
    // Get the head node
    if (RET_SUCCESS == retval)
    {
        table_entries = (entry_pair_ptr*)table->table_ptr;
        tmp_head = (*(table_entries + old_index));
        if (!tmp_head)
        {
            retval = RET_NOT_FOUND;
        }
        else
        {
            retval = _validate_entry_pair(tmp_head);
        }
    }
    // Update linked list
    if (RET_SUCCESS == retval)
    {
        if (tmp_head == old_node)
        {
            (*(table_entries + old_index)) = tmp_head->next;
        }
        else
        {
            tmp_node = tmp_head->next;
            while (tmp_node)
            {
                retval = _validate_entry_pair(tmp_node);
                if (RET_SUCCESS == retval)
                {
                    if (tmp_node == old_node)
                    {
                        tmp_head->next = tmp_node->next;  // Remove it from the linked list
                        break;  // Found it
                    }
                    else
                    {
                        retval = RET_NOT_FOUND;  // Haven't found it yet
                        tmp_head = tmp_node;
                        tmp_node = tmp_node->next;  // Move it on down the list
                    }
                }
                else
                {
                    break;  // No need to continue
                }
            }
        }
    }
    // Destroy it
    if (RET_SUCCESS == retval)
    {
        old_node->next = NULL;  // Don't want to remove *all the nodes, just this one
        retval = _destroy_entry_pair(old_node);
        table->entries -= 1;
    }

    // DONE
    return retval;
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
 *  Copies the member values of src_table into dst_table.  No validation, beyond checking for
 *  NULL is performed.
 */
return_value _copy_struct_contents(hash_table_ptr src_table, hash_table_ptr dst_table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // COPY CONTENTS
    if (src_table && dst_table)
    {
        dst_table->table_ptr = src_table->table_ptr;
        dst_table->entries = src_table->entries;
        dst_table->capacity = src_table->capacity;
        dst_table->threshold = src_table->threshold;
    }
    else
    {
        retval = RET_INV_PARAM;
    }

    // DONE
    return retval;
}


/*
 *  Allocate a hash table of a given capacity.  Hash table will contain an array of entry_pair
 *  pointers.  This function does not validate input, only results.
 */
hash_table_ptr _create_hash_table(int capacity, float threshold, return_value_ptr result)
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
        retval = _fill_hash_table_struct(new_table, capacity, threshold);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_table;
}


return_value _delete_key(hash_table_ptr table, any_data_ptr key)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    unsigned int index = 0;             // Calculated index
    entry_pair_ptr old_entry = NULL;    // Entry to delete(?)
    entry_pair_ptr old_head = NULL;     // Head entry

    // DELETE IT
    // Calc index
    index = _calc_index(key->d_ptr, key->d_size, table->capacity);
    if (BAD_INDEX != index)
    {
        old_head = _get_index(table, index, &retval);
        old_entry = old_head;
    }
    while(old_entry)
    {
        // Validate finding
        retval = _validate_entry_pair(old_entry);
        // Verify a match
        if (RET_SUCCESS == retval && true == _compare_any_data(key, old_entry->key, &retval))
        {
            // Clear index
            retval = _clear_index(table, index, old_entry);
            break;
        }
        else
        {
            old_entry = old_entry->next;
        }
    }

    // DONE
    return retval;
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
                else
                {
                    (*(table_arr + i)) = NULL;
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
        if (old_entry->next)
        {
            temp_ret = _destroy_entry_pair(old_entry->next);
            if (temp_ret != RET_SUCCESS)
            {
                retval = temp_ret;
            }
            old_entry->next = NULL;
        }
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
    // Table array
    if (RET_SUCCESS == retval)
    {
        // void *table_ptr;  // Pointer to the array of entries
        retval = _free_table_array(old_table);
    }
    // Now, the rest
    if (RET_SUCCESS == retval)
    {
        // int entries;      // Number of entries in table_ptr
        old_table->entries = 0;
        // int capacity;     // Number of indices in the table_ptr array
        old_table->capacity = 0;
        // float threshold;  // Load factor threshold to resize the hash table
        old_table->threshold = 0;
    }

    // DONE
    return retval;
}


return_value _evaluate_table(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool needs_resizing = false;        // Return value from _check_for_resize()

    // INPUT VALIDATION
    retval = _validate_table(table);

    // EVALUATE IT
    if (RET_SUCCESS == retval)
    {
        needs_resizing = _check_for_resize(table, &retval);
    }
    // RESIZE IT
    if (RET_SUCCESS == retval && true == needs_resizing)
    {
        retval = _resize_table(table);
    }

    // DONE
    return retval;
}


return_value _fill_hash_table_struct(hash_table_ptr dst_table, int capacity, float threshold)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    int errnum = 0;                     // Errno value

    // FILL IT
    if (dst_table)
    {
        dst_table->table_ptr = calloc(capacity, sizeof(entry_pair_ptr));
        if (!(dst_table->table_ptr))
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            HARKLE_ERROR(_create_hash_table, Failed to allocate calloc memory);
            retval = RET_ERROR;
        }
        dst_table->entries = 0;  // Empty hash table
        dst_table->capacity = capacity;  // That's what the caller wants
        dst_table->threshold = threshold;  // That's what the caller wants
    }
    else
    {
        retval = RET_INV_PARAM;
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
    // 2. Find the data
    if (index < table->capacity)
    {
        entry = _get_index(table, index, &retval);
    }
    // 3. Verify the data
    if (entry && RET_SUCCESS == retval)
    {
        while (entry)
        {
            if (true == _compare_data(raw_data, raw_data_type, raw_data_size, entry->key, &retval))
            {
                if (RET_SUCCESS == retval)
                {
                    value = entry->value;
                    break;  // Found it
                }
            }
            else if (RET_SUCCESS != retval)
            {
                break;
            }
            else
            {
                entry = entry->next;  // Check the next node in the linked list
            }
        }
        if (!value)
        {
            retval = RET_NOT_FOUND;  // Apparently, it wasn't found
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return value;
}


return_value _free_table_array(hash_table_ptr old_table)
{
    // LOCAL VARAIBLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (old_table && old_table->table_ptr)
    {
        // void *table_ptr;  // Pointer to the array of entries
        free(old_table->table_ptr);
        old_table->table_ptr = NULL;
    }
    else
    {
        retval = RET_INV_PARAM;
    }

    // DONE
    return retval;
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
        entry = (*((entry_pair_ptr*)table->table_ptr + index));
        if (!entry)
        {
            retval = RET_NOT_FOUND;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return entry;
}


/*
 *  Iterates over all indices in table->table_ptr.  Removes all entry_pair_ptr found and strings
 *  them together in one long linked list.  Also, sets all table->table_ptr indices to NULL and
 *  updates table->entries.
 *
 *  Returns the head node to that linked list.  If this function encounters an error, mid-removal,
 *  it will: stop the process, update result with the error value, and return the head node it has.
 *  Know that the table is in an undefined state if this occurs (e.g., table->entries may be
 *  inaccurate).
 */
entry_pair_ptr _remove_entries(hash_table_ptr table, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    entry_pair_ptr head_entry = NULL;   // Head node for a linked list of old table entries
    entry_pair_ptr tmp_entry = NULL;   // Head node for a linked list of old table entries
    entry_pair_ptr *table_arr = NULL;   // table->table_ptr

    // INPUT VALIDATION
    retval = _validate_table(table);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // REMOVE THEM
    if (RET_SUCCESS == retval)
    {
        table_arr = (entry_pair_ptr*)table->table_ptr;
        for (unsigned int i = 0; i < table->capacity; i++)
        {
            // Get entry
            tmp_entry = (*(table_arr + i));
            // Chain entry
            if (head_entry && tmp_entry)
            {
                retval = _add_entry_node(head_entry, tmp_entry);
            }
            else if (tmp_entry)
            {
                head_entry = tmp_entry;
            }
            // Validate results
            if (RET_SUCCESS != retval)
            {
                fprintf(stderr, "_remove_entries() encountered %d mid-removal.  Aborting.", retval);
                break;
            }
            else
            {
                (*(table_arr + i)) = NULL;  // Clear old entry
            }
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS == result)
    {
        table->entries = 0;  // Doesn't matter what the count *was*... It's empty now.
    }
    return head_entry;
}


return_value _resize_table(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    return_value tmp_ret = RET_SUCCESS;  // Temp function call results var
    hash_table tmp_storage;              // Store old table values here
    entry_pair_ptr head_entry = NULL;    // Head node for a linked list of old table entries
    entry_pair_ptr tmp_entry = NULL;     // Temp node to iterate over the linked list
    static int num_calls = 0;            // Defend against recursion

    // INPUT VALIDATION
    retval = _validate_table(table);
    num_calls++;  // Increment the call count
    if (RET_SUCCESS == retval && num_calls > 1)
    {
        retval = RET_ERROR;  // Recursion detected
        fprintf(stderr, "Recursion detected in _resize_table()!\n");
    }

    // RESIZE IT
    // Copy old table
    if (RET_SUCCESS == retval)
    {
        retval = _copy_struct_contents(table, &tmp_storage);
    }
    // Reset the table struct
    if (RET_SUCCESS == retval)
    {
        table->table_ptr = NULL;  // I don't think _f_h_t_s() checks but let's be safe
        retval = _fill_hash_table_struct(table, tmp_storage.capacity * 2, tmp_storage.threshold);
    }
    // Pull out all the old entries
    if (RET_SUCCESS == retval)
    {
        head_entry = _remove_entries(&tmp_storage, &retval);
    }
    // Shove the old entries into the new table
    if (RET_SUCCESS == retval)
    {
        while(head_entry)
        {
            tmp_entry = head_entry;         // Process the head node
            head_entry = head_entry->next;  // Advance the head node to the next node
            tmp_entry->next = NULL;         // Disconnect tmp_entry from the linked list
            tmp_ret = _shove_entry_in(table, tmp_entry);
            if (RET_SUCCESS != tmp_ret)
            {
                fprintf(stderr, "_resize_table() encountered a %d error while inserting old "
                        "entries into the new array.  Soldiering on.", retval);
                if (RET_SUCCESS == retval)
                {
                    retval = tmp_ret;  // Store only the first error encountered but continue
                }
            }
        }
    }
    // Free the old array
    if (tmp_storage.table_ptr && 1 == num_calls)
    {
        tmp_ret = _free_table_array(&tmp_storage);  // We're in too deep
        if (RET_SUCCESS == retval)
        {
            retval = tmp_ret;  // Store only the first error encountered
        }
    }

    // DONE
    num_calls--;  // Decrement the call count
    return retval;
}


return_value _shove_entry_in(hash_table_ptr table, entry_pair_ptr new_entry)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    unsigned int index = 0;             // new_entry->value index, based on the hash
    any_data_ptr temp_data_ptr = NULL;  // Temp any_data_ptr for detecting collisions
    entry_pair_ptr temp_entry = NULL;   // Temp entry var used for probing

    // SHOVE IT IN
    // Hash collision?
    if (RET_SUCCESS == retval)
    {
        // 1. Get the data's index
        index = _calc_index(new_entry->key->d_ptr, new_entry->key->d_size, table->capacity);
        // 2. Find the data
        if (BAD_INDEX != index)
        {
            temp_entry = _get_index(table, index, &retval);
        }
        else
        {
            retval = RET_ERROR;  // _calc_index() appears to have failed (somehow)
        }
        // 3. Insert it
        // Hash collision detected
        if (RET_SUCCESS == retval && temp_entry)
        {
            while (NULL != temp_entry->next)
            {
                temp_entry = temp_entry->next;  // Find the end of the linked list
            }
            temp_entry->next = new_entry;
            table->entries += 1;
        }
        // Insert as normal
        else if (RET_NOT_FOUND == retval)
        {
            retval = RET_SUCCESS;
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
    }

    // DONE
    return retval;
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
    else if (table->threshold < 0.01 || table->threshold > 0.99)
    {
        retval = RET_INV_PARAM;  // The threshold member represents a percentage
    }

    // DONE
    return retval;
}
