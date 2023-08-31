/*
 *  PLACEHOLDER
 */

#include "8-02-linked_list.h"


/**************************************************************************************************/
/********************************* INTERNAL FUNCTION DECLARATIONS *********************************/
/**************************************************************************************************/

/*
 *  Appends a new_node to the end of the linked list found at head_node.
 */
return_value _append_node(list_node_ptr head_node, list_node_ptr new_node);

/*
 *  Allocates a new any_data struct on the heap, copies over the source bookkeeping values,
 *  allocates a heap-buffer for the new any_data.d_ptr, and memcpy()s source->d_ptr into the
 *  new buffer.  If any part of the process fails, this function will free() all allocated memory,
 *  updated result, and return NULL.
 */
any_data_ptr _copy_any_data(any_data_ptr source, return_value_ptr result);

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
        new_node = _copy_any_data(node_data, &retval);
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
    if (RET_SUCCESS != result)
    {
        new_head = NULL;
        if (new_node)
        {
            _destroy_any_data(new_node);
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
            tmp_node = remove_node_pos(new_head, 0, &retval);
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
        tmp_node = tmp_node->next;
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
                tmp_node = tmp_node->next;
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
 	                       return_value_ptr result);


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
            new_head = new_head->next;  // Next node is the new head node
        }
        else
        {
            retval = RET_NOT_FOUND;
            while(tmp_node->next)
            {
                cur_pos++;
                if (cur_pos == pos)
                {
                    retval = RET_SUCCESS;
                    old_node = tmp_node->next;        // Store the pointer to destroy
                    tmp_node->next = old_node->next;  // Remove that pointer from the linked list
                    break;  // Stop looking
                }
                else
                {
                    tmp_node = tmp_node->next;
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

    // DONE
    if (result)
    {
        *result = retval;
    }
    return new_head;
 }


list_node_ptr find_node_val(list_node_ptr head_node, any_data_ptr needle, return_value_ptr result);


// return_value sort_list(list_node_ptr head_node, SORT FUNCTION POINTER PLACEHOLDER);


/**************************************************************************************************/
/*************************************** INTERNAL FUNCTIONS ***************************************/
/**************************************************************************************************/


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
        while (tmp_node->next)
        {
            tmp_node = tmp_node->next;
        }
        tmp_node->next = new_node;
    }

    // DONE
    return retval
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
        new_data->d_ptr = calloc(new_data->d_size, 1);
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
        old_node->next = NULL;
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
