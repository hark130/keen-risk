:title: C Programming - Data Structures - Linked List
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
8.2 Demonstrate skill in creating and using a circularly linked list that accepts any data type

----

8.2 Demonstrate skill in creating and using a circularly linked list that accepts any data type
===============================================================================================

----

Objectives
========================================

* Removing selected items from the circularly linked list
* Creating a circularly linked list with n number of items
* Navigating through a circularly linked list
* Finding the first occurrence of an item in a circularly linked list
* Sorting the circularly linked list alphanumerically using a function pointer
* Destroying a circularly linked list
* Inserting an item into a specific location in a circularly linked list
* Removing all items from the circularly linked list

.. note::

	I intend to accomplish these objectives in incremental stages.

----

Overview
========================================

* "Any data type"
* Data Structure Bookkeeping
* Sorting
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

	Whomever wrote the "any data type" objective hates students or they meant "discrete data type".
	You store "any data type" by saving the raw data, the original data type, and the size of that data in memory.
	Another solution would be to use a Union but you'd still have to store the original data type.
	Walk them through a couple examples.

----

Data Structure Bookkeeping
========================================

At a minimum, someone must hold the head node.

.. code:: c

	typedef struct _list_node
	{
	    // Data
	    any_data_ptr data_ptr;
	    // Next node
	    struct _list_node *next_ptr;
	} list_node, *list_node_ptr;	

.. note::

	You could just operate on a list_node_ptr without doing any data structure bookkeeping.
	Bookkeeping can save you some time though.

----

Data Structure Bookkeeping
========================================

A layer of abstraction allows for bookkeeping

Bookkeeping can help improve performance

.. code:: c

	typedef struct _linked_list
	{
	    // Head node
	    list_node_ptr head_ptr;
	    // Tail node
	    list_node_ptr tail_ptr;
	    // Number of entries
	    unsigned int entries;
	} linked_list, *linked_list_ptr;

.. note::

	You could just operate on a list_node_ptr without doing any data structure bookkeeping.
	Bookkeeping can save you some time though.
	For instance, keeping track of the number of linked list entries will make validating insertion/seeking easier.
	Also, keeping track of the tail node will make appending new nodes O(1) instead of O(n).

----

Sorting
========================================

* Generic Process
* Sorting Algorithms
* Modular Sorting

.. note::

	This "sorting" section is purposely short.  This isn't 8-02: Sorting.  This is 8-02: Linked Lists.
	It's only here because there's one objective that requires sorting.

----

Sorting - Process
========================================

* Generic Process
	1. Gather the input
	2. Sort it
	3. Put it back

.. note::

	1. Sometimes the input is already gathered.  Sometimes it's best to put the input into an array.  That way, the sorting implementation works regardless of the original data structure format.
	2. There are numerous sorting algorithms, each with their own strengths and weaknesses.
	3. Sometimes the data can be sorted in-place but if you gathered the input into an array then you'll need to put it back into its original format.

----

:class: split-table

Sorting - Algorithms
========================================

Common Sorting Algorithms

+---------------+---------------+-------------+
| **Algorithm** |    **PRO**    | **Time**    |
+---------------+---------------+-------------+
| Bubble        | Simplest      | Slowest     |
+---------------+---------------+-------------+
| Insertion     | Almost sorted | Slow        |
+---------------+---------------+-------------+
| Quick         | Most common   | Fast        |
+---------------+---------------+-------------+
| Merge         | Worst == Best | Fastest     |
+---------------+---------------+-------------+

.. note::

	Bubble sort touches all permutations of all elements while sorting.  "Worst case" == "Best case" time complexity: O(n^2).

	Insertion sort is a good choice when the array is nearly sorted

	Quick sort (AKA partition sort) is a divide-and-conquer algorithm

	Merge sort's "worst case" time complexity is the same as its "best case": O(nlogn).

	SOURCE: https://www.geeksforgeeks.org/sorting-algorithms/#
	        https://builtin.com/machine-learning/fastest-sorting-algorithm

----

:class: center-image

Sorting - Algorithms
========================================

.. image:: images/08-02_001_01-Linux-qsort-cropped.png

.. note::

	The Linux API implements a quick sort alogrithm.

	man qsort

----

Sorting - Modular
========================================

Modular Sorting

.. code:: c

	/* Should they be swapped? */
	int compare(char *left, char *right);

	/* Swaps two array v indices */
	void swap(char *v[], int i, int j);

	/* Implements quick sort */
	void qsort(char *v[], int left, int right);

.. note::

	The trick here is that the quick sort function utilizes both compare and swap under-the-hood.
	This modular programming technique is a best practice.  It makes updates/changes/support/testing easier.
	This modular technique can be extended by adding a "compare" function pointer to the sorting algorithm function declaration.

	SIDE NOTE: Why does the qsort() function take left/right indices as parameters?  To facilitate recursive function calls.
	Quick sort (AKA partition sort) is a divide-and-conquer algorithm.

	SOURCE: The C Programming Language 5.6

----

Resources
========================================

* Linked Lists:
	* Data Structures and Algorithms Made Easy Ch. 3
* Sorting:
	* https://www.geeksforgeeks.org/sorting-algorithms/#
	* https://builtin.com/machine-learning/fastest-sorting-algorithm
	* The C Programming Language 5.6

----

STUDENT LABS
========================================

All labs will utilize the 8-02-circular_list "library".
Each lab has unit tests available to validate your work.
Be sure to use ASAN and Valgrind.

* 8-02-1: Minimum functionality: append data, delete list
* 8-02-2: Basic functionality: count nodes, find node (pos), insert data (pos), remove node (pos)
* 8-02-3: More functionality: find node (value), sort list

General Files:
	* 8-02-circular_list.h - Defines the circularly linked list interface
	* 8-02-circular_list-lab.c - Implments the circularly linked list
	* 8-02-sort_functions.h - Declares sorting functions
	* 8-02-sort_functions.c - Implments sorting functions

.. note::

	These files will be used throughout all three labs
	The labs represent crawl-walk-run milestones while implementing a circularly linked list
	Files
	The interface is already designed in 8-02-circular_list.h (wait for applause/thanks)
	It's important to note that 8-02-circular_list-lab.c is the single most important file in the list.  It's where the students do all their work.
	The 8-02-sort_functions library already defines sorting algorithms to use in the labs (wait for applause/thanks)

----

STUDENT LABS
========================================

8-04-1: PLACEHOLDER

Key Files:
	* 8-04-1-hash_table-main.c - Unit tests for basic functionality

Suggested implementation order:
	1. create_hash_table()
	2. destroy_table()
	3. find_value()
	4. add_key()
	5. delete_key()
	6. delete_all_keys()

CONSIDER THIS THE HINT OF THE CENTURY:

.. code:: c

	typedef struct _circular_list
	{
	    // Linked list head node
	    circular_node_ptr head_ptr;
	    // Linked list tail node
	    circular_node_ptr tail_ptr;
	    // Number of entries
	    unsigned int entries;
	} circular_list, *circular_list_ptr;

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

8-04-2: PLACEHOLDER

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

8-04-3: PLACEHOLDER

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
* Sorting
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
