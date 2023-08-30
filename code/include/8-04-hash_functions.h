/*
 *  This header file defines the two different hash functions for use by the 8-04 student labs.
 *  Hash tables require hash functions but the 8.4 JQS line item doesn't explicitly require
 *  developers write their own.
 *
 *  All things being equal, get_fnv_hash() is preferable but get_jank_hash() could help when
 *  testing how well a hash table handles hash collisions.
 */

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
