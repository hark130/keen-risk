/*
 *  This file is where the 8-04 student labs should be completed.
 *  This source file implements the library functions declared in 8-04-hash_table.h.
 *  Keep an eye out for phrases like "CODE GOES HERE", "SPOILER ALERT", and "PRO TIP".
 *  Don't suffer in silence.  Your 2nd trouble-shooting step should be to ask for help.
 *  The instructor has an example solution for this file and might be willing to share.
 */

#include "8-04-hash_functions.h"
#include "8-04-hash_table.h"


/* PRO TIP: Consider defining a data structure for storing key/value pairs in the hash table. */


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/


hash_table_ptr create_hash_table(unsigned int capacity, float threshold, return_value_ptr result)
{
    // LOCAL VARIABLES
    hash_table_ptr new_table = NULL;  // Heap-allocated hash table
    /* SPOILER ALERT: The threshold argument won't be used until lab 8-04-3. */

    /* !!! CODE GOES HERE !!! */

    return new_table;
}


any_data_ptr find_value(hash_table_ptr table, any_data_ptr key, return_value_ptr result)
{
    // LOCAL VARIABLES
    any_data_ptr value = NULL;  // The value from the entry

    /* !!! CODE GOES HERE !!! */

    return value;
}


return_value add_key(hash_table_ptr table, any_data_ptr key, any_data_ptr value)
{
    // LOCAL VARIABLES
    return_value retval = RET_ERROR;  // Function call results

    /* !!! CODE GOES HERE !!! */

    return retval;
}


return_value delete_key(hash_table_ptr table, any_data_ptr key)
{
    // LOCAL VARIABLES
    return_value retval = RET_ERROR;  // Function call results

    /* !!! CODE GOES HERE !!! */

    return retval;
}


return_value delete_all_keys(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_ERROR;  // Function call results

    /* !!! CODE GOES HERE !!! */

    return retval;
}


return_value destroy_table(hash_table_ptr table)
{
    // LOCAL VARIABLES
    return_value retval = RET_ERROR;  // Function call results

    /* !!! CODE GOES HERE !!! */

    return retval;
}
