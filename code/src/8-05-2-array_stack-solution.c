/*
 *  This is an example implementation for the 8-05-2 lab.
 *  This solution should work, as-is, when copy pasted into 8-05-2-array_stack-lab.c.
 *
 *  DISCLAIMER: This implementation is not perfect.
 *      The Good:
 *          - It works.
 *          - ASAN and Valgrind both give this implementation a clean bill of health.
 *      The Bad:
 *          - My brain told me to realloc() the stack's array but I don't like realloc() so I
 *            just allocated and entirely new array and copied the pointers in.  Let history be
 *            my judge.
 *          - Normally, this is functionality to add/expose/refactor when you find the original
 *            design doesn't meet all needs but I didn't want to pollute another JQS module's
 *            example solution.
 */

#include "8-00-definitions.h"    // any_data, any_data_ptr, return_value, return_value_ptr
#include "8-05-stack.h"          // stack_adt, stack_adt_ptr
#include <errno.h>               // errno
#include <string.h>              // memset()
#include <stdio.h>               // fprintf()
#include <stdlib.h>              // free()


/* A Linked List Stack Struct */
struct _stack_adt
{
    unsigned int top;       // Index of the top stack entry
    unsigned int capacity;  // Size of the array
    any_data_ptr *array;    // List implementation
};


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
 *  Allocate and initialize an array-implemented stack struct.
 */
stack_adt_ptr _allocate_stack(unsigned int initial_capacity, return_value_ptr result);

/*
 *  Allocate stack's array to hold initial_capacity and update stack's bookkeeping.
 */
return_value _allocate_stack_array(stack_adt_ptr stack, unsigned int initial_capacity);

/*
 *  Compares all contents of s1_data to s2_data.  Returns true on exact match.  Returns false
 *  on mismatch or failure.  Result always updated.
 */
bool _compare_any_data(any_data_ptr s1_data, any_data_ptr s2_data, return_value_ptr result);

/*
 *  Compares all aspects of s1 data against s2, starting with the bookkeeping.  Immediately
 *  returns false on the first difference detected.
 */
bool _compare_data(void *s1_data, data_type s1_data_type, unsigned int s1_data_size,
                   any_data_ptr s2_data, return_value_ptr result);

/*
 *  Allocates a new any_data struct on the heap, copies over the source bookkeeping values,
 *  allocates a heap-buffer for the new any_data.d_ptr, and memcpy()s source->d_ptr into the
 *  new buffer.  If any part of the process fails, this function will free() all allocated memory,
 *  updated result, and return NULL.
 */
any_data_ptr _copy_any_data(any_data_ptr source, return_value_ptr result);

/*
 *  Push new_data onto the top of stack.  Update stack bookkeeping.
 */
return_value _push_any_data(stack_adt_ptr stack, any_data_ptr new_data);

/*
 *  Realloc the stack->array and update the stack capacity.
 */
return_value _resize_stack_array(stack_adt_ptr stack);

/*
 *  Validates any_data structs on behalf of the library.
 */
return_value _validate_any_data(any_data_ptr data);

/*
 *  Validates raw data on behalf of the library.
 */
return_value _validate_raw_data(void *raw_data, data_type raw_data_type,
                                unsigned int raw_data_size);

/*
 *  Validate stack struct contents.
 */
return_value _validate_stack(stack_adt_ptr stack);


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
        new_stack = _allocate_stack(initial_capacity, &retval);
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
    any_data_ptr data_copy = NULL;      // Heap-allocated copy of new_data

    // INPUT VALIDATION
    retval = _validate_stack(stack);

    // PUSH IT
    // Copy the data
    if (RET_SUCCESS == retval)
    {
        data_copy = _copy_any_data(new_data, &retval);
    }
    // Store the data
    if (RET_SUCCESS == retval)
    {
        retval = _push_any_data(stack, data_copy);
    }

    // DONE
    return retval;
}


any_data_ptr get_top(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr top_data = NULL;       // Data from the top of the stack

    // INPUT VALIDATION
    retval = _validate_stack(stack);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // GET IT
    if (RET_SUCCESS == retval)
    {
        if (stack->top < stack->capacity)
        {
            top_data = (*(stack->array + stack->top));
        }
        else
        {
            retval = RET_NOT_FOUND;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return top_data;
}


any_data_ptr pop_data(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr top_data = NULL;       // Data in the top node

    // INPUT VALIDATION
    // Handled by get_top()
    top_data = get_top(stack, &retval);
    if (top_data && RET_SUCCESS == retval)
    {
        (*(stack->array + stack->top)) = NULL;
        stack->top += 1;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return top_data;
}


int get_size(stack_adt_ptr stack, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    int stack_count = -1;               // Return value

    // INPUT VALIDATION
    retval = _validate_stack(stack);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // GET IT
    if (RET_SUCCESS == retval)
    {
        stack_count = stack->capacity - stack->top;
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
        if (get_size(stack, &retval) > 0)
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
    retval = _validate_stack(stack);

    // EMPTY IT
    if (RET_SUCCESS == retval && false == is_empty(stack, &retval))
    {
        while (stack->top < stack->capacity)
        {
            retval = destroy_any_data((*(stack->array + stack->top)));
            if (RET_SUCCESS != retval)
            {
                break;  // Bad entry
            }
            else
            {
                stack->top += 1;
            }
        }
    }

    // DONE
    return retval;
}


return_value destroy_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // DESTROY IT
    retval = empty_stack(stack);  // Validated by empty_stack()
    if (RET_SUCCESS == retval)
    {
        stack->capacity = 0;
        stack->top = 0;
        free(stack->array);
        stack->array = NULL;
        free(stack);
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


any_data_ptr _allocate_any_data(return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;                    // Function call results
    any_data_ptr new_data = calloc(1, sizeof(any_data));  // New any_data struct
    int errnum = errno;                                   // Errno value

    // VALIDATION
    if (!new_data)
    {
        HARKLE_ERRNO(_allocate_any_data, errnum);  // Already captured errno
        HARKLE_ERROR(_allocate_any_data, Calloc failed to allocate a new entry);
        retval = RET_ERROR;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_data;
}


stack_adt_ptr _allocate_stack(unsigned int initial_capacity, return_value_ptr result)
{
    // LOCAL VARIABLES
    stack_adt_ptr new_stack = NULL;     // Heap-allocated stack struct
    int errnum = 0;                     // Store errno
    return_value retval = RET_SUCCESS;  // Function call results

    // ALLOCATE IT
    // Allocate struct
    if (RET_SUCCESS == retval)
    {
        new_stack = calloc(1, sizeof(stack_adt));
        if (!new_stack)
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);  // Already captured errno
            HARKLE_ERROR(allocate_stack, Calloc failed to allocate a new stack);
            retval = RET_ERROR;
        }
    }
    // Allocate array
    if (RET_SUCCESS == retval)
    {
        retval = _allocate_stack_array(new_stack, initial_capacity);
        if (RET_SUCCESS != retval)
        {
            new_stack->array = NULL;
            free(new_stack);
            new_stack = NULL;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_stack;
}


return_value _allocate_stack_array(stack_adt_ptr stack, unsigned int initial_capacity)
{
    // LOCAL VARIABLES
    int errnum = 0;                     // Store errno
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (stack)
    {
        stack->array = calloc(initial_capacity, sizeof(any_data_ptr));
        if (NULL == stack->array)
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);  // Already captured errno
            HARKLE_ERROR(allocate_stack, Calloc failed to allocate the array);
            retval = RET_ERROR;
        }
        else
        {
            stack->capacity = initial_capacity;
            stack->top = initial_capacity;
        }
    }

    // DONE
    return retval;
}


bool _compare_any_data(any_data_ptr s1_data, any_data_ptr s2_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool matches = false;               // s1 matches s2

    // INPUT VALIDATION
    // s1
    retval = _validate_any_data(s1_data);
    // s2
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(s2_data);
    }
    // result
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        matches = _compare_data(s1_data->d_ptr, s1_data->d_type, s1_data->d_size, s2_data, &retval);
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return matches;
}


bool _compare_data(void *s1_data, data_type s1_data_type, unsigned int s1_data_size,
                   any_data_ptr s2_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    bool matches = true;                // s1 matches s2

    // INPUT VALIDATION
    // s1
    retval = _validate_raw_data(s1_data, s1_data_type, s1_data_size);
    // s2
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(s2_data);
    }
    // result
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COMPARE IT
    if (RET_SUCCESS == retval)
    {
        if (s1_data_size != s2_data->d_size)
        {
            matches = false;  // Different sizes
        }
        else if (s1_data_type != s2_data->d_type)
        {
            matches = false;  // Different data types
        }
        else if (memcmp(s1_data, s2_data->d_ptr, s1_data_size))
        {
            matches = false;  // Memory doesn't match
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval)
    {
        matches = false;
    }
    return matches;
}


any_data_ptr _copy_any_data(any_data_ptr source, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr new_data = NULL;       // New heap-allocated any_data struct copied from source
    int errnum = 0;                     // Errno value

    // INPUT VALIDATION
    retval = _validate_any_data(source);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // COPY IT
    // Allocate
    if (RET_SUCCESS == retval)
    {
        new_data = _allocate_any_data(&retval);
    }
    // Copy
    if (RET_SUCCESS == retval)
    {
        // data_type d_type;     // The data type of the data
        new_data->d_type = source->d_type;
        // unsigned int d_size;  // Total size of the data, in memory, as bytes
        new_data->d_size = source->d_size;
        // void *d_ptr;          // Pointer to data
        new_data->d_ptr = calloc(1, new_data->d_size);
        if (!(new_data->d_ptr))
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            HARKLE_ERROR(_copy_any_data, Failed to allocate memory);
            retval = RET_ERROR;
        }
        else
        {
            memcpy(new_data->d_ptr, source->d_ptr, new_data->d_size);
        }
    }
    // Verify
    if (RET_SUCCESS == retval)
    {
        if (false == _compare_any_data(source, new_data, &retval))
        {
            fprintf(stderr, "Failed to successfully copy %p to %p in _copy_any_data()\n",
                    source, new_data);
            retval = RET_ERROR;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval && new_data)
    {
        destroy_any_data(new_data);
        new_data = NULL;
    }
    return new_data;
}


return_value _push_any_data(stack_adt_ptr stack, any_data_ptr new_data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_stack(stack);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(new_data);
    }

    // CHECK IT
    if (RET_SUCCESS == retval)
    {
        if (0 == stack->top)
        {
            // Stack is full so let's resize
            retval = _resize_stack_array(stack);
        }
    }

    // PUSH IT
    if (RET_SUCCESS == retval)
    {
        // Is there room?
        if (stack->top > 0)
        {
            stack->top -= 1;
            (*(stack->array + stack->top)) = new_data;
        }
        else
        {
            fprintf(stderr, "The stack should have resized!\n");
            retval = RET_FULL;  // PLACEHOLDER
        }
    }

    // DONE
    return retval;
}


return_value _resize_stack_array(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    unsigned int new_cap = 0;           // New capacity
    stack_adt temp_stack;               // Temp storage

    // INPUT VALIDATION
    retval = _validate_stack(stack);

    // INITIALIZATION
    if (RET_SUCCESS == retval)
    {
        temp_stack.capacity = 0;
        temp_stack.top = 0;
        temp_stack.array = NULL;
    }

    // RESIZE IT
    // Make a new array
    if (RET_SUCCESS == retval)
    {
        new_cap = stack->capacity * 2;
        retval = _allocate_stack_array(&temp_stack, new_cap);
    }
    // Move the any_data pointers to the new array
    if (RET_SUCCESS == retval)
    {
        for (int i = stack->capacity - 1; i >= 0; i--)
        {
            retval = _push_any_data(&temp_stack, (*(stack->array + i)));
            if (RET_SUCCESS != retval)
            {
                fprintf(stderr, "Resize operations failed to push stack->array[%d]\n", i);
                break;  // Encountered an error so let's stop
            }
        }
    }
    // All the moves succeeded so let's replace the old with the new
    if (RET_SUCCESS == retval)
    {
        free(stack->array);
        stack->array = temp_stack.array;
        stack->top = temp_stack.top;
        stack->capacity = temp_stack.capacity;
    }

    // DONE
    if (RET_SUCCESS != retval && temp_stack.array)
    {
        free(temp_stack.array);
        temp_stack.array = NULL;
    }
    return retval;
}


return_value _validate_any_data(any_data_ptr data)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!data)
    {
        retval = RET_INV_PARAM;
    }
    else
    {
        retval = _validate_raw_data(data->d_ptr, data->d_type, data->d_size);
    }

    // DONE
    return retval;
}


return_value _validate_raw_data(void *raw_data, data_type raw_data_type, unsigned int raw_data_size)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!raw_data)
    {
        retval = RET_INV_PARAM;
    }
    else if (NULL_DT == raw_data_type)
    {
        retval = RET_INV_PARAM;
    }
    else if (raw_data_size < 1)
    {
        retval = RET_INV_PARAM;
    }

    // DONE
    return retval;
}


return_value _validate_stack(stack_adt_ptr stack)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!stack)
    {
        retval = RET_INV_PARAM;  // NULL pointer
    }
    else if (stack->capacity < 1)
    {
        retval = RET_INV_PARAM;  // Invalid stack capacity
    }
    else if (stack->top > stack->capacity)
    {
        retval = RET_INV_PARAM;  // Invalid stack count
    }
    else
    {
        for (unsigned int i = stack->top; i < stack->capacity; i++)
        {
            retval = _validate_any_data((*(stack->array + i)));
            if (RET_SUCCESS != retval)
            {
                break;  // Bad entry
            }
        }
    }

    // DONE
    return retval;
}
