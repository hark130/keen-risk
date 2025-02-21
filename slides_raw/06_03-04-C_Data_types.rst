:title: C Programming - Data Types
:data-transition-duration: 1500
:css: c-prog.css

Introduction to data types in C

----

Data Types
========================================
* 6.3
* 6.4

----

Objectives
========================================

* Identify variable types and their sizes
* Understand variable declaration and initialization

----

Overview
========================================

* Primitive/Standard data types
* User defined data types
* Variable declaration

----

Variable Types
========================================

C is a strongly typed language.
Data types are keywords that provide necessary information to interpret regions of memory.

.. note::

	Why it matters coming after type definitions

----

Standard types
=========================

Types supported by the standard library in C.
They are recognized across all compilers/systems; however, may compile differently.

----

:class: split-table

Void
=========================

+------+------+--------+
| Type | Size | Values |
+------+------+--------+
| void | N/A  | N/A    |
+------+------+--------+

----

:class: split-table

Characters
=========================

+---------------+--------+-------------------------+
|  Type         |  Size  |  Values                 |
+---------------+--------+-------------------------+
| char          | 1 byte | -128 to 127 or 0 to 255 |
+---------------+--------+-------------------------+
| unsigned char | 1 byte | 0 to 255                |
+---------------+--------+-------------------------+
| signed char   | 1 byte | -128 to 127             |
+---------------+--------+-------------------------+


----

:class: split-table shrink-table

Integers
=========================

+----------------+--------------+---------------------------+
| Type           |  Size        |  Values                   |
+----------------+--------------+---------------------------+
| short          | 2            | -32,768 to 32,767         |
+----------------+--------------+---------------------------+
| unsigned short | 2            | 0 to 65,535               |
+----------------+--------------+---------------------------+
| int            | 2 or 4 bytes | -(2^(n-1)) to (2^(n-1))-1 |
+----------------+--------------+---------------------------+
| unsigned int   | 2 or 4 bytes | 0 to (2^n)-1              |
+----------------+--------------+---------------------------+
| long           | 4 or 8 bytes | 0 to (2^n)-1              |
+----------------+--------------+---------------------------+
| unsigned long  | 4 or 8 bytes | 0 to (2^n)-1              |
+----------------+--------------+---------------------------+

----

:class: split-table

Floating Point
=========================
+-------------+----------+------------------------+
| Type        |  Size    |  Values                |
+-------------+----------+------------------------+
| float       | 4 bytes  | 1.2E-38 to 3.4E+38     |
+-------------+----------+------------------------+
| double      | 8 bytes  | 2.3E-308 to 1.7E+308   |
+-------------+----------+------------------------+
| long double | 16 bytes | 3.4E-4932 to 1.1E+4932 |
+-------------+----------+------------------------+

----

Derived Types
========================================

+---------+-----------------------------------------+------------------+
| Type    |  Size                                   |  Values          |
+---------+-----------------------------------------+------------------+
| Arrays  | sizeof(primitive) * number_of_elements  |  primitive value |
+---------+-----------------------------------------+------------------+
| Pointer | long                                    | 0 to MAX_LONG    |
+---------+-----------------------------------------+------------------+

----

User Defined Types
========================================

Types defined by Kernels/Operating Systems, additional libraries, or by you 
through the use of *typedef*

----

Defining Types
=========================

keyword typdef will alias data types to new names

.. code:: c

    typedef existing_type alias;

.. note::

	provides a way to abstract data types for different implementations 

----

Common typedefs
=========================

bool:
 + stdbool.h
fixed-width Integers:
 + stdint.h
size_t:
 + compiler
<identifier>_t:
 + common naming conventions for typedefs

.. note::

	provides a way to abstract data types for different implementations 

----

Structures 
========================================

Way to group items of different types together

.. code:: c

	struct person
	{
		int employee_id;
		char first_initial;
		int team_id;
	};

.. note::

	Cover more later

----

Union
========================================

Way to use one region of memory for different kinds of data

.. code:: c

	union number
	{
		int integer;
		float decimal;
	};

.. note::

	Cover more later

----

Enum
========================================

Way to assign names to integer values

.. code:: c

	enum _RETURN_CODES
	{
		IDF_SUCCESS = 0,
		IDF_TASK_FAILED,
		IDF_INVALID_INPUT
	};

.. note::

	Cover more later

----

Data size
========================================

Identifier's tell your program where to start reading.
Types, a.k.a size, tell your program how many bytes to read.

----

sizeof()
========================================

Identifies the size of data type, identifier, or expression

.. note::

	Common pitfall using on 'unexpected' data type (pointer vs array, etc...)

----

Declaring variables
========================================

----

Initialization
=========================

Setting a region of memory to specific value when it is reserved for use.

.. code:: c

	int x; // variable is defined; however value is unknown
	int y = 0; //variable is defined and initialized to 0

.. note::

	ALWAYS

----

Scope
========================================

Identifiers are recognized by code after it's declaration,
and within the same statement or any nested statements

----

Type Conversion
========================================

Allows you to interpret region of memory as separate type.
Commonly used to simplify expressions, allow easier traversal

.. code:: c

	(data_type) expression

.. note::

	<PRESENTER_NOTE>

----

Summary
========================================

* Why data types are important in C
* Primitive/Standard data types
* User defined data types
* Variable declaration

----

Objectives
========================================

* Identify variable types and their sizes
* Understand variable declaration and initialization
