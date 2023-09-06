/*
 *  This library was written to aid the 8-02 labs.  It may not implement an actual sorting
 *  algorithm but it does implement compare functions and swap functions (which an algorithm
 *  would use).  The compare_any_data_*() functions allow for dependency injection into
 *  linked list library sort() functions.
 */

#ifndef _8_02_SORT_FUNCTIONS_
#define _8_02_SORT_FUNCTIONS_

#include "8-02-1-linked_list.h"
#include <stdbool.h>  // true, false, bool


/*
 *  Compares d_ptr pointer of left_data to right_data.  Returns true if
 *  left_data->d_ptr < right_data->d_ptr.  Returns false for all other conditions.
 */
bool compare_any_data_ptr(any_data_ptr left_data, any_data_ptr right_data);


/*
 *  Compares d_size of left_data to right_data.  If left_data and right_data have the same d_size,
 *  Compares the d_ptr value byte by byte.  Returns true if left_data < right_data.
 *  Returns false for all other conditions.
 */
bool compare_any_data_siz(any_data_ptr left_data, any_data_ptr right_data);


/*
 *  Compares d_ptr value of left_data to right_data.  Returns true if left_data < right_data.
 *  Returns false for all other conditions.
 */
bool compare_any_data_val(any_data_ptr left_data, any_data_ptr right_data);


/*
 *  Swap the value stored in left_data with the value stored in right_data.
 */
void swap_data(any_data_ptr *left_data, any_data_ptr *right_data);


/*
 *  Swap the value stored in left_node with the value stored in right_node.
 */
void swap_node(list_node_ptr *left_node, list_node_ptr *right_node);


#endif  /* _8_02_SORT_FUNCTIONS_ */
