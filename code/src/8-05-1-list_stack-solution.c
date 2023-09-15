/*
 *  This is an example implementation for the 8-05-1 lab.
 *  This solution should work, as-is, when copy pasted into 8-05-1-list_stack-lab.c.
 *
 *  DISCLAIMER: This implementation is not perfect.
 *      The Good:
 *          - It works.
 *          - ASAN and Valgrind both give this implementation a clean bill of health.
 *          - It reuses existing code
 *      The Bad:
 *          - It highlighted an oversight in the design of the 8-02-1-linked_list library.
 *              - There's no 8-02-1-linked_list function to free() library-allocated any_data_ptrs.
 *                As you may remember from 6-21, you should allocate and free at the same
 *                level-of-abstraction/module.
 *              - The library should probably expose a delete_node() function.  As it stands,
 *                disconnecting the node from the list and using delete_list() suffices as a
 *                work-around.
 *              - The library should probably expose a function to remove a node at a position
 *                without free()ing the entire node, like remove_node_pos() does.
 *          - Normally, this is functionality to add/expose/refactor when you find the original
 *            design doesn't meet all needs but I didn't want to pollute another JQS module's
 *            example solution.
 */

#include "8-00-definitions.h"  // any_data, any_data_ptr, return_value, return_value_ptr
#include "8-02-linked_list.h"  // delete_list(), insert_data(), list_node_ptr
#include "8-05-stack.h"        // stack_adt, stack_adt_ptr


/* A Linked List Stack Struct */
typedef struct _stack_adt
{
    unsigned int entries;  // Number of entries
    list_node_ptr *top;    // List implementation
} _stack_adt;



#define HARKLE_ERROR(funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", \
                                                 __FILE__, #funcName, #msg); } while (0);
#define HARKLE_ERRNO(funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - \
                                                                 %s() returned errno:\t%s\n", \
                                                                 __FILE__, #funcName, \
                                                                 strerror(errorNum)); }


/**************************************************************************************************/
/********************************* INTERNAL FUNCTION DECLARATIONS *********************************/
/**************************************************************************************************/

/*
 *  Validate stack struct contents.
 */
return_value _validate_stack(stack_adt_ptr stack);

/*
 *  Validates the stack struct entry value against the actual linked list count.  Also
 *  validates the struct contents by calling _validate_stack().
 */
return_value _validate_node_count(stack_adt_ptr stack);



/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


stack_adt_ptr allocate_stack(unsigned int initial_capacity, return_value_ptr result)
{
    // LOCAL VARIABLES
    stack_adt_ptr new_stack = NULL;     // Heap-allocated stack struct
    int errnum = 0;                     // Store errno
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    // Ignore initial capacity
    if (!result)
    {
        retval = RET_INV_PARAM;
    }

    // ALLOCATE IT
    if (RET_SUCCESS == retval)
    {
        new_stack = calloc(1, sizeof(stack_adt));
        if (!new_stack)
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);  // Already captured errno
            HARKLE_ERROR(allocate_stack, Calloc failed to allocate a new entry);
            retval = RET_ERROR;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_stack;
}


return_value push_data(stack_adt_ptr stack, any_data_ptr new_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    list_node_ptr tmp_node = NULL;      // Store linked list return values

    // INPUT VALIDATION
    retval = _validate_stack(stack);

    // PUSH IT
    if (RET_SUCCESS == retval)
    {
        tmp_node = insert_data(stack->top, new_data, 1, &retval);  // New head node
        if (tmp_node && RET_SUCCESS == retval && tmp_node != stack->top)
        {
            stack->top = tmp_node;  // New head top (AKA top)
            tmp_node = NULL;
        }
        else if (RET_SUCCESS == retval)
        {
            retval = RET_ERROR;  // Logical failure
        }
    }

    // DONE
    if (tmp_node && RET_SUCCESS != retval)
    {
        delete_list(tmp_node);  // Destroy this node
    }
    return retval;
}


any_data_ptr get_top(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    list_node_ptr top_node = NULL;      // Store linked list return values

    // INPUT VALIDATION
    retval = _validate_stack(stack);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // GET IT
    if (RET_SUCCESS == retval)
    {
        top_node = stack->top;  // Top node
        if (NULL == stack->top)
        {
            retval = RET_NOT_FOUND;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return top_node
}


any_data_ptr pop_data(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    list_node_ptr top_node = NULL;      // Store linked list return values
    any_data_ptr top_data = NULL;       // Data in the top node

    // INPUT VALIDATION
    // Stack is validated by subsequent function calls
    if (!result)
    {
        retval = RET_INV_PARAM;
    }

    // POP IT
    if (RET_SUCCESS == retval)
    {
        top_node = get_top(stack, &retval);
        if (top_node)
        {
            stack->top = top_node->next_ptr;
            top_node->next_ptr = NULL;
            top_data = top_node->data_ptr;
            top_node->data_ptr = NULL;
            delete_list(top_node);  // We're in to deep to roll-back now so ignore errors
            stack->entries -= 1;  // Decrement the stack count
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return top_data;
}


int get_size(stack_adt_ptr stack, ireturn_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    int stack_count = -1;               // Return value

    // INPUT VALIDATION
    retval = _validate_node_count(stack);  // Also validates stack
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // GET IT
    if (RET_SUCCESS == retval)
    {
        stack_count = stack->entries;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return stack_count;
}


bool is_empty(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool empty = true;                  // Return value

    // INPUT VALIDATION
    retval = _validate_stack(stack);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // CHECK IT
    if (RET_SUCCESS == retval)
    {
        if (stack->entries > 0)
        {
            empty = false;
        }
    }

    if (result)
    {
        *result = retval;
    }
    return empty;
}


return_value empty_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_node_count(stack);

    // EMPTY IT
    if (RET_SUCCESS == retval)
    {
        retval = delete_list(stack->top);
        if (RET_SUCCESS == retval)
        {
            stack->top = NULL;
            stack->entries = 0;
        }
    }

    // DONE
    return retval;
}


return_value destroy_any_data(any_data_ptr old_data)
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


/**************************************************************************************************/
/*************************************** INTERNAL FUNCTIONS ***************************************/
/**************************************************************************************************/

return_value _validate_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!stack)
    {
        retval = RET_INV_PARAM;  // NULL pointer
    }
    else if (0 == stack->entries && stack->top)
    {
        retval = RET_INV_PARAM;  // Invalid stack count
    }

    // DONE
    return retval
}


return_value _validate_node_count(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    int stack_count = 0;                // Return value

    // INPUT VALIDATION
    retval = _validate_stack(stack);

    // VALIDATE COUNT
    if (RET_SUCCESS == retval)
    {
        stack_count = count_nodes(stack->top);
        if (stack_count != stack->entries)
        {
            fprintf(stderr, "Stack count mismatch!  Actual count %d doesn't match %d.\n",
                    stack_count, stack->entries);
            retval = RET_ERROR;
        }
    }

    // DONE
    return retval;
}
