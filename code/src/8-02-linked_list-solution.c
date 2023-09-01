/*
 *  PLACEHOLDER
 */

#include "8-02-linked_list.h"
#include <errno.h>    // errno
#include <stdbool.h>  // true, false, bool
#include <stdlib.h>   // calloc(), free()
#include <stdio.h>    // fprintf()
#include <string.h>   // memset()



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
 *  Appends a new_node to the end of the linked list found at head_node.
 */
return_value _append_node(list_node_ptr head_node, list_node_ptr new_node);

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
 *  Allocate a new node and copy in heap-allocated data copied from source.  Returns NULL on
 *  failure.  See result for details.
 */
list_node_ptr _create_new_node(any_data_ptr source, return_value_ptr result);

/*
 *  Zeroize the data and free the data pointer.  Then zeroize the pointer, type and size.  Then
 *  free the any_data struct pointer.
 */
return_value _destroy_any_data(any_data_ptr old_data);

/*
 *  Destroy the data and old_node pointer.  Does not alter its position in a linked list.
 *  That is the caller's responsibility.
 */
return_value _destroy_node(list_node_ptr old_node);

/*
 *  Validates any_data structs on behalf of the library.
 */
return_value _validate_any_data(any_data_ptr data);

/*
 *  Validate a single node.  Checks the contents of its data_ptr member.
 */
return_value _validate_node(list_node_ptr node);

/*
 *  Validates raw data on behalf of the library.
 */
return_value _validate_raw_data(void *raw_data, data_type raw_data_type,
                                unsigned int raw_data_size);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/
// Library functions listed in header order.


list_node_ptr append_data(list_node_ptr head_node, any_data_ptr node_data, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr new_head = head_node;  // Pointer to the new(?) head node
    list_node_ptr new_node = NULL;       // Pointer to the newly allocated node

    // INPUT VALIDATION
    retval = _validate_any_data(node_data);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // APPEND IT
    // Allocate
    if (RET_SUCCESS == retval)
    {
        new_node = _create_new_node(node_data, &retval);
        if (!new_node && RET_SUCCESS == retval)
        {
            retval = RET_ERROR;
        }
    }
    // Add it
    if (RET_SUCCESS == retval)
    {
        if (new_head)
        {
            retval = _append_node(new_head, new_node);
        }
        else
        {
            new_head = new_node;  // The new node *is* the head node
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval)
    {
        new_head = NULL;
        if (new_node)
        {
            _destroy_node(new_node);
            new_node = NULL;
        }
    }
    return new_head;
}


return_value delete_list(list_node_ptr head_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr new_head = head_node;  // Temp node to iterate the list
    list_node_ptr tmp_node = NULL;       // Return value from remove_node_pos()

    // INPUT VALIDATION
    retval = _validate_node(head_node);

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        while(new_head)
        {
            tmp_node = remove_node_pos(new_head, 1, &retval);
            if (RET_SUCCESS != retval)
            {
                break;
            }
            else
            {
                new_head = tmp_node;
            }
        }
    }

    // DONE
    return retval;
}


unsigned int count_nodes(list_node_ptr head_node)
{
    // LOCAL VARIABLES
    unsigned int count = 0;              // Current count
    list_node_ptr tmp_node = head_node;  // Temp node to iterate the list

    // COUNT IT
    while (tmp_node)
    {
        count++;
        tmp_node = tmp_node->next_ptr;
    }

    // DONE
    return count;
}


list_node_ptr find_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr tmp_node = head_node;  // Temp node to iterate the list
    unsigned int cur_pos = 0;            // Counter variable

    // INPUT VALIDATION
    retval = _validate_node(head_node);
    if (RET_SUCCESS == retval)
    {
        if (pos < 1 || !result)
        {
            retval = RET_INV_PARAM;
        }
    }

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        retval = RET_NOT_FOUND;
        while(tmp_node)
        {
            cur_pos++;
            if (cur_pos == pos)
            {
                retval = RET_SUCCESS;
                break;  // Found it
            }
            else
            {
                tmp_node = tmp_node->next_ptr;
            }
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return tmp_node;
}


 list_node_ptr insert_data(list_node_ptr head_node, any_data_ptr node_data, unsigned int pos,
 	                       return_value_ptr result)
 {
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr new_head = head_node;  // Pointer to the new(?) head node
    list_node_ptr new_node = NULL;       // Pointer to the newly allocated node
    list_node_ptr tmp_node = NULL;       // Node at position pos - 1

    // INPUT VALIDATION
    retval = _validate_any_data(node_data);
    if (RET_SUCCESS == retval)
    {
        if (!result || pos < 1)
        {
            retval = RET_INV_PARAM;
        }
    }

    // INSERT IT
    // Create node
    if (RET_SUCCESS == retval)
    {
        new_node = _create_new_node(node_data, &retval);
        if (!new_node && RET_SUCCESS == retval)
        {
            retval = RET_ERROR;
        }
    }
    // Insert node
    if (RET_SUCCESS == retval)
    {
        if (1 == pos)
        {
            // New node is the new head node
            new_node->next_ptr = head_node;
            new_head = new_node;
        }
        else if (pos > count_nodes(head_node))
        {
            retval = _append_node(new_head, new_node);
        }
        else
        {
            tmp_node = find_node_pos(head_node, pos - 1, &retval);
            if (tmp_node && RET_SUCCESS == retval)
            {
                new_node->next_ptr = tmp_node->next_ptr;  // Add downstream linkage to new_node
                tmp_node->next_ptr = new_node;  // Add new_node to upstream linkage
            }
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval)
    {
        if (new_node)
        {
            _destroy_node(new_node);
            new_node = NULL;            
        }
        new_head = NULL;  // Return NULL on failure.
    }

    return new_head;
 }


 list_node_ptr remove_node_pos(list_node_ptr head_node, unsigned int pos, return_value_ptr result)
 {
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr new_head = head_node;  // Pointer to the new(?) head node
    list_node_ptr tmp_node = head_node;  // Temp node to iterate the list
    list_node_ptr old_node = NULL;       // Node to 
    unsigned int cur_pos = 1;            // Counter variable

    // INPUT VALIDATION
    retval = _validate_node(head_node);
    if (RET_SUCCESS == retval)
    {
        if (pos < 1 || !result)
        {
            retval = RET_INV_PARAM;
        }
    }

    // REMOVE IT
    if (RET_SUCCESS == retval)
    {
        // Use Case: Pos 1
        if (1 == pos)
        {
            old_node = new_head;        // Store the pointer to destroy
            new_head = new_head->next_ptr;  // Next node is the new head node
        }
        else
        {
            retval = RET_NOT_FOUND;
            while(tmp_node->next_ptr)
            {
                cur_pos++;
                if (cur_pos == pos)
                {
                    retval = RET_SUCCESS;
                    old_node = tmp_node->next_ptr;  // Store the pointer to destroy
                    tmp_node->next_ptr = old_node->next_ptr;  // Remove it from the linked list
                    break;  // Stop looking
                }
                else
                {
                    tmp_node = tmp_node->next_ptr;
                }
            }
        }
    }
    // DESTROY IT
    if (RET_SUCCESS == retval)
    {
        retval = _destroy_node(old_node);
        old_node = NULL;
    }
    else
    {
        new_head = NULL;
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_head;
 }


list_node_ptr find_node_val(list_node_ptr head_node, any_data_ptr needle, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr tmp_node = head_node;  // Temp node to iterate the list
    list_node_ptr needle_node = NULL;    // Node pointer with data that matches needle

    // INPUT VALIDATION
    // Head node gets validated in the while loop below
    if (RET_SUCCESS == retval)
    {
        retval = _validate_any_data(needle);
    }
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // FIND IT
    if (RET_SUCCESS == retval)
    {
        while(tmp_node)
        {
            retval = _validate_node(tmp_node);
            if (RET_SUCCESS != retval)
            {
                fprintf(stderr, "Found an invalid node with find_node_val(): %d\n", retval);
                break;  // Error encountered
            }
            else if (true == _compare_any_data(needle, tmp_node->data_ptr, &retval))
            {
                needle_node = tmp_node;  // Found it
                break;  // Stop looking
            }
            else
            {
                tmp_node = tmp_node->next_ptr;  // Check the next node
            }
        }
        if (!needle_node)
        {
            retval = RET_NOT_FOUND;  // Didn't find a match
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    return needle_node;
}


// return_value sort_list(list_node_ptr head_node, SORT FUNCTION POINTER PLACEHOLDER);


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


return_value _append_node(list_node_ptr head_node, list_node_ptr new_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;   // Function call results
    list_node_ptr tmp_node = head_node;  // Temp node to iterate the list

    // INPUT VALIDATION
    retval = _validate_node(head_node);
    if (RET_SUCCESS == retval)
    {
        retval = _validate_node(new_node);
    }

    // APPEND IT
    if (RET_SUCCESS == retval)
    {
        while (tmp_node->next_ptr)
        {
            tmp_node = tmp_node->next_ptr;
        }
        tmp_node->next_ptr = new_node;
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
        _destroy_any_data(new_data);
        new_data = NULL;
    }
    return new_data;
}


list_node_ptr _create_new_node(any_data_ptr source, return_value_ptr result)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results
    any_data_ptr new_data = NULL;       // New heap-allocated any_data struct copied from source
    list_node_ptr new_node = NULL;      // New heap-allocated list_node struct pointer
    int errnum = 0;                     // Errno value

    // INPUT VALIDATION
    retval = _validate_any_data(source);
    if (RET_SUCCESS == retval && !result)
    {
        retval = RET_INV_PARAM;
    }

    // CREATE IT
    // Create new any_data_ptr
    if (RET_SUCCESS == retval)
    {
        new_data = _copy_any_data(source, &retval);
    }
    // Create new node
    if (RET_SUCCESS == retval)
    {
        new_node = calloc(1, sizeof(list_node));
        if (!new_node)
        {
            errnum = errno;
            HARKLE_ERRNO(calloc, errnum);
            HARKLE_ERROR(_copy_any_data, Failed to allocate memory);
            retval = RET_ERROR;
        }
        else
        {
            new_node->data_ptr = new_data;
        }
    }

    // DONE
    if (result)
    {
        *result = retval;
    }
    if (RET_SUCCESS != retval)
    {
        if (new_node)
        {
            _destroy_node(new_node);  // Will also destroy the node's data
        }
        else if (new_data)
        {
            _destroy_any_data(new_data);
        }
        new_node = NULL;
        new_data = NULL;
    }
    return new_node;
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


return_value _destroy_node(list_node_ptr old_node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    retval = _validate_node(old_node);

    // DESTROY IT
    // Data
    if (RET_SUCCESS == retval)
    {
        retval = _destroy_any_data(old_node->data_ptr);
    }
    // Node
    if (RET_SUCCESS == retval)
    {
        old_node->data_ptr = NULL;
        old_node->next_ptr = NULL;
        free(old_node);
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


return_value _validate_node(list_node_ptr node)
{
    // LOCAL VARIABLES
    return_value retval = RET_SUCCESS;  // Function call results

    // INPUT VALIDATION
    if (!node)
    {
        retval = RET_INV_PARAM;
    }
    else
    {
        retval = _validate_any_data(node->data_ptr);
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
