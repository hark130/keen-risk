#include "8-04-hash_table-solution.h"
#include <stdio.h>   // fprintf()
#include <string.h>  // strerror()


int main()
{
    // LOCAL VARIABLES
    hash_table_ptr table = NULL;        // Hash table
    int start_cap = 20;                 // Hash table starting capacity
    return_value result = RET_SUCCESS;  // Out parameter for certain library calls

    table = create_hash_table(start_cap, &result);
    if (!table)
    {
        fprintf(stderr, "The call to create_hash_table() returned NULL\n");
        if (result)
        {
            fprintf(stderr, "create_hash_table(): %s\n", strerror(result));
        }
    }

    // DONE
    if (table)
    {
        result = destroy_table(table);
        if (result)
        {
            fprintf(stderr, "destroy_table() failed with %d", result);
        }
        table = NULL;
    }
    return result;
}
