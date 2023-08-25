#ifndef _8_04_HASH_TABLE_
#define _8_04_HASH_TABLE_

typedef enum _return_value
{
    RET_SUCCESS = 0,    // Success
    RET_INV_PARAM = 1,  // Bad input: NULL pointer, unsupported data type
    RET_ERROR = 2,      // System call failed (print errno)
    RET_NOT_FOUND = 3,  // Key not found
} return_value, *return_value_ptr;


typedef enum _data_type
{
    NULL_DT = 0, CHAR_DT, DOUBLE_DT, FLOAT_DT, INT_DT, STRING_DT, VOID_DT
} data_type, *data_type_ptr;


typedef struct _any_data
{
    void *d_ptr;          // Pointer to data
    data_type d_type;     // The data type of the data
    unsigned int d_size;  // Total size of the data, in memory, as bytes
} any_data, *any_data_ptr;


typedef struct _hash_table
{
    void *table_ptr;        // Pointer to the array of entries
    unsigned int entries;   // Number of entries in table_ptr
    unsigned int capacity;  // Number of indices in the table_ptr array
} hash_table, *hash_table_ptr;


/*
 *  Library functions listed in suggested call order.
 */

/*
 *  Allocates and initializes heap memory for a hash table.
 *
 *  NOTE: The caller is responsible for (eventually) calling destroy_table() to free the table.
 */
hash_table_ptr create_hash_table(int capacity, return_value_ptr result);


/*
 *  Attempts to locate the value associated with key in the hash table.
 *  1. Hashes key
 *  2. Calculates the index
 *  3. Validates the found entry against key
 *  4. Returns the value
 *
 *  NOTE: The heap memory for the value returned is owned by the hash table.  Do not free!
 */
any_data_ptr find_value(hash_table_ptr table, any_data_ptr key, return_value_ptr result);


/*
 *  Allocates heap memory to copy the key and value.  Adds the copied pair to the hash table.
 *
 *  NOTE: The caller is responsible for any memory storing the table, key, and value.
 */
return_value add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value);


/*
 *
 */
return_value delete_key(hash_table_ptr table, any_data_ptr key);


/*
 *
 */
return_value delete_all_keys(hash_table_ptr table);


/*
 *  Frees all entries in table and then frees table.
 */
return_value destroy_table(hash_table_ptr table);


#endif  /* _8_04_HASH_TABLE_ */
