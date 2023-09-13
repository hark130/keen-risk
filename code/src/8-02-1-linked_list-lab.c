/*
 *  This file is where the 8-02-1 lab should be completed.
 *  This source file implements the library functions declared in 8-02-1-linked_list.h.
 *  Keep an eye out for phrases like "CODE GOES HERE", "SPOILER ALERT", and "PRO TIP".
 *  Don't suffer in silence.  Your 2nd trouble-shooting step should be to ask for help.
 *  The instructor has an example solution for this file and might be willing to share.
 */

#include "8-02-1-linked_list.h"
#include "8-02-sort_functions.h"
#include <stddef.h>  // NULL


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


list_node_ptr append_data(list_node_ptr head_node, any_data_ptr node_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    list_node_ptr new_head = NULL;  // Pointer to the new(?) head node
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return new_head;
}


return_value delete_list(list_node_ptr head_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_ERROR;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */
    /* Think about what to do if something goes wrong mid-process: stop, best effort, try harder. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}


unsigned int count_nodes(list_node_ptr head_node)
{
    // LOCAL VARIABLES
    unsigned int count = 0;  // Current count
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return count;
}


list_node_ptr find_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result)
{
    // LOCAL VARIABLES
    list_node_ptr tmp_node = NULL;  // Temp node to iterate the list
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return tmp_node;
}


 list_node_ptr insert_data(list_node_ptr head_node, any_data_ptr node_data, unsigned int pos,
 	                       return_value_ptr result)
 {
    // LOCAL VARIABLES
    list_node_ptr new_head = NULL;  // Pointer to the new(?) head node
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return new_head;
 }


 list_node_ptr remove_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result)
 {
    // LOCAL VARIABLES
    list_node_ptr new_head = NULL;  // Pointer to the new(?) head node
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return new_head;
 }


list_node_ptr find_node_val(list_node_ptr head_node, any_data_ptr needle, return_value_ptr result)
{
    // LOCAL VARIABLES
    list_node_ptr needle_node = NULL;  // Node pointer with data that matches needle
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return needle_node;
}


list_node_ptr sort_list(list_node_ptr head_node, compare_any_data comp_func,
                        return_value_ptr result)
{
    // LOCAL VARIABLES
    list_node_ptr new_head = NULL;  // Pointer to the new(?) head node
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */
    /* SPOILER ALERT: This implementation is non-trivial.  Save this for last. */

    /* !!! CODE GOES HERE !!! */

    // DONE
    return new_head;
}
