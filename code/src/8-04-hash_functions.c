#include "8-04-hash_functions.h"


/**************************************************************************************************/
/********************************* INTERNAL FUNCTION DECLARATIONS *********************************/
/**************************************************************************************************/


/*
 *  Validates input on behalf of the library.  Returns ERROR_HASH on bad input.
 */
unsigned long _validate_input(void* data, unsigned int size);


/**************************************************************************************************/
/*************************************** LIBRARY FUNCTIONS ****************************************/
/**************************************************************************************************/


unsigned long get_jank_hash(void* data, unsigned int size)
{
    // LOCAL VARIABLES
    unsigned long hash = 0;  // Calculated hash

    // INPUT VALIDATION
    hash = _validate_input(data, size);

    // HASH IT
    if (ERROR_HASH != hash)
    {
        for (int i = 0; i < size; i++)
        {
            hash += (*((char*)data + i));
        }
    }

    // DONE
    return hash;
}


unsigned long get_fnv_hash(void* data, unsigned int size)
{
    // LOCAL VARIABLES
    const unsigned long fnv_prime = 0x811C9DC5;  // Large prime number
    unsigned long hash = 0;                      // Calculated hash

    // INPUT VALIDATION
    hash = _validate_input(data, size);

    // HASH IT
    if (ERROR_HASH != hash)
    {
        for (int i = 0; i < size; i++)
        {
            hash *= fnv_prime;
            hash ^= (*((char*)data + i));
        }
    }

    // DONE
    return hash;
}


/**************************************************************************************************/
/*************************************** INTERNAL FUNCTIONS ***************************************/
/**************************************************************************************************/


unsigned long _validate_input(void* data, unsigned int size)
{
    // LOCAL VARIABLES
    unsigned long result = 0;

    // INPUT VALIDATION
    if (!data || size < 1)
    {
        result = ERROR_HASH;
    }

    // DONE
    return result;
}
