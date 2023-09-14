/*
 *  This header file declares data types used in many of the 8-0? data structure labs.
 *  In general, the library should be responsible for allocating memory to copy user input.
 *  The any_data structs are used to format user input, but the library does not own the contents.
 *  Data stored in data structures should be duplicated by the library and stored in the heap.
 *  The data_type struct may seem unimportant but could help identify duplicates and DEBUGGING.
 */

#ifndef _8_00_DEFINITIONS_
#define _8_00_DEFINITIONS_


#include <stdbool.h>  // bool


/* Standardize Return Values */
typedef enum _return_value
{
    RET_SUCCESS = 0,     // Success
    RET_INV_PARAM = 1,   // Bad input: NULL pointer, unsupported data type
    RET_ERROR = 2,       // System call failed (print errno)
    RET_NOT_FOUND = 3,   // Node not found
    RET_FULL = 4,        // No room left in the data structure
} return_value, *return_value_ptr;


/* Keep Track Of The Data Type */
typedef enum _data_type
{
    NULL_DT = 0, CHAR_DT, DOUBLE_DT, FLOAT_DT, INT_DT, STRING_DT, VOID_DT
} data_type, *data_type_ptr;


/* Store "any data" */
typedef struct _any_data
{
    void *d_ptr;          // Pointer to data
    data_type d_type;     // The data type of the data
    unsigned int d_size;  // Total size of the data, in memory, as bytes
} any_data, *any_data_ptr;


/*
 *  Defined data type for a function pointer to an any_data pointer comparison function.  Returns
 *  true if left_data < right_data.  Returns false for all other conditions.
 */
typedef bool (*compare_any_data)(any_data_ptr left_data, any_data_ptr right_data);


#endif  /* _8_00_DEFINITIONS_ */
