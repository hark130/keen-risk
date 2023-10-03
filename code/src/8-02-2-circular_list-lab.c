/*
 *  This file is where the 8-02-2 lab should be completed.
 *  This source file implements the library functions declared in 8-02-2-circular_list.h.
 *  Keep an eye out for phrases like "CODE GOES HERE", "SPOILER ALERT", and "PRO TIP".
 *  Don't suffer in silence.  Your 2nd trouble-shooting step should be to ask for help.
 *  The instructor has an example solution for this file and might be willing to share.
 */

#include "8-00-definitions.h"
#include "8-02-2-circular_list.h"
#include "8-02-sort_functions.h"
#include <stddef.h>  // NULL


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


circular_list_ptr create_circular_list(return_value_ptr result)
{
    // LOCAL VARIABLES
    circular_list_ptr c_list = NULL;  // Heap-allocated circular_list pointer
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return c_list;
}


return_value empty_the_list(circular_list_ptr c_list)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}


return_value delete_clist(circular_list_ptr c_list)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}


circular_node_ptr find_cnode_pos(circular_list_ptr c_list, unsigned int pos,
                                 return_value_ptr result)
{
    // LOCAL VARIABLES
    circular_node_ptr needle_ptr = NULL;  // Node found at position pos
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return needle_ptr;
}


return_value insert_cdata(circular_list_ptr c_list, any_data_ptr node_data, unsigned int pos)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}


return_value remove_cnode_pos(circular_list_ptr c_list, unsigned int pos)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}


circular_node_ptr find_cnode_val(circular_list_ptr c_list, any_data_ptr needle,
                                return_value_ptr result)
{
    // LOCAL VARIABLES
    circular_node_ptr needle_node = NULL;  // Node found matching data needle

    /* !!! CODE GOES HERE !!! */

    return needle_node;
}


return_value sort_clist(circular_list_ptr c_list, compare_any_data comp_func)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    /* PRO TIP: Always Be Checking (ABC) for invalid input. */
    /* SPOILER ALERT: This implementation is non-trivial.  Save this for last. */

    /* !!! CODE GOES HERE !!! */

    return retval;
}
