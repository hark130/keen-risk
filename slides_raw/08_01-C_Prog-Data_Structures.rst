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
* Binary Tree
* Stack
* Queue
* Graph

----

Data Structure Types - Linked Lists
========================================

What is it?
    * Comprised of one or more nodes
    * Can store a variable number of nodes
    * Nodes contains data and a reference to the next node
    * Memory efficient
    * Linear storage
    * Easy to change the length

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Linked Lists
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


Data Structure Types - Linked Lists
========================================

Types
    * Linked List
    * Doubly Linked List
    * Circular (Singly) Linked List
    * Circular Doubly Linked List

.. note::

	<PRESENTER_NOTE>

----

Data Structure Types - Binary Tree
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

* Common Pitfalls
* FIFO vs. LIFO

----

Considerations - Common Pitfalls
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Considerations - FIFO vs. LIFO
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

Summary
========================================

* Definitions
* Data Structure Types
* Considerations

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
