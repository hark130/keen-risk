/*
 *  This header file declares functions used in the 8-05 labs.  It defines an interface that
 *  should suffice for either array or linked list implementations.  The containing struct is
 *  abstracted for the user and defined by the actual implementation.  The complete implementation
 *  of this stack should allow it to grow indefinitely, limited only by the host's resources.
 *  The strategy for that stack growth is dependent on the underlying implementation: array,
 *  linked list.
 *
 *  Consider these functions the entry point of the library.  Validate all input.
 *  In general, the library is responsible for allocating memory to copy user input.
 *  The any_data structs are used to format user input, but the library does not own the contents.
 *  Data stored in the stack should be duplicated and stored in the heap.
 */

#ifndef _8_05_STRUCT_ADT_
#define _8_05_STRUCT_ADT_


#include "8-00-definitions.h"  // any_data, any_data_ptr, return_value, return_value_ptr
#include <stdbool.h>  // bool


/* A Stack Abstract Data Type */
typedef struct _stack_adt stack_adt, *stack_adt_ptr;


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in suggested implementation order.


/*
 *  Allocate and return a stack_adt struct pointer.  The stack stores and retrieves LIFO
 *  data.  The stack's storage size will be able to grow to match new entries.  Returns NULL on
 *  failure (consult result).
 */
stack_adt_ptr allocate_stack(unsigned int initial_capacity, return_value_ptr result);

/*
 *  Copies new_data into heap-allocated memory and pushes that data onto the stack.  Ensure
 *  new_data is LIFO.
 */
return_value push_data(stack_adt_ptr stack, any_data_ptr new_data);

/*
 *  Returns the LIFO data from the stack without removing it from the stack.  Do *NOT* free the
 *  pointer returned by this function.  Returns NULL on empty stack or failure (consult result).
 */
any_data_ptr get_top(stack_adt_ptr stack, return_value_ptr result);

/*
 *  Remove and return the top data from the stack.  The caller is responsible for free()ing this
 *  pointer returned by this function.  Use destroy_any_data();  Returns NULL on failure
 *  (consult result).
 */
any_data_ptr pop_data(stack_adt_ptr stack, return_value_ptr result);

/*
 *  Returns the number of elements contained in the stack.  Returns 0 for an empty stack and
 *  -1 on failure (consult result).
 */
int get_size(stack_adt_ptr stack, return_value_ptr result);

/*
 *  Returns true if stack is empty (and error).  Consult result to verify success.
 */
bool is_empty(stack_adt_ptr stack, return_value_ptr result);

/*
 *  Remove and free all entries from the stack.  Returns success even if the stack was already
 *  empty.
 */
return_value empty_stack(stack_adt_ptr stack);

/*
 *  Remove and free all entries from the stack.  Then free the stack_adt_ptr.  Calls empty_stack()
 *	under the hood.
 */
return_value destroy_stack(stack_adt_ptr stack);

/*
 *  Free all heap-allocated memory from old_data.  Only use this function for any_data_ptr values
 *  returned by pop();
 */
return_value destroy_any_data(any_data_ptr old_data);


#endif  /* _8_05_STRUCT_ADT_ */
