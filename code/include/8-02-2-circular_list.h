/*
 *  This header file declares functions used in the instructor's 8-02-2 circular linked list lab.
 *  Consider these functions the entry point of the library.  Validate all input.
 *  In general, the library is responsible for allocating memory to copy user input.
 *  The any_data structs are used to format user input, but the library does not own the contents.
 *  Data stored in the circular linked list should be duplicated and stored in the heap.
 *  The data_type struct may seem unimportant but could help identify duplicates and DEBUGGING.
 */

#ifndef _8_02_2_CIRCULAR_LIST_
#define _8_02_2_CIRCULAR_LIST_


#include <stdbool.h>  // bool


/* Standardize Return Values */
typedef enum _return_value
{
    RET_SUCCESS = 0,     // Success
    RET_INV_PARAM = 1,   // Bad input: NULL pointer, unsupported data type
    RET_ERROR = 2,       // System call failed (print errno)
    RET_NOT_FOUND = 3,   // Node not found
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


/* One Circular Linked List Node */
typedef struct _circular_node
{
    any_data_ptr data_ptr;            // Data
    struct _circular_node *prev_ptr;  // Previous node
    struct _circular_node *next_ptr;  // Next node
} circular_node, *circular_node_ptr;


/* Circular Linked List Bookkeeping */
typedef struct _circular_list
{
    struct circular_node_ptr head_ptr;  // Head node
    struct circular_node_ptr tail_ptr;  // Tail node
    unsigned int entries;               // Number of entries
} circular_list, *circular_list_ptr;


/*
 *  Defined data type for a function pointer to an any_data pointer comparison function.  Returns
 *  true if left_data < right_data.  Returns false for all other conditions.
 */
typedef bool (*compare_any_data)(any_data_ptr left_data, any_data_ptr right_data);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in suggested implementation order.


/*
 *  Allocate memory for a circular_list struct on the heap and initialize that struct.
 *  Returns the struct pointer on succcess, NULL on failure (consult result).
 */
circular_list_ptr create_circular_list(return_value_ptr result);


/*
 *  Frees every node found in c_list.  The circular_list struct pointer is still valid but it
 *  will not contain any nodes.
 */
return_value empty_the_list(circular_list_ptr c_list);


/*
 *  Frees every node found in c_list.  Frees the circular_list struct.
 */
return_value delete_list(circular_list_ptr c_list);


/*
 *  Finds and returns the circular_node_ptr at position number pos.  The head_node is position 1.
 *
 *  Returns a pointer to the desired node on success.  Returns NULL on failure (consult result).
 */
circular_node_ptr find_node_pos(circular_list_ptr c_list, unsigned int pos,
                                return_value_ptr result);


/*
 *  Allocates a circular_node, copies node_data into the circular_node, and inserts the new
 *  circular_node at position pos, moving any existing nodes back.  The head_node is position 1.
 *  If c_list is empty, then the new circular_node becomes the new head node (and tail node).
 *  If pos is greater than the list length then the node will be appended (becoming the new tail
 *  node).
 */
 return_value insert_data(circular_list_ptr c_list, any_data_ptr node_data, unsigned int pos);


/*
 *  Finds the node at position pos, removes that node from the list, and frees that node.
 *  The head_node is position 1.
 */
 return_value remove_node_pos(circular_list_ptr c_list, unsigned int pos);


/*
 *  Finds and returns the circular_node_ptr that contains data matching needle.
 *
 *  Returns a pointer to the matching node on success.  Returns NULL on failure (consult result).
 */
circular_node_ptr find_node_val(circular_list_ptr c_list, any_data_ptr needle,
                                return_value_ptr result);


/*
 *  Sort all nodes found in the head_node linked list in ascending order according to the
 *  comp_func results.
 *
 *  Returns a pointer to the head_node, which may change, on success.
 *  Returns NULL on failure (consult result).
 */
return_value sort_list(circular_list_ptr c_list, compare_any_data comp_func);


#endif  /* _8_02_2_CIRCULAR_LIST_ */
