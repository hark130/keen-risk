/*
 *  This file is where the 8-05-1 lab should be completed.
 *  This source file implements the library functions declared in 8-05-stack.h.
 *  This implementation should utilize a linked list to underpin this stack.
 *  Keep an eye out for phrases like "CODE GOES HERE", "SPOILER ALERT", and "PRO TIP".
 *  Don't suffer in silence.  Your 2nd trouble-shooting step should be to ask for help.
 *  The instructor has an example solution for this file and might be willing to share.
 */

#include "8-00-definitions.h"    // any_data, any_data_ptr, return_value, return_value_ptr
#include "8-05-stack.h"          // stack_adt, stack_adt_ptr
#include <string.h>              // NULL


/* A Linked List Stack Struct */
struct _stack_adt
{
    /* DEFINE YOUR LINKED LIST BOOKKEEPING HERE */
};


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


stack_adt_ptr allocate_stack(unsigned int initial_capacity, return_value_ptr result)
{
    // LOCAL VARIABLES
    stack_adt_ptr new_stack = NULL;  // Heap-allocated stack struct

    /* CODE GOES HERE */

    // DONE
    return new_stack;
}


return_value push_data(stack_adt_ptr stack, any_data_ptr new_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    /* CODE GOES HERE */

    // DONE
    return retval;
}


any_data_ptr get_top(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    any_data_ptr top_data = NULL;  // Data from the top of the stack

    /* CODE GOES HERE */

    // DONE
    return top_data;
}


any_data_ptr pop_data(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    any_data_ptr top_data = NULL;  // Data in the top node

    /* CODE GOES HERE */

    // DONE
    return top_data;
}


int get_size(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    int stack_count = -1;  // Return value

    /* CODE GOES HERE */

    // DONE
    return stack_count;
}


bool is_empty(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    bool empty = true;  // Return value

    /* CODE GOES HERE */

    // DONE
    return empty;
}


return_value empty_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    /* CODE GOES HERE */

    // DONE
    return retval;
}


return_value destroy_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    /* CODE GOES HERE */

    // DONE
    return retval;
}


return_value destroy_any_data(any_data_ptr old_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    /* CODE GOES HERE */

    // DONE
    return retval;
}
