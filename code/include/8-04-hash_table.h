/*
 *  This header file declares the functions used by all of the 8-04 unit tests.
 *  Consider these functions the entry point of your library.  Validate all input.
 *  In general, the library is responsible for allocating memory to copy user input.
 *  The hash_table struct serves as a layer of abstraction between the library and the user.
 *  The user should never directly modify any data contained in the hash_table struct.
 *  Instead, the user should call the library functions to add, delete, find, etc.
 *  The any_data structs are used to format user input, but the library does not own the contents.
 *  Data stored in the hash_table struct or the hash_table itself should be stored in the heap.
 *  The data_type struct may seem unimportant but could help identify duplicates and DEBUGGING.
 */

#ifndef _8_04_HASH_TABLE_
#define _8_04_HASH_TABLE_

#include "8-00-definitions.h"  // any_data_ptr, return_value, return_value_ptr

/* Hash Table Bookkeeping */
typedef struct _hash_table
{
    void *table_ptr;        // Pointer to the array of entries
    unsigned int entries;   // Number of entries in table_ptr
    unsigned int capacity;  // Number of indices in the table_ptr array
    float threshold;        // Load factor threshold to resize the hash table
} hash_table, *hash_table_ptr;


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in suggested call order.


/*
 *  Allocates and initializes heap memory for a hash table.  Capacity is the initial size of the
 *  hash table and threshold is the load factor which will trigger the hash table to double in
 *  size (at least).
 *
 *  NOTES:
 *      - The caller is responsible for (eventually) calling destroy_table() to free the table.
 *      - Consider 0.75 as the threshold.
 *
 *  Updates result with RET_SUCCESS on success, RET_INV_PARAM for bad input, RET_ERROR if an OS
 *  system call fails (and print errno), or RET_NOT_FOUND if key can't be found in the hash table.
 */
hash_table_ptr create_hash_table(unsigned int capacity, float threshold, return_value_ptr result);


/*
 *  Attempts to locate the value associated with key in the hash table.
 *  1. Hashes key
 *  2. Calculates the index
 *  3. Validates the found entry against key
 *  4. Returns the value
 *
 *  Updates result with RET_SUCCESS on success, RET_INV_PARAM for bad input, RET_ERROR if an OS
 *  system call fails (and print errno), or RET_NOT_FOUND if key can't be found in the hash table.
 *
 *  NOTE: The heap memory for the value returned is owned by the hash table.  Do not free!
 */
any_data_ptr find_value(hash_table_ptr table, any_data_ptr key, return_value_ptr result);


/*
 *  Allocates heap memory to copy the key and value.  Adds the copied pair to the hash table.
 *
 *  Returns RET_SUCCESS on success, RET_INV_PARAM for bad input, RET_DUPE_ENTRY is key is already
 *  in the hash table, or RET_ERROR if an OS system call fails (and print errno).
 *
 *  NOTE: The caller is responsible for any memory storing the table, key, and value.
 */
return_value add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value);


/*
 *  Delete the hash table entry for the data in key.
 *
 *  Returns RET_SUCCESS on success, RET_INV_PARAM for bad input, RET_ERROR if an OS system call
 *  fails (and print errno), or RET_NOT_FOUND if key can't be found in the hash table.
 */
return_value delete_key(hash_table_ptr table, any_data_ptr key);


/*
 *  Delete all the hash table entries and reset the entries count.
 *
 *  Returns RET_SUCCESS on success, RET_INV_PARAM for bad input, or RET_ERROR if an OS system call
 *  fails (and print errno).
 */
return_value delete_all_keys(hash_table_ptr table);


/*
 *  Frees all entries in table and then frees table.
 *
 *  Returns RET_SUCCESS on success, RET_INV_PARAM for bad input, or RET_ERROR if an OS system call
 *  fails (and print errno).
 */
return_value destroy_table(hash_table_ptr table);


#endif  /* _8_04_HASH_TABLE_ */
