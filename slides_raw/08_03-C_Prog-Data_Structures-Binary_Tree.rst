:title: C Programming - Data Structures - Binary Tree
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
8.3 Demonstrate skill in creating and using a binary search tree that accepts any data type

----

8.3 Demonstrate skill in creating and using a binary search tree that accepts any data type
===========================================================================================

----

Objectives
========================================

* Creating a binary search tree with n number of items
* Navigating through a binary search tree
* Locating an item in a binary search tree
* Removing selected items from the binary search tree
* Removing all items from the binary search tree
* Describe implementation strategies for a balanced binary search tree
* Destroying a binary search tree

----

Overview
========================================

* "Any data type"
* Data Structure Bookkeeping
* Binary Tree
* Binary Search Tree
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

	typedef struct _binary_node
	{
	    // Data
	    any_data_ptr data_ptr;
	    // Left node
	    struct _binary_node *left_ptr;
	    // Right node
	    struct _binary_node *right_ptr;
	} binary_node, *binary_node_ptr;	

.. note::

	You could just operate on a binary_node_ptr without doing any data structure bookkeeping.

----

Binary Tree (BT)
============================================

* Operations
* Traversal

----

Binary Tree - Operations
========================================

Common Operations
	* Insert an item
	* Delete an item
	* Search for an item
	* Traverse the tree

.. note::

	Auxiliary Operations: size of the tree, height of the tree, level of the maximum sum, find the least common ancestor (LCA) for a pair of nodes.

----

Binary Tree - Traversal
========================================

Tree Traversal
	* The process of visiting all nodes of a tree
	* Each node is processed once
	* Nodes may be visited more than once
	* The traversal sequence defines a method

.. note::

	The next slide discusses the three traversal methods.

	All the nodes may be visited but searching stops when a "needle" node is found in the "haystack"

----

Binary Tree - Traversal
========================================

Traversal Legend
	* D - Process the current node
	* L - Process the left subtree
	* R - Process the right subtree

Traversal Methods
	* Preorder (DLR)
	* Inorder (LDR)
	* Postorder (LRD)
	* Level Order Traversal

.. note::

	The next slide provide a graphic and examples of the traversal methods.

	SPOILER - A Level Order Traversal transcends "branch" traversal by utilizing a queue to traverse each level.  There may be another type of solution but use of a queue is the most basic.

----

:class: flex-image center-image

Binary Tree - Traversal
========================================

Preorder (DLR) Traversal Method

GRAPHIC PLACEHOLDER

.. image:: images/08-01_004_02-simple_stack-cropped.png

The nodes would be visited in the order: 1 2 4 5 3 6 7

.. note::

	These nodes are displayed in 

	This traversal method makes the most logical sense to me.  However, it may not be the most efficient "traversal method" for a given binary tree use case.

	The non-recursive Preorder traversal method utilizes stacks.  There are other solutions but using a stack is the most basic.

----

:class: flex-image center-image

Binary Tree - Traversal
========================================

Inorder (LDR) Traversal Method

GRAPHIC PLACEHOLDER

.. image:: images/08-01_004_02-simple_stack-cropped.png

The nodes would be visited in the order: 4 2 5 1 6 3 7

.. note::

	This may confuse someone.  "Why not 2 1 3...?"  Because you'll never get back to 4.

	This "traversal method" processes all the lefts, then their parent nodes, and then all the rights.

	It may be even better to think of a "tall" tree as a collection of sub-trees.
	Node 2 is the head node for a sub-tree.  As such, Node 2's "L" is processed before it is.

	The non-recursive Inorder traversal method utilizes stacks.  There are other solutions but using a stack is the most basic.

----

:class: flex-image center-image

Binary Tree - Traversal
========================================

Postorder (LRD) Traversal Method

GRAPHIC PLACEHOLDER

.. image:: images/08-01_004_02-simple_stack-cropped.png

The nodes would be visited in the order: 4 5 2 6 7 3 1

.. note::

	The non-recursive Postorder traversal method utilizes stacks.  There are other solutions but using a stack is the most basic.

----

:class: flex-image center-image

Binary Tree - Traversal
========================================

Level Order Traversal Method

GRAPHIC PLACEHOLDER

.. image:: images/08-01_004_02-simple_stack-cropped.png

The nodes would be visited in the order: 1 2 4 5 3 6 7

.. note::

	This "traversal method" processes levels instead of branches.
	Level order traversal algorithms utilize queues.  There may be another type of solution but use of a queue is the most basic.

----

Binary Tree - Traversal
========================================

Traversal Methods
	* Preorder (DLR)
	* Inorder (LDR)
	* Postorder (LRD)
	* Level Order Traversal

.. note::

	Have the students recap some basic facts about each of these traversal methods.

	Q: Which traversal method will process left-most node at the "depth of the tree" first?  A: Inorder (LDR)

	Q: Which traversal method will process node 2 & 3 (by insertion order) before nodes 4 - 7?  A: Level Order Traversal

	Traversal Legend: D - Process the current node, L - Process the left subtree, R - Process the right subtree

	Recursion rules the day for Preorder, Inorder, and Postorder traversal but these traversal methods require stacks for non-recursive solutions.  Again, there are other non-recursive solutions but stacks are the most basic.

	A queue is commonly used for Level Order traversal.  There may be another type of solution but use of a queue is the most basic.

----

Binary Search Tree (BST)
============================================

* Operations
* Traversal

----

Binary Search Tree - Operations
============================================

----

Binary Search Tree - Traversal
============================================

----

BT vs BST
============================================

* Operations
* Traversal

.. note::

	Have the students list some differences between common operations of BTs and BSTs.

	Have the students list some differences between traversal methods of BTs and BSTs.

----

<SECTION_1_2>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_1_3>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_2>
========================================

----

<SECTION_2_1>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_2_2>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_2_3>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_3>
========================================

----

<SECTION_3_1>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_3_2>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

<SECTION_3_3>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Summary
========================================

* <SECTION_1>
* <SECTION_2>
* <SECTION_3>

----

Objectives
========================================

* <OBJECTIVE_1>
* <OBJECTIVE_2>
* <OBJECTIVE_3>
