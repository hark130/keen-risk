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
* Cross-Compilation
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
=========================

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
=========================

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

RESOURCES
========================================

* GNU Compiler Collection (GCC) Online Manuals: https://gcc.gnu.org/onlinedocs/
* GCC Man Page: https://man7.org/linux/man-pages/man1/gcc.1.html
* 39 IOS IDF Course Material: https://39ios-idf.90cos.cdl.af.mil/4_c_module/08_c_compiler/index.html

.. note::

	It seems like every other safe-for-work webpage describes the C Programming compilation stages: https://lmgtfy.app/?q=c+programming+compilation+stages

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
