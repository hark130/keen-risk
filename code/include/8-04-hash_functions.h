#ifndef _8_04_HASH_FUNCTIONS_
#define _8_04_HASH_FUNCTIONS_

#define ERROR_HASH (unsigned long)0-1


/*
 *  Barely a hash algorithm.  Adds up hex values.
 *  PROS: Easily replicates hash collisions.
 *  CONS: Easily replicates hash collisions.
 *
 *  ARGS:
 *      data - Pointer holding the data to hash.
 *      size - The size of the data in bytes.
 *
 *  RETURNS: ERROR_HASH on error, hash value on success.
 */
unsigned long get_jank_hash(void* data, unsigned int size);


/*
 *  Fowler-Noll-Vo (FNV) hash function.
 *  PROS: Simple and fast.
 *  CONS: The FNV is not a randomized or cryptographic hash function so it's possible for
 *        attackers to create keys with collisions and slow down lookups.
 *
 *  ARGS:
 *      data - Pointer holding the data to hash.
 *      size - The size of the data in bytes.
 *
 *  RETURNS: ERROR_HASH on error, hash value on success.
 */
unsigned long get_fnv_hash(void* data, unsigned int size);


#endif  /* _8_04_HASH_FUNCTIONS_ */
