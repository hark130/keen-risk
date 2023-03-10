:title: C Programming - Preprocessor
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
6.19 Demonstrate skill in using the C preprocessor

----

6.19 Demonstrate skill in using the C preprocessor
==================================================

----

Objectives
========================================

* Describe uses for common preprocessor directives
* Integrate common preprocessor directives into C projects

.. note::

	These are Harkjectives.  The CCD Basic JQR does not include objectives for this JQS line item.

----

Overview
========================================

* What?
* Common preprocessor directives
* Preprocessor operators
* Put it all together
* Resources
* Student Labs

----

What is it?
========================================

A preprocessing stage command.

.. note::

	Discuss details and facts about the Preprocessing Stage of C Compilation (see: 6-15 for definitions and 6-16 for performance)

----

Preprocessor Directives
========================================

* File Inclusion
    * include
* Macro Substitution
    * define
    * undef
* Conditionals
    * ifdef
    * ifndef
    * if
    * elif
    * endif

.. note::

	Many of these directives have to be discussed in groups: File Inclusion, Macro Substitution, Conditional Substitution.  The group names are formal.  They are merely a logical association of directives.

----

Preprocessor Directives - File Inclusion
============================================

#include <filename>

* Copies files into your file
* Commonly used to include header files
    * Macros
    * Function declarations
    * Extern variables
* "Included" files often contain their own include directives

.. code:: c

	#include <stdio.h>   // Include "installed" files
	/* The OS knows where to look */

	#include "my_lib.h"  // Include "user defined" file
	/* Starts looking in the local directory */

.. note::

	Use of the <> and "" tells the preprocessor where to search for the file

----

Preprocessor Directives - Macro Substitution
============================================

Define: Establishes a macro name and its replacement text.

#define <name> <replacement text>

* Substitutes text for names
* Commonly used to define:
    * file/library-wide values
    * code blocks

Define Values

.. code:: c

	/* The possibilities for the third argument to `fseek'. */
	/* These values should not be changed.  */
	#define SEEK_SET	0	/* Seek from beginning of file.  */
	#define SEEK_CUR	1	/* Seek from current position.  */
	#define SEEK_END	2	/* Seek from end of file.  */

Define Code Blocks

.. code:: c

	#define MAX(A, B) ((A) > (B) ? (A) : (B))

PRO TIP: Make all macro names UPPER_CASE

.. note::

	The "Define Values" example is a copy/paste from <stdio.h>

	The "Define Code Blocks" example was taken from K&R 4.11.2 Macro Substitution.

----

Preprocessor Directives - Macro Substitution
============================================

Undefine: Removes a macro name, if it exists

#undef name

* Explicitly change a macro value
* Useful for conditional compilation
* Ensure a name is a routine and not a function

.. code:: c

	#undef BUFF_SIZE       // Remove the name so that...
	#define BUFF_SIZE 256  // ...you can give it your own value.

.. note::

	The best use case for undef involves preprocessor conditionals but we haven't gotten there yet.

----

Preprocessor Directives - Conditionals
============================================

Test whether a macro name is defined:

* ifdef - if defined, use this code
* ifndef - if not defined, use this code
* endif - the capstone for all preprocessor conditionals

Conditional Compilation

.. code:: c

	/* End of file character. */
	/* Some things throughout the library rely on this being -1.  */
	#ifndef EOF
	#define EOF (-1)
	#endif

Header Guards

.. code:: c

	#ifndef _STDIO_H
	#define _STDIO_H 1

	/* <snip> */

	#endif /* _STDIO_H */

PRO TIPS:

* Use unique header guard macro names to avoid name collisions with other libraries
* Consider prepending and appending the macro name with underscores "_"
* Consider working the file extension in the macro name (e.g., _H)

.. note::

	"What's a header guard?"  A header guard is a preprocessor directive application that protects against including the same file more than once.

	Both examples are almost complete copy/pastes from stdio.h

----

Preprocessor Directives - Conditionals
============================================

Evaluate constant integer expression

* if - if non-zero, use this code
* elif - otherwise, if non-zero, use this code
* else - otherwise, use this code
* endif - the capstone for all preprocessor conditionals

.. code:: c

	/* First Example */
	#if SYSTEM == SYSV
		#define HDR "sysv.h"
	#elif SYSTEM == BSD
		#define HDR "bsd.h"
	#elif SYSTEM == MSDOS
		#define HDR "msdos.h"
	#else
		#define HDR "default.h"
	#endif
	#include HDR

	/* Second Example */
	/* 64bit arch MACRO */
	#if (defined (__x86_64__) || defined (__arm64__) || defined (__aarch64__))
	#define WORD_SIZE_64 1
	#endif

	/* Third Example */
	#if VERBOSE >= 2
  	printf("trace message");
	#endif

FUN FACT: #ifdef and #ifndef are simple shorthands for #if defined(...) and #if !defined(...), respectively

.. note::

	The first example was transcribed from K&R 4.11.3 Conditional Inclusion

	The second example is from: https://github.com/google/AFL/blob/master/config.h

	The third example is from: https://en.wikipedia.org/wiki/C_preprocessor

----

Preprocessor Operators
========================================

* #
    * "stringification"
    * expands macro replacement text into a quoted string
* ##
    * "token pasting"
    * concatenates arguments during macro expansion

.. code:: c

	#define dprint(expr) printf(#expr " = %g\n", expr)

	#define paste(front, back) front ## back

SPOILER ALERT: There are some "gotchas" when using the stringification preprocessor operator

.. note::

	Both of these examples were taken from K&R 4.11.2 Macro Substitution

----

Put It All Together
========================================

Let's re-evaluate this old chestnut:

.. code:: c

	#ifdef HARKLE_DEBUG
	#define HARKLE_ERROR(header, funcName, msg) do { fprintf(stderr, "<<<ERROR>>> - %s - %s() - %s!\n", \
	                                                         #header, #funcName, #msg); } while (0);
	#define HARKLE_ERRNO(header, funcName, errorNum) if (errorNum) { fprintf(stderr, "<<<ERROR>>> - %s - \
	                                                                         %s() returned errno:\t%s\n", \
	                                                                         #header, #funcName, \
	                                                                         strerror(errorNum)); }
	#define HARKLE_WARNG(header, funcName, msg) do { fprintf(stderr, "¿¿¿WARNING??? - %s - %s() - %s!\n", \
	                                                         #header, #funcName, #msg); } while (0);
	#else
	#define HARKLE_ERROR(header, funcName, msg) ;;;
	#define HARKLE_ERRNO(header, funcName, msg) ;;;
	#define HARKLE_WARNG(header, funcName, msg) ;;;
	#endif  // HARKLE_DEBUG

Let's also look at some real uses of preprocessor directives:

* https://github.com/torvalds/linux/blob/master/include/linux/io.h
* https://www.gnu.org/software/m68hc11/examples/stdio_8h-source.html
* https://github.com/google/AFL/blob/master/config.h

.. note::

	All of these examples have header guards

	The AFL config.h has some good examples of "conditional compilation".  Read: "/* Comment out to disable ..."

	The "Define Code Blocks" example is an example that was used in 6-16

	The "HARKLE" conditional compilation section uses a macro, HARKLE_DEBUG, to control the macro expansion.
	If HARKLE_DEBUG is defined, the macros will output DEBUGGING information.  Otherwise, the macro won't do anything.

----

Resources
========================================

* K&R 4.11 The C Preprocessor - http://cslabcms.nju.edu.cn/problem_solving/images/c/cc/The_C_Programming_Language_%282nd_Edition_Ritchie_Kernighan%29.pdf
* 39 IOS Training - https://39ios-idf.90cos.cdl.af.mil/4_c_module/09_preprocessor/index.html

----

Student Labs
========================================

* Create a C library, complete with header file, that:
    * Contains header guards
    * Includes an option for conditional compilation
    * Defines a value
    * Defines a code block

NOTE: For funsies, explore some C compiler-defined macros: \__FILE__, \__LINE__, \__DATE__, \__TIME__,  \__func__.

----

Summary
========================================

* Preprocessor directive definition
* Common preprocessor directives
* Preprocessor operators
* Put it all together
* Resources
* Student Labs

.. note::

	Ask the class to define a preprocess directive
	Ask the class to list some common preprocessor directives
	Ask the class to list the two preprocessor operators

----

Objectives
========================================

* Describe uses for common preprocessor directives
* Integrate common preprocessor directives into C projects

.. note::

	These are Harkjectives.  The CCD Basic JQR does not include objectives for this JQS line item.
