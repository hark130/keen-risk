:title: C Programming - Data Structures
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
8.1 Describe the concepts and terms associated with key data structures

----

8.1 Describe the concepts and terms associated with key data structures
=======================================================================

----

Objectives
========================================

[Describe the concepts and terms associated with...]

* Circularly linked list
* Hash table
* Weighted graph
* Common pitfalls when using linked lists, trees, and graphs
* The effect of First In First Out (FIFO) and Last In First Out (LIFO)
* Stack
* Tree vs Binary search tree
* Linked list
* Double linked list
* Queue vs Priority Queue

.. note::

	This may be the order the Job Qualification Standard (JQS) line items are presented in but this is *not* the order I'll be teaching them in.

----

Overview
========================================

* Definitions
* Data Structure Types
* Considerations
* Resources

----

Definitions
========================================

* What is a data structure?

.. note::

	Take this opportunity to see what they know before proceeding.

----

Definitions
========================================

What is a data structure?
    * A specialized format to store data
    * Organizes, processes, and retrieves data
    * Format implies relationship
    * Includes operations that can be applied to the data

Where can I get one?
    * Lower level languages tend to lack built-in support
    * Most languages permit data structure implementations as libraries
    * Modern languages support modular programming

.. note::

	The relationship implied by a chosen format could represent: order, priority, metadata, etc.

	By this definition alone, a database is a good example of a data structure.  It has a format.
	It organizes and retrieves data.  A database's primary key implies relationship.

	Programmatically, an array is a data structure they (should) have encountered by now.
	C arrays have a format (data type, length).  They organize data.  The format of the array implies relationship (sequential order).
	There are common operations you can apply to an array.

	Do the students know what modular programming is?  Wikipedia defines it as "a software design technique that emphasizes separating the functionality of a program into independent, interchangeable modules, such that each contains everything necessary to execute only one aspect of the desired functionality." (https://en.wikipedia.org/wiki/Modular_programming)
	Shorthand: "a separation between the interface of a library module and its implementation" (https://en.wikipedia.org/wiki/Data_structure)

	Basically, OS implementations are mostly(?) just well(ish) defined data structures under the hood.

	The real answer to "Where can I get one?" is "Make one."

----

Data Structure Types
========================================

* Linked List
* Queue
* Tree
* Stack
* Hash Table
* Graph

----

Data Structure Types - Linked List
========================================

What is it?
    * Comprised of one or more connected nodes
    * Can store a variable number of nodes
    * Nodes contains data and a reference to the next node
    * Memory efficient
    * Linear storage
    * Easy to change the length

.. note::

	SPOILERS: There are four types of Linked Lists and some of those type contain *more* than just data and the next node.
	This definition is more of a "at least" description.

----

Data Structure Types - Linked List
========================================

Common Operations
    * Traverse the list
    * Insert a node
    * Delete a node
    * Search for a node

Real Examples
    * Commonly used to implement other data structures
    * "The linked list is the simplest and most common data structure in the Linux kernel." (1)
    * Windows internals use a linked list data structure to maintain thread scheduler queues

\(1) Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures P. 86

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Linked List
========================================

Types
	* Linked List
	* Doubly Linked List
	* Circular (Singly) Linked List
	* Circular Doubly Linked List

----

:class: flex-image center-image

Data Structure Types - Linked List
========================================

.. code:: c

	/* An element in a linked list */
	struct list_element {
		void *data;                 // Payload
		struct list_element *next;  // Next node
	};

.. image:: images/08-01_001_01-linked_list-cropped.png

.. note::

	The first node in a linked list is called the "Head" node.
	The last node in a linked list is called the "Tail" node.

	Example questions to ask the students:
	* In a well formed linked list, what is special about the tail node?  (next is NULL)
	* In a well formed linked list, what is special about the head node?  (Nothing)
	* Can a well formed linked list contain just one node?  (Arguably yes, unless you define design restrictions)

	Source: Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures

----

:class: flex-image center-image

Data Structure Types - Linked List
========================================

.. code:: c

	/* An element in a doubly linked list */
	struct list_element {
		void *data;                 // Payload
		struct list_element *next;  // Next node
		struct list_element *prev;  // Previous node
	};

.. image:: images/08-01_001_02-doubly_linked_list-cropped.png

.. note::

	Source: Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures

----

:class: flex-image center-image

Data Structure Types - Linked List
========================================

.. image:: images/08-01_001_03-circular_singly_linked_list-cropped.png

.. note::

	What's changed between this and a (singly) linked list?  The tail node points at the head node.
	In a circular list, head nodes and tail nodes don't implicitly exist.  You can choose to maintain a head node though.
	It's not required though.  If you have one node, you have access to all the nodes.

	Source: Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures

----

:class: flex-image center-image

Data Structure Types - Linked List
========================================

.. image:: images/08-01_001_04-circular_doubly_linked_list-cropped.png

.. note::

	What's changed between this and a doubly linked list?  The tail node points at the head node.
	In a circular list, head nodes and tail nodes don't implicitly exist.  You can choose to maintain a head node though.
	It's not required though.  If you have one node, you have access to all the nodes.

	FUN FACT: The Linux kernel's default linked list implementation is fundamentally a circular doubly linked list.  "Using this type of linked list provides the greatest flexibility."

	Source: Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures

----

Data Structure Types - Queue
========================================

What is it?
    * PLACEHOLDER

.. note::

	PLACEHOLDER

----

Data Structure Types - Queue
========================================

Common Operations
    * Create
    * Enqueue
    * Dequeue
    * Size
    * Reset
    * Destroy

Real Examples
    * PLACEHOLDER

.. note::

	Create - AKA Allocate
	Enqueue - AKA Write
	Dequeue - AKA Read
	Size - How big is that buffer?
	Reset - Jettisons all the contents of the queue
	Destroy - AKA Free

----

Data Structure Types - Tree
========================================

What is it?
    * A hierarchical tree-like structure of data
    * Each vertex (AKA node) has 0 or 1 incoming edges
    * Each vertex has >= 0 outgoing edges

So what's a Binary Tree?
	* Same as a tree except each vertex has at most two outgoing edges
	* Each node has zero, one, or two children

.. note::

	A Binary Tree is a Tree but with more steps.  Those "more steps" provide some logical advantages.

----

Data Structure Types - Tree
========================================

Common Operations
    * PLACEHOLDER

Real Examples
    * PLACEHOLDER

\(1) Linux Kernel Development, Third Edition; Ch 6 Kernel Data Structures P. 86

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Tree
========================================

Types
	* Tree
	* Binary Tree
	* Binary Search Trees
	* Self-Balancing Binary Search Trees
	* Red-Black Trees

.. note::

	The objective stops at Binary Search Tree (BST) but it seems amiss to avoid at least mentioning self-balancing BSTs and Red-Black Trees.

----

Data Structure Types - Tree
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Stack
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Queue
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Graph
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Considerations
========================================

* FIFO vs. LIFO
* I have data.  Which structure type should I use?
* Common Pitfalls

----

Considerations - FIFO vs. LIFO
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Considerations - Which one?
========================================

Use linked lists if...
    * ...you iterate over *all* of your data
    * ...performance is not important
    * ...you're storing a small number of items

Use queues if...
	* ...your code follows a producer/consumer pattern
	* ...you want to use a fixed-size buffer
	* ...you value simple/efficient add/remove functionality

Use a hash table if...
    * ...you think to yourself, "I wish I had a Python dictionary here"

Use a binary search tree if...
    1. You need to store a large amount of data
    2. You need to traverse that data efficiently
    3. Your instructor didn't teach you how to use a red-black tree

.. note::

	Queues work well for inter-process communication (IPC).  Doubly so if the communication is only one-way.

	All things being equal, the simplest solution is the best.  As such, use a linked-list if you're not performing time-critical searches.

----

Considerations - Common Pitfalls
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Resources
========================================

* Linux Kernel Development, Third Edition

.. note::

	This is a good chance to ask the students if they have any questions.

----

Summary
========================================

* Definitions
* Data Structure Types
	* Linked List
	* Queue
	* Tree
	* Stack
	* Hash Table
	* Graph
* Considerations
	* FIFO vs. LIFO
	* I have data.  Which structure type should I use?
	* Common Pitfalls
* Resources

.. note::

	Last chance to cover student questions.

----

Objectives
========================================

Describe the concepts and terms associated with...

* Circularly linked list
* Hash table
* Weighted graph
* Common pitfalls when using linked lists, trees, and graphs
* The effect of First In First Out (FIFO) and Last In First Out (LIFO)
* Stack
* Tree vs Binary search tree
* Linked list
* Double linked list
* Queue vs Priority Queue
