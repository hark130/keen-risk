

#include "8-02-2-circular_list.h"
#include "8-02-sort_functions.h"
#include <errno.h>  // errno
#include <stdio.h>  // fprintf()
#include <stdlib.h>  // calloc()
#include <string.h>  // strerror()



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
 *  Allocate a new any_data struct and copy data into it.  Allocate a new circular_node struct
 *  and add the copy of data to it.  Returns NULL on failure (see: result).
 */
circular_node_ptr _allocate_node(any_data_ptr data, return_value_ptr result);

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
 *  Delete data_ptr, zeroize contents, and free old_node.
 */
return_value _delete_circular_node(circular_node_ptr old_node);

/*
 *  Zeroize the data and free the data pointer.  Then zeroize the pointer, type and size.  Then
 *  free the any_data struct pointer.
 */
return_value _destroy_any_data(any_data_ptr old_data);

/*
 *  Insert new_node in front of old_node.  Full validation for old_node but new_node is barely
 *  validated.
 */
return_value _insert_here(circular_node_ptr new_node, circular_node_ptr old_node);

/*
 *  Insert new node at position pos.  Head node counts as position 1.
 */
return_value _insert_node(circular_list_ptr c_list, circular_node_ptr new_node, unsigned int pos);

/*
 *  Remove this node from the circular linked list.
 */
return_value _remove_node(circular_node_ptr old_node);

/*
 *  Validates any_data structs on behalf of the library.
 */
return_value _validate_any_data(any_data_ptr data);

/*
 *  Validates a circular_list struct pointer: not NULL, either head and tail both NULL or both
 *  not NULL.
 */
return_value _validate_circular_list(circular_list_ptr c_list);

/*
 *  Validates a circular_node struct pointer.  Returns RET_INV_PARAM if c_node is NULL.  Returns
 *  RET_ERROR if c_node is not part of a circular linked list.
 */
return_value _validate_circular_node(circular_node_ptr c_node);

/*
 *  Validates raw data on behalf of the library.
 */
return_value _validate_raw_data(void *raw_data, data_type raw_data_type,
                                unsigned int raw_data_size);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


circular_list_ptr create_circular_list(return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    circular_list_ptr c_list = NULL;    // Heap-allocated circular_list pointer
    int errnum = 0;                 // Errno value

    // INPUT VALIDATION
    if (!result)
    {
        retval = RET_INV_PARAM;
    }

    // CREATE IT
    if (RET_SUCCESS == retval)
    {
        c_list = calloc(1, sizeof(circular_list));
        if (!c_list)
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            HARKLE_ERROR(create_circular_list, Calloc failed to allocate a circular_list struct);
            retval = RET_ERROR;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return c_list;
}


return_value empty_the_list(circular_list_ptr c_list)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    circular_node_ptr tmp_node = NULL;  // Temp node to iterate the list
    circular_node_ptr tmp_next = NULL;  // Temp next node to iterate the list

    // INPUT VALIDATION
    retval = _validate_circular_list(c_list);

    // EMPTY IT
    if (RET_SUCCESS == retval)
    {
        tmp_node = c_list->head_ptr;
        while (tmp_node)
        {
            tmp_next = tmp_node->next_ptr;
            retval = _remove_node(tmp_node);
            if (RET_SUCCESS == retval)
            {
                retval = _delete_circular_node(tmp_node);
            }
            if (RET_SUCCESS != retval)
            {
                break;  // Encountered an error
            }
            c_list->entries -= 1;  // Best effort bookkeeping
            tmp_node = tmp_next;  // Iterate to the next node
        }
    }
    // Update bookkeeping
    if (RET_SUCCESS == retval)
    {
        c_list->head_ptr = NULL;
        c_list->tail_ptr = NULL;
        c_list->entries = 0;  // Zeroize it just in case the count was wrong
    }

    // DONE
    return retval;
}


return_value delete_list(circular_list_ptr c_list)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // DELETE IT
    // Empty it
    retval = empty_the_list(c_list);
    // Delete it
    if (RET_SUCCESS == retval)
    {
        free(c_list);
    }

    // DONE
    return retval;
}


circular_node_ptr find_node_pos(circular_list_ptr c_list, unsigned int pos,
                                return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;    // Function call results
    unsigned int counter = 0;             // Count the positions
    circular_node_ptr needle_ptr = NULL;  // Node found at position pos

    // INPUT VALIDATION
    retval = _validate_circular_list(c_list);
    if (RET_SUCCESS == retval)
    {
        if (!result)
        {
            retval = RET_INV_PARAM;
        }
        else if (pos > c_list->entries)
        {
            retval = RET_NOT_FOUND;
        }
    }

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        tmp_node = c_list->head_ptr;
        for (int i = 1; i <= c_list->entries; i++)
        {
            retval = _validate_circular_node(tmp_node);
            if (RET_SUCCESS != retval)
            {
                break;  // This circular list is broken
            }
            else if (counter == pos)
            {
                needle_ptr = tmp_node;
                break;
            }
            tmp_node = tmp_node->next_ptr;
        }
        if (!needle_ptr)
        {
            retval = RET_NOT_FOUND;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return needle_ptr;
}


return_value insert_data(circular_list_ptr c_list, any_data_ptr node_data, unsigned int pos)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    circular_node_ptr new_node = NULL;  // New node, with a copy of node_data, on the heap

    // INPUT VALIDATION
    retval = _validate_circular_list(c_list);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(node_data);
    }

    // MAKE A NODE
    if (RET_SUCCESS == retval)
    {
        new_data = _allocate_node(node_data, &retval);
        if (!new_data && RET_SUCCESS == retval)
        {
            retval = RET_ERROR;  // Suffer not the NULL pointer
        }
    }

    // INSERT IT
    if (RET_SUCCESS == retval)
    {
        // HERE
    }

    // DONE
    return retval;
}


return_value remove_node_pos(circular_list_ptr c_list, unsigned int pos)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // DONE
    return retval;
}


circular_node_ptr find_node_val(circular_list_ptr c_list, any_data_ptr needle,
                                return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;     // Function call results
    circular_node_ptr needle_node = NULL;  // Node found matching data needle

    // DONE
    if (result)
    {
        *result = retval;
    }
    return needle_node;
}


return_value sort_list(circular_list_ptr c_list, compare_any_data comp_func)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

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


circular_node_ptr _allocate_node(any_data_ptr new_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;                         // Function call results
    any_data_ptr new_node = calloc(1, sizeof(circular_node));  // New any_data struct
    int errnum = errno;                                        // Errno value

    // VALIDATION
    if (!new_node)
    {
        HARKLE_ERRNO(_allocate_any_data, errnum);  // Already captured errno
        HARKLE_ERROR(_allocate_any_data, Calloc failed to allocate a new entry);
        retval = RET_ERROR;
    }
    else
    {
        new_node->data_ptr = _copy_any_data(new_data, &retval);
        if (RET_SUCCESS != retval)
        {
            new_node->data_ptr = NULL;
        }
        else if (NULL == new_node->data_ptr)
        {
            retval = RET_ERROR;  // Success and NULL are incompatible
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_data;
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
        _destroy_any_data(new_data);
        new_data = NULL;
    }
    return new_data;
}


return_value _delete_circular_node(circular_node_ptr old_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!old_node)
    {
        retval = RET_INV_PARAM;
    }

    // DELETE IT
    // any_data
    if (RET_SUCCESS == retval)
    {
        retval = _destroy_any_data(old_node->data_ptr);
    }
    // old_node
    if (RET_SUCCESS == retval)
    {
        old_node->data_ptr = NULL;
        old_node->prev_ptr = NULL;
        old_node->next_ptr = NULL;
        free(old_node);
    }

    // DONE
    return retval;
}


return_value _destroy_any_data(any_data_ptr old_data)
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


return_value _insert_here(circular_node_ptr new_node, circular_node_ptr old_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_circular_node(old_node);
    if (RET_SUCCESS == retval && !new_node)
    {
        retval = RET_INV_PARAM;
    }

    // INSERT HERE
    if (RET_SUCCESS == retval)
    {
        // Upstream linkage
        new_node->prev_ptr = old_node->prev_ptr;
        old_node->prev_ptr->next_ptr = new_node;
        // Downstream linkage
        new_node->next_ptr = old_node;
        old_node->prev_ptr = new_node;
    }

    // DONE
    return retval;
}


return_value _insert_node(circular_list_ptr c_list, circular_node_ptr new_node, unsigned int pos)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    circular_node_ptr tmp_node = NULL;  // Node found at position pos

    // INPUT VALIDATION
    retval = _validate_circular_list(c_list);
    if (RET_SUCCESS == retval && !new_node)
    {
        retval = RET_INV_PARAM;
    }

    // INSERT IT
    if (RET_SUCCESS == retval)
    {
        // First node
        if (NULL == c_list->head_ptr)
        {
            c_list->head_ptr = new_node;
            c_list->tail_ptr = new_node;
            new_node->prev_ptr = new_node;
            new_node->next_ptr = new_node;
        }
        // New head node
        if (1 == pos)
        {
            tmp_node = c_list->head_ptr;
            retval = _insert_here(new_node, tmp_node);
            if (RET_SUCCESS == retval)
            {
                c_list->head_ptr = new_node;  // New head node
            }
        }
        // New tail
        else if (pos >= c_list->entries)
        {
            tmp_node = c_list->tail_ptr->next_ptr;
            retval = _insert_here(new_node, tmp_node);
            if (RET_SUCCESS == retval)
            {
                c_list->tail_ptr = new_node;
            }
        }
        // Chain node
        else
        {
            tmp_node = find_node_pos(c_list, pos, &retval);
            if (RET_SUCCESS == retval)
            {
                retval = _insert_here(new_node, tmp_node);
            }
        }
    }

    // DONE
    if (RET_SUCCESS == retval)
    {
        c_list->entries += 1;  // Increment the count
    }
    return retval;
}


return_value _remove_node(circular_node_ptr old_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_circular_node(old_node);

    // REMOVE IT
    if (RET_SUCCESS == retval)
    {
        old_node->prev_ptr->next_ptr = old_node->next_ptr;
        old_node->next_ptr->prev_ptr = old_node->prev_ptr;
        old_node->prev_ptr = NULL;
        old_node->next_ptr = NULL;
    }

    // DONE
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


return_value _validate_circular_list(circular_list_ptr c_list)
{
    // LOCAL VARIABLES
    return_value retval = RET_INV_PARAM;  // Function call results

    // INPUT VALIDATION
    if (c_list)
    {
        // Empty circular list (which is fine)
        if (NULL == c_list->head_ptr && NULL == c_list->tail_ptr && 0 == c_list->entries)
        {
            retval = RET_SUCCESS;  // Empty circular lists are fine
        }
        // Non-empty circular list
        else if (c_list->head_ptr && c_list->tail_ptr && c_list->entries > 0)
        {
            retval = _validate_circular_node(c_list->head_ptr);
            if (RET_SUCCESS == retval)
            {
                retval = _validate_circular_node(c_list->tail_ptr);
            }
        }
    }

    // DONE
    return retval;
}


return_value _validate_circular_node(circular_node_ptr c_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!c_node)
    {
        retval = RET_INV_PARAM;
    }
    else if (NULL == c_node->prev_ptr || NULL == c_node->next_ptr)
    {
        retval = RET_ERROR;
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