:title: C Programming - Data Structures - Hash Table
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
8.4 Demonstrate skill in creating and using a hash table that accepts any data type

----

8.4 Demonstrate skill in creating and using a hash table that accepts any data type
===================================================================================

----

Objectives
========================================

* Creating a hash table with n number of items
* Navigating through a hash table to find the nth item
* Finding an item in a hash table
* Removing selected items from a hash table
* Inserting an item into a hash table
* Implement functionality to mitigate hash collisions within the hash table
* Removing all items from the hash table

.. note::

	I intend to accomplish these objectives in incremental stages.

----

Overview
========================================

* "Any data type"
* Data Structure Bookkeeping
* Hash Function
* Mitigating Hash Collisions
* Resizing
* Resources
* Student Labs

----

"Any data type"
========================================

How can you store "any data type"?

.. code:: c

	typedef enum _data_type
	{
	    NULL_DT = 0, CHAR_DT,
	    DOUBLE_DT, FLOAT_DT,
	    INT_DT, STRING_DT, VOID_DT
	} data_type, *data_type_ptr;

	typedef struct _any_data
	{
	    // Pointer to data
	    void *d_ptr;
	    // Data type
	    data_type d_type;
	    // Total data size
	    unsigned int d_size;
	} any_data, *any_data_ptr;

.. note::

	Whomever wrote the "any data type" objective hates students or meant "discrete data type".
	You store "any data type" by saving the raw data, the original data type, and the size of that data in memory.
	Walk them through a couple examples.

----

Data Structure Bookkeeping
========================================

How can a data structure dream?

.. code:: c

	typedef struct _hash_table
	{
		// Array of entries
	    void *table_ptr;
	    // Number of entries
	    unsigned int entries;
	    // Number of indices
	    unsigned int capacity;
	    // Load factor threshold
	    float threshold;
	} hash_table, *hash_table_ptr;

.. note::

	At any given time, a hash table needs to know how many entries it has, how much room is left, etc.
	Some of that data *could* be calculated at runtime but it's far more efficient to store-and-update.

----

Hash Function
========================================

Hash Function - Transforms a key into a slot index.

The 8-04-hash_functions only gives you half the answer: the hash.

Your code will have to compute the slot index.

.. code:: c

	get_jank_hash()

	// Fowler-Noll-Vo (FNV)
	get_fnv_hash();

.. code:: mathematica

	slot_index = get_fnv_hash(key) % table_size

.. note::

	It might help to have 8-04-hash_functions.h open in a code editor.

	A "hash collision" is when a hash function computes the same result for two different inputs.

	Focus on get_fnv_hash().  If someone asks about get_jank_hash(), tell them it's a poor hash function to help test hash collision mitigation.
	(Then again, the 8-04-2 unit test code does an adequate job of creating hash collisions from different keys.)

	The % is a reference to mod

	NOTE: I wanted to implement it all together but I decided against it.  I didn't want the students wrestling with hashing functions but I *did* want them to compute slot indices.

	TRANSITION: We know what a hash collision is now but what do we do with it?

----

Mitigating Hash Collisions
========================================

Hash collisions resolution:
	* Chain Results - Store key/value pairs as linked lists
	* Open Addressing - Probe-and-store

.. note::

	Also, discuss the difference between duplicates and hash collisions.
	(SPOILERS: The exact same key is a duplicate.  Different key, same hash is a collision.)

----

Resizing
========================================

One solution for a high load factor is to resize.

1. Allocates a new `void *table_ptr` with double the capacity (1)
2. Transfer all entries from the old `table_ptr` to the new `table_ptr`
3. Free the old `table_ptr`

\(1) Best practice is to round-up the capacity to a prime number

.. note::

	1. Make maximum reuse of existing code.  (Sounds like a job for `create_hash_table()`)

	2. There's a lot of "yadda yadda yadda" in that statement.
	The important thing to note for 2 is that we can't do this if we didn't store the keys (so store the keys).
	Also, the hash wouldn't have changed but the capacity did so the hash % capacity formulate will calculate all new slot indices.
	Lastly, if each `table_ptr` entry is heap-allocated, you can just move the pointers over.  No need to RE-allocate.
	Modular programming suggests there is the opportunity for a lot of reused code here.

	3. This is also easier said than done.
	There's a high chance for memory leaks here.

----

Resources
========================================

* Data Structures and Algorithms Made Easy Ch. 13 & 14
* Hash Table
    * https://en.wikipedia.org/wiki/Hash_table
    * https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/tutorial/

----

STUDENT LABS
========================================

All labs will utilize the 8-04-hash_table "library".
Each lab has unit tests available to validate your work.
Be sure to use ASAN and Valgrind.

* 8-04-1: Implement basic functionality: create, find, insert, remove, remove all, destroy
* 8-04-2: Mitigate hash collisions
* 8-04-3: Extend hash table capacity

General Files:
	* 8-04-hash_table.h - Defines the hash table interface
	* 8-04-hash_table-lab.c - Implments the hash table
	* 8-04-hash_functions.h - Declares hash functions
	* 8-04-hash_functions.c - Implments hash functions

.. note::

	These files will be used throughout all three labs
	The labs represent crawl-walk-run milestones while implementing a hash table
	Files
	The interface is already designed in 8-04-hash_table.h (wait for applause/thanks)
	It's important to note that 8-04-hash_table-lab.c is the single most important file in the list.  It's where the students do all their work.
	The 8-04-hash_functions library already defines two hashing algorithms to use in the hash table (wait for applause/thanks)

----

STUDENT LABS
========================================

8-04-1: Implement basic functionality: create, find, insert, remove, remove all, destroy

Key Files:
	* 8-04-1-hash_table-main.c - Unit tests for basic functionality

Suggested implementation order:
	1. create_hash_table()
	2. destroy_table()
	3. find_value()
	4. add_key()
	5. delete_key()
	6. delete_all_keys()

.. note::

	The file comment block includes a description, build instructions, and notes on testing.
	You might want to have 8-04-hash_table.h open in a code editor when discussing these.
	The function prototypes are copy/pasted from 8-04-hash_table.h.
	Essentially, the function comment blocks serve as instructions.
	The library function prototypes are presented in order of "recommended implementation"

	Suggested implementation order:
		1. create_hash_table() - Can't test a hash table if you don't have one.
		2. destroy_table() - Write the free() anytime you alloc() something.
		3. find_value() - Can't detect duplicates if you can't find a value
		4. add_key() - Should probably use find_value() to detect duplicates.
		5. delete_key() - Should probably underpin delete_all_keys().
		6. delete_all_keys() - Maybe refactor destroy_table() to use this.

	After 1 & 2 - Unit tests will be failing but you shouldn't have any memory leaks.
	After 3 & 4 - Most of the unit tests should be passing but you may have some leaks.
	After 5 & 6 - All of the unit tests should be passing, ASAN should be happy, and Valgrind should be happy.

	The students may appreciate a demonstration of the unit test build and execution (just to put them on the right path)

----

STUDENT LABS
========================================

8-04-2: Mitigate hash collisions

Key Files:
	* 8-04-2-hash_table-main.c - Hash collision unit tests

PRO TIP: Store the keys with the values.

.. note::

	The file comment block includes a description, build instructions, and notes on testing.
	Discuss resolution techniques with the students.  Encourage them to use chaining (AKA linked lists).
	Also, discuss the difference between duplicates and hash collisions.
	(SPOILERS: The exact same key is a duplicate.  Different key, same hash is a collision.)

----

STUDENT LABS
========================================

8-04-3: Extend hash table capacity

Key Files:
	* 8-04-3-hash_table-main.c - Load factor unit tests

Load factor = (entries) / (capacity)
	* High load factor == full table
	* High load factor == efficient hashing function (1)

\(1) Assuming hash collisions get rejected or handled by open addressing

For this lab, check the load factor when a user calls `add_key()`.

If the load factor exceeds the threshold, double the capacity (at least)

.. note::

	The file comment block includes a description, build instructions, and notes on testing.
	Discuss the beauty of abstraction.  Talk to the students about the "opaque" nature of table_ptr.
	(It's not for the user, it's for the library.  The user doesn't need to know about it.)
	The table_ptr member can be destroyed and remade larger or even realloc()d without the user knowing.
	Also, discuss the function comment block for create_hash_table() at length (with regards to resizing).

----

STUDENT LABS
========================================

8-04-3: Extend hash table capacity (cont)

.. code:: c

	typedef struct _hash_table
	{
	    // Array of entries
	    void *table_ptr;
	    // Number of entries
	    unsigned int entries;
	    // Number of indices
	    unsigned int capacity;
	    // Load factor threshold
	    float threshold;
	} hash_table, *hash_table_ptr;

.. note::

	The file comment block includes a description, build instructions, and notes on testing.
	Discuss the beauty of abstraction.  Talk to the students about the "opaque" nature of table_ptr.
	(It's not for the user, it's for the library.  The user doesn't need to know about it.)
	The table_ptr member can be destroyed and remade larger or even realloc()d without the user knowing.
	Also, discuss the function comment block for create_hash_table() at length (with regards to resizing).

----

Summary
========================================

* "Any data type"
* Data Structure Bookkeeping
* Hash Function
* Mitigating Hash Collisions
* Resizing
* Resources
* Student Labs

.. note::

	Last chance to cover student questions.

----

Objectives
========================================

* 8-04-1:   Creating a hash table with n number of items
* 8-04-1:   Navigating through a hash table to find the nth item
* 8-04-1:   Finding an item in a hash table
* 8-04-1:   Removing selected items from a hash table
* 8-04-1:   Inserting an item into a hash table
* 8-04-2/3: Implement functionality to mitigate hash collisions within the hash table
* 8-04-1:   Removing all items from the hash table

.. note::

	This slide is presented as a lookup table of lab-to-objective
