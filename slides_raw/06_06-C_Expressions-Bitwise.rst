:title: C Programming - Expressions - Bitwise
:data-transition-duration: 1500
:css: c-prog.css

Bitwise operations in C

----

C Bitwise Expressions and Operators
========================================
* 6.6
* 6.18

----

Objectives
========================================

* Use bitwise operators to create relevant expressions

----

Overview
========================================

* Binary 101
* Signed vs. Unsigned Types
* Bitwise Operators
* Common Uses
* Common Expressions
* Resources
* Student Labs

----

:class: shrink-image center-image

Binary 101
========================================

.. image:: images/06-06_001_01-XKCD_binary_scale-cropped.png

.. note::

	SOURCE: https://xkcd.com/953

----

Binary 101
========================================

+--------------+-----+-----+-----+-----+-----+-----+-----+-----+
| Bit Value    |  0  |  1  |  0  |  1  |  1  |  0  |  1  |  0  |
+--------------+-----+-----+-----+-----+-----+-----+-----+-----+
| Bit Number   |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
+--------------+-----+-----+-----+-----+-----+-----+-----+-----+
| Bit Weight   | 128 | 064 | 032 | 016 | 008 | 004 | 002 | 001 |
+--------------+-----+-----+-----+-----+-----+-----+-----+-----+
| Significance | MSB |     |     |     |     |     |     | LSB |
+--------------+-----+-----+-----+-----+-----+-----+-----+-----+

Least Significant Bit (LSB) - the bit position in a binary value representing the lowest-order place

Most Significant Bit (MSB) - the highest-order bit position of the binary value

.. note::

	Explain to the students that "position" will be used interchangeable with "number"
	MSB has the highest weight, LSB has the lowest weight
	Bit indexing correlates to the positional notation of the value in base 2.
	Have the students do some basic conversions:
	    - Convert 01011010 to decimal
	    - Convert a decimal value to binary
	    - Ask the students how to convert -3 to binary (as a transition to the next slide)

----

Signed vs. Unsigned Types
========================================

* Similarities
* Differences
* Sign Bits
* Storage Methods

----

Signed vs. Unsigned (Similarities)
========================================

* Base data types all have the same sizes
* Base data types all have the same alignment
* Machine language makes no distinction (for most architectures)

.. note::

	Size - Reference `sizeof()`
	Alignment - Big/Little Endian
	Machine Language - It is just data in memory.  Humans infer the context and instructions utilize flags to handle this data differently.

----

Signed vs. Unsigned (Differences)
========================================

* Data types have different value ranges
* The "sign bit" indicates the value's sign
* Only signed types have a "sign bit"

.. note::

	Ranges - An unsigned byte can represent values from 0 to 255, while a signed byte can represent -128 to 127
	Sign - AKA positive or negative

----

Signed vs. Unsigned (Sign Bits)
========================================

* Invariably the most significant bit
* (Mostly) 0 sign bit represents a positive number
* (Mostly) 1 sign bit represents a negative number

.. note::

	I don't have an example of a counter-example but it's not a guarantee

----

Signed vs. Unsigned (Storage Methods)
========================================

* Two's Complement: To negate a number, invert all the bits and add 1.
* One's Complement: To negate a number, invert all the bits.
* Sign-Magnitude: To negate a number, flip the MSB (0 to 1 or 1 to 0).

+------------------+------+------+
| Method           | 0111 | 1001 |
+------------------+------+------+
| Unsigned         | 7    | 9    |
+------------------+------+------+
| Two's Complement | 7    | -7   |
+------------------+------+------+
| One's Complement | 7    | -6   |
+------------------+------+------+
| Sign-Magnitude   | 7    | -1   |
+------------------+------+------+

.. note::

	Two's Complement is by far the most common.
	These positive values match up.
	However, the sign bit changes everything between all of the storage methods.
	Is it important to know which is being used?  Mostly not.

----

Bitwise Operators
========================================

----

:class: split-table shrink-table

Bitwise Operators
========================================

+-------------+--------+
| Operator    | Symbol |
+-------------+--------+
| AND         | &      |
+-------------+--------+
| OR          | \|     |
+-------------+--------+
| XOR         | ^      |
+-------------+--------+
| NOT         | ~      |
+-------------+--------+
| Left Shift  | <<     |
+-------------+--------+
| Right Shift | >>     |
+-------------+--------+

.. note::

	XOR is pronounced "Ecks-Ohr"
	Foot-stomp the fact these are not to be confused with logical operators
	(Make the students describe the different between logical/bitwise AND, OR, and NOT)

----

Bitwise AND
========================================

+-------+-------+-------+
| bit a | bit b | a & b |
+-------+-------+-------+
| 0     | 0     | 0     |
+-------+-------+-------+
| 0     | 1     | 0     |
+-------+-------+-------+
| 1     | 0     | 0     |
+-------+-------+-------+
| 1     | 1     | 1     |
+-------+-------+-------+

.. note::

	Both bits must be "true" for the result to be "true"

----

Bitwise AND
========================================

.. code:: text

	  01001101 01100001 01110010 01101011
	& 01001000 01100001 01110010 01101011
	  -----------------------------------
	  01001000 01100001 01110010 01101011

.. note::

	Walk the students through this bit by bit
	Mark & Hark == Hark

----

Bitwise OR
========================================

+-------+-------+-------+
| bit a | bit b | a | b |
+-------+-------+-------+
| 0     | 0     | 0     |
+-------+-------+-------+
| 0     | 1     | 1     |
+-------+-------+-------+
| 1     | 0     | 1     |
+-------+-------+-------+
| 1     | 1     | 1     |
+-------+-------+-------+

.. note::

	Either bit can be "true" for the result to be "true"

----

Bitwise OR
========================================

.. code:: text

	  01001101 01100001 01110010 01101011
	| 01001000 01100001 01110010 01101011
	  -----------------------------------
	  01001101 01100001 01110010 01101011

.. note::

	Walk the students through this bit by bit
	Mark | Hark == Mark

----

Bitwise XOR
========================================

* AKA Exclusive Or

+-------+-------+-------+
| bit a | bit b | a ^ b |
+-------+-------+-------+
| 0     | 0     | 0     |
+-------+-------+-------+
| 0     | 1     | 1     |
+-------+-------+-------+
| 1     | 0     | 1     |
+-------+-------+-------+
| 1     | 1     | 0     |
+-------+-------+-------+

.. note::

	Only one bit can be "true" for the result to be "true"

----

Bitwise XOR
========================================

.. code:: text

	  01001101 01100001 01110010 01101011
	^ 01001000 01100001 01110010 01101011
	  -----------------------------------
	  00000101 00000000 00000000 00000000

.. note::

	Walk the students through this bit by bit
	Mark | Hark == "\x05\x00\x00\x00"

----

Bitwise NOT
========================================

* AKA The 1's Compliment

+-------+-------+
| bit a | ~a    |
+-------+-------+
| 0     | 1     |
+-------+-------+
| 1     | 0     |
+-------+-------+

.. note::

	This is a unary operator (needing just one operand)
	It has the effect of "flipping" the bit

----

Bitwise NOT
========================================

.. code:: text

	~ 01001101 01100001 01110010 01101011
	  -----------------------------------
	  10110010 10011110 10001101 10010100

.. note::

	Walk the students through this bit by bit
	~Mark == ����

----

Bitwise Left Shift
========================================

The left operand's value is moved left by the number of bits specified by the right operand.

Any blank spaces generated while shifting are filled up by zeroes.

.. code:: text

	01001101 << 2 == 00110100
	01001000 << 3 == 01000000

.. note::

	M << 2 == 4
	H << 3 == @

----

Bitwise Right Shift
========================================

The left operand's value is moved right by the number of bits specified by the right operand.

Unsigned values: Any blank spaces are filled by zeroes.

Signed values: Implementation-defined.

.. code:: c

	unsigned int num1 = 12;  // 00001100
	// num1 >> 2 == 3          (00000011)
	signed int num2 = -8;    // 11111000 (Two's Complement)
	// num2 >> 1 == ?????

.. note::

	This behavior is specific to the C programming language.
	The behavior of other programming languages may differ.
	The method used to right shift a signed value is implementation-defined.
	Do *not* rely on its behavior for portability.
	Circumvent it by replicating the behavior you desire in your own implementation.

----

:class: split-table shrink-table

Bitwise Operators Recap
========================================

+-------------+--------+
| Operator    | Symbol |
+-------------+--------+
| AND         | &      |
+-------------+--------+
| OR          | \|     |
+-------------+--------+
| XOR         | ^      |
+-------------+--------+
| NOT         | ~      |
+-------------+--------+
| Left Shift  | <<     |
+-------------+--------+
| Right Shift | >>     |
+-------------+--------+

.. note::

	Quiz the students on facts

----

Common Uses
========================================

When would I use bitwise operations?

* Flags
* Packing data
* Low-level I/O
* Cryptography

.. note::

	Flags - Each bit is an indicator
	Packing data - Storing more than one pieces of data in a single value
	Low-level I/O - Accessing specific bits in device registers (common in microcontroller programming)
	Cryptography - Makes heavy use of XOR


----

Common Expressions
========================================

What are some common bitwise expressions?

* Test a bit (is it on or off?)
* Turn on a bit
* Turn off a bit

.. note::

	These are the basic building blocks for bitwise expressions

----

Common Expressions
========================================

How do I test a bit?

.. code:: c

	uint8_t bitmask = 1;  // 00000001
	bitmask << 2;         // 00000100
	if (0x9 & bitmask)
		// If true, bit position 2 is set

.. note::

	uint8_t is an unsigned integer type guaranteed to only be 8 bits in size, regardless of implementation or infrastructure
	Have the students tell you if 0x9 & (1 << 2) is true or not
	SPOILERS: It's false because 1001 & 0100 == 0000

----

Common Expressions
========================================

How do I set a bit?

.. code:: c

	uint8_t flags = 0xF0;   // 11110000
	uint8_t mask = 1 << 3;  // 00001000
	flags = flags | mask;   // 11111000

.. note::

	uint8_t is an unsigned integer type guaranteed to only be 8 bits in size, regardless of implementation or infrastructure
	Have the students tell you if 0x9 & (1 << 2) is true or not
	SPOILERS: It's false because 1001 & 0100 == 0000

----

Common Expressions
========================================

How do I clear a bit?

.. code:: c

	uint8_t flags = 0xFF;       // 11111111
	uint8_t mask = 0b00111100;  // 00111100
	mask = ~mask;               // 11000011
	flags = flags & mask;       // 11000011

.. note::

	This is example is doing a bit more.
	The initialization value for the mask variable is a "binary literal", introduced in C23.
	This example is also operating on more than one bit at a time.

----

Resources
========================================

* Bitwise Calculator: https://bitwisecmd.com/
* Bitwise Calculator & Visualizer: https://unsuitable001.github.io/BitViz
* The C Programming Language 2.9
* https://www.programiz.com/c-programming/bitwise-operators

----

Student Labs
========================================

* TO DO: DON'T DO NOW...

.. note::

	TO DO: DON'T DO NOW...

----

Summary
========================================

* Binary 101
* Signed vs. Unsigned Types
* Bitwise Operators
* Common Uses
* Common Expressions
* Resources
* Student Labs

----

Objectives
========================================

* Use bitwise operators to create relevant expressions

----

:class: shrink-image center-image

00000000
========================================

.. image:: images/06-06_002_01-XKCD_binary_heart-cropped.jpg
	:align: center

.. note::

	SOURCE: https://xkcd.com/99
