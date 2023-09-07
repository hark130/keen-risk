/*
 *  This header file declares functions used in the instructor's 8-02-1 linked list demonstration.
 *  Consider these functions the entry point of the library.  Validate all input.
 *  In general, the library is responsible for allocating memory to copy user input.
 *  The any_data structs are used to format user input, but the library does not own the contents.
 *  Data stored in the linked list should be duplicated and stored in the heap.
 *  The data_type struct may seem unimportant but could help identify duplicates and DEBUGGING.
 */

#ifndef _8_02_1_LINKED_LIST_
#define _8_02_1_LINKED_LIST_


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


/* One Linked List Node */
typedef struct _list_node
{
    any_data_ptr data_ptr;        // Data
    struct _list_node *next_ptr;  // Next node
} list_node, *list_node_ptr;


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
 *  Allocates a list_node, copies node_data into the list_node, and adds the list_node to the
 *  end of head_node.  If head_node is NULL, then the new list_node becomes the new head_node.
 *  The result value is updated with the return_value.
 *
 *  Returns a pointer to the head_node, which may change, on success.
 *  Returns NULL on failure (consult result).
 */
list_node_ptr append_data(list_node_ptr head_node, any_data_ptr node_data, return_value_ptr result);


/*
 *  Frees the data and list_node pointers for each node found in head_node's linked list.
 */
return_value delete_list(list_node_ptr head_node);


/*
 *  Count the nodes in the link list starting at head_node.  If head_node is NULL, returns 0.
 */
unsigned int count_nodes(list_node_ptr head_node);


/*
 *  Finds and returns the list_node_ptr at position number pos.  The head_node is position 1.
 *
 *  Returns a pointer to the desired node on success.  Returns NULL on failure (consult result).
 */
list_node_ptr find_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result);


/*
 *  Allocates a list_node, copies node_data into the list_node, and inserts the list_node at
 *  position pos, moving any existing nodes back.  The head_node is position 1.  If head_node is
 *  NULL, then the new list_node becomes the new head_node.  If pos is greater than the list length
 *  then the node will be appended.  The result value is updated with the return_value.
 *
 *  Returns a pointer to the head_node, which may change, on success.
 *  Returns NULL on failure (consult result).
 */
 list_node_ptr insert_data(list_node_ptr head_node, any_data_ptr node_data, unsigned int pos,
                           return_value_ptr result);


/*
 *  Finds the node at position pos, removes that node from the list, and frees that node.
 *  The head_node is position 1.  The result value is updated with the return_value.
 *
 *  Returns a pointer to the head_node, which may change, on success.
 *  Returns NULL on failure (consult result).
 */
 list_node_ptr remove_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result);


/*
 *  Finds and returns the list_node_ptr that contains data matching needle.
 *
 *  Returns a pointer to the matching node on success.  Returns NULL on failure (consult result).
 */
list_node_ptr find_node_val(list_node_ptr head_node, any_data_ptr needle, return_value_ptr result);


/*
 *  Sort all nodes found in the head_node linked list in ascending order according to the
 *  comp_func results.
 *
 *  Returns a pointer to the head_node, which may change, on success.
 *  Returns NULL on failure (consult result).
 */
list_node_ptr sort_list(list_node_ptr head_node, compare_any_data comp_func,
                        return_value_ptr result);


#endif  /* _8_02_1_LINKED_LIST_ */
