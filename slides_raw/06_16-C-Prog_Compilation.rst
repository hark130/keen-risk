:title: C Programming - Compilation
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
6.16 Demonstrate skill in compiling, linking, and debugging

----

6.16 Demonstrate skill in compiling, linking, and debugging
===========================================================

----

Objectives
========================================

* Execute a program in a debugger to perform general debugging actions
* Create a program using the compilation and linking process
* Compile position-independent code using a cross-compiler

----

Overview
========================================

* C Compilation Stages
* Debugging
* Position Independent Code (PIC)
* Cross-Compilation
* Cross Compiling PIC
* Resources
* Student Labs

----

C COMPILATION STAGES
========================================

* I remember that!
* But why do we care?
* How can I do it?

----

:class: flex-image center-image

C COMPILATION STAGES
========================================

.. image:: images/06-15_001_01-Compilation_Stages-cropped.png

.. note::

	"I remember that!" (But do they, though?)

	Recap facts and terms from 6-15.
	Discuss the purpose of each phase.
	Name the input and the output.

----

C COMPILATION STAGES
========================================

Why do we care?

* Preprocessing
    * Troubleshooting directives
    * Conditional compilation
    * Expanding system macros
* Compiling
    * Make the compiler write assembly for you
* Assembling
    * Easy to swap out object code
    * Link a binary to different object code builds
    * Save build time by only assembling modified libraries
* Linking
	* Easily swap out static libraries
	* Save build time by linking modified libraries into binaries

.. note::

	AKA "Why do I care how the saugsage is made?"

	Preprocessing:

		- The only real way to troubleshoot misbehaving preprocessor directives is to preprocess them and see what's happening

		- What is the value of INT_MAX on your current system?  printf INT_MAX | gcc -include limits.h -E - | tail -n 1  # Preprocesses a Linux header and prints the value

	Compiling:

		- I've used compilers to help write shell code for me

	Assembling:

		- Swap out a library implementation to diversify your code or change implementation.

		- Sometimes a library needs to be troubleshot.  Assemble that library into a DEBUG-version of object code (insted of the entire project).

		- Build time for complex projects can take minutes.  Cut that time by only assembling the libraries that have changed.

	Linking:

		- So you have DEBUG object code for a library.  Link the other unchanged object code against this new DEBUG-build and save time.

		- Build time for complex projects can take minutes.  Cut that time by linking libraries instead of compiling the entire project each time one statement changes.

----

C COMPILATION STAGES
========================================

\1. Preprocessing

Linux

.. code:: bash

	# Preprocesses foo.c into foo.i
	gcc -E -o foo.i foo.c
	# Preprocesses a Linux header and print the value of a macro
	printf INT_MAX | gcc -include limits.h -E - | tail -n 1

Windows

.. code:: batch

	# As one example...

.. note::

	"How can I do it?"

	<PRESENTER_NOTE>

----

C COMPILATION STAGES
========================================

\2. Compiling

Linux

.. code:: bash

	# gcc -S stops after compilation
	gcc -S -o foo.s foo.c

Windows

.. code:: batch

	# As one example...

.. note::

	<PRESENTER_NOTE>

----

C COMPILATION STAGES
========================================

\3. Assembling

Linux

.. code:: bash

	# gcc -c stops after assembly
	gcc -c -o foo.o foo.c

Windows

.. code:: batch

	# As one example...

.. note::

	<PRESENTER_NOTE>

----

C COMPILATION STAGES
========================================

\4. Linking

Linux

.. code:: bash

	# Just keep doing what you've been doing
	gcc -o hello_world.bin hello_world.c
	# -or-
	# TO DO: DON'T DO NOW... gcc linking command example
	# TO DO: DON'T DO NOW... ld command example

Windows

.. code:: batch

	# As one example...

.. note::

	<PRESENTER_NOTE>

----

DEBUGGING
========================================

Crashing C code with a SEG FAULT is like stubbing your toe in the dark...
It's going to happen if you're not careful.

So you've written bad code.  What do you do now?

1. Debugging Statements
1. (Memory) Debugger
1. (Interactive) Debugger

.. note::

	There aren't good categories to separate, say, GDB and Valgrind.
	We are using Interactive (GDB) and Memory (Valgrind) to help separate the two categories.

	NOTE: These are written in order of precedence (which happens to also be ease-of-use).
	It's a lot easier to find simple errors, like order-of-operations, with debugging statements than it is to go "full ham" in an interactive debugger.
	If you can't find the error with debugging statements and Address Sanitizer (ASAN) is quiet, then it might be time for an interactive debugger. 

----

DEBUGGING
========================================

\1. Debugging statements are a good first step in troubleshooting

Basic Debugging Statement

.. code:: c

	my_func(char *my_string)
	{
		puts("Entered my_func()");  // DEBUGGING
	    char temp_char = 0x0;  // Iterate the string
	    printf("Why am I crashing with %p?!", my_string);  // DEBUGGING
	    temp_char = my_string[0];  // BOOM GOES THE NULL POINTER
	}

Preprocessor Conditional Compilation Magic

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

.. note::

	These two examples represent a range of DEBUGGING statements: basic to advanced(?)

----

:class: split-table

DEBUGGING
========================================

\2. Testing C code with a Memory Debugger is a "best practice"

The C programming language will gladly hand you a loaded weapon to shoot yourself in the foot with.
Memory Debuggers are there to stop you.

C Programming Memory Debuggers

+--------------------------+-------------------------------------------------------------------------------------------+-------------------+
|          NAME            |                                      PROS                                                 |      CONS         |
+--------------------------+-------------------------------------------------------------------------------------------+-------------------+
| Address Sanitizer (ASAN) | FOSS; 75% effective; Instrumented; Detailed output; Easy to use                           |                   |
+--------------------------+-------------------------------------------------------------------------------------------+-------------------+
| Memwatch                 | FOSS; 56% effective; Instrumented; Readable output; Good w/ multi-process & multi-threads |                   |
+--------------------------+-------------------------------------------------------------------------------------------+-------------------+
| Valgrind                 | FOSS; 69% effective                                                                       | Verbose output    |
+--------------------------+-------------------------------------------------------------------------------------------+-------------------+

NOTE: Some memory debuggers find BUGS others don't so consider using more than one.

Effectiveness research documented at: https://github.com/hark130/Mind_Monitor

.. note::

	ASAN: https://github.com/google/sanitizers/wiki/AddressSanitizer
	Memwatch: https://memwatch.sourceforge.net/
	Valgrind: https://valgrind.org/

	Mind Monitor is a project to compare the effectiveness, ease of use, and readability of six memory debuggers.
	See the final ranking here: https://github.com/hark130/Mind_Monitor#final-ranking

----

:class: flex-image center-image

DEBUGGING
========================================

ASAN Example: Someone forgot to call free().

Without ASAN

.. image:: images/06-16_001_01-ASAN_without-cropped.png

With ASAN

.. image:: images/06-16_001_02-ASAN_with-cropped.png

View the bad_code3.c source here: https://github.com/hark130/Mind_Monitor/blob/development/src/bad_code3.c

.. note::

	Highlight for the students that ASAN is accessed using -fsanitize=address -g

	NOTE: An observant student will spot a reference to "gimme_mem_malloc /tmp/test/gimme_mem.c:13" which is not seen in the gcc command.
	It was intentionally cropped out to help focus the attention on the benefits of ASAN.  The full gcc commands were:

	gcc -o bad_code3.bin bad_code3.c gimme_mem.c mimo_wrappers.c

	-and-

	gcc -fsanitize=address -g -o bad_code3_ASAN.bin bad_code3.c gimme_mem.c mimo_wrappers.c

----

:class: split-table

DEBUGGING
=========================

\3. Interactive debuggers allow you to debug code, inspect variables, examine registers, etc during program execution.

C Programming Interactive Debuggers

+---------+----------+----------------------+-------------------+
|  NAME   | PLATFORM |        PROS          |      CONS         |
+---------+----------+----------------------+-------------------+
| GDB     | Most     | FOSS; Customizable   | CLI only          |
+---------+----------+----------------------+-------------------+
| Ghidra  | Most     | FOSS; Easily updated | Uses GDB & WinDbg |
+---------+----------+----------------------+-------------------+
| IDA     | Most     | Free(ish); Standard  | COTS; Expensive   |
+---------+----------+----------------------+-------------------+
| WinDbg  | Windows  | Free                 | COTS              |
+---------+----------+----------------------+-------------------+

.. note::

	NOTE: "Most" == Linux, Windows, and Mac.

	GDB - GNU Debugger: https://www.sourceware.org/gdb/
	Ghidra: https://ghidra-sre.org/
	IDA - Interactive Disassembler: https://hex-rays.com/
	WinDbg - Windows Debugger: https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debugger-download-tools

	FOSS: Free Open Source Software

----

:class: flex-image center-image

DEBUGGING
========================================

.. image:: images/06-16_002_01-GDB_Cheat_Sheet_page_1-cropped.png

.. note::

	Cheat sheet (essentials): https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf

----

:class: flex-image center-image

DEBUGGING
========================================

.. image:: images/06-16_002_02-GDB_Cheat_Sheet_page_2-cropped.png

.. note::

	Cheat sheet (essentials): https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf

----

DEBUGGING
========================================

What is some basic step-by-step GDB usage?

1. gcc -o hello_world.bin hello_world.c -g
2. gdb hello_world.bin
3. break main
4. run
5. next*
6. kill
7. quit

\* Ad infinitum

Tips:

* Use "print" to see values stored in variables.
* Got lost in the source?  Start over with "run".
* Use "step" to enter function calls (but avoid library functions).
* Use "list" to show you source code.
* Use "help <command>" for help with a command.
* The "info" command is very useful:
    * Use "info args" to see the function arguments
    * Use "info locals" to see the current values of local variables.
* GDB accepts truncated commands (e.g., "i b" is equivalent to "info breakpoints")

.. note::

	gcc -o hello_world.bin hello_world.c -g - Don't forget to produce debugging information with -g

	gdb hello_world.bin - Starts GDB with hello_world.bin

	break main - Sets a breakpoint at the main() function

	run - Run the program until it exits, crashes, or hits a breakpoint

	next - Execute the next statement

	kill - Stop the process

	quit - Exit GDB

----

DEBUGGING
========================================

Now harangue your instructor to do it!

* Debugging statements using errno
* ASAN FTW!
* GDB walk-through

.. note::

	Let the students guide you.  Maybe they want to see everything.  Maybe they only want to see GDB.
	Start small.  Expand.  Finish big.  Show them examples of all the commands on the previous slide, at least.

----

<SECTION_3_3>
========================================

* <STUDENTS_SEE_THIS>

.. note::

	<PRESENTER_NOTE>

----

RESOURCES
========================================

* GNU Debugger (GDB)
    * Cheat sheet (essentials): https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf
    * Cheat sheet (long): https://gist.github.com/rkubik/b96c23bd8ed58333de37f2b8cd052c30
* GNU Compiler Collection (GCC) Online Manuals: https://gcc.gnu.org/onlinedocs/
* GCC Man Page: https://man7.org/linux/man-pages/man1/gcc.1.html
* 39 IOS IDF Course Material: https://39ios-idf.90cos.cdl.af.mil/4_c_module/08_c_compiler/index.html

.. note::

	It seems like every other safe-for-work webpage describes the C Programming compilation stages: https://lmgtfy.app/?q=c+programming+compilation+stages

----

STUDENT LABS
========================================

* 6-16-1: Manually walk your source code through the compilation stages and view the results of each stage.
* 6-16-2: What's wrong with the instructor's code?
* 6-16-3: Create a Linux library
* <SECTION_3>

----

STUDENT LABS
========================================

6-16-1 Instructions

* Write some code
* Preprocess it and view the results
* Compile it and view the results
* Assemble it and view the results
* Link it and run it

* 6-16-2: What's wrong with the instructor's code?

----

STUDENT LABS
========================================

6-16-2: What's wrong with the instructor's code?

.. code:: python

	for binary in what_the_instructor_gives_you:
	    does_it_run(binary)
	    what_does_it_do(binary)
	    is_there_something_wrong(binary)
	    write_it_down.append(binary)

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
