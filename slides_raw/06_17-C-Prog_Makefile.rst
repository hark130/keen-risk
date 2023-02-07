:title: C Programming - Makefiles
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
6.17 Demonstrate the ability to build a binary from multiple C source files and headers by writing a Makefile using explicit rules

----

6.17 Makefiles
========================================

----

Objectives
========================================

* Demonstrate the ability to build a binary from multiple C source files and headers by writing a Makefile using explicit rules

----

Overview
========================================

* make what?
* make why?
* make how?
* Common Pitfalls
* Resources

----

make what?
========================================

* Description
* Key Terms
* Basic Examples

----

Make Description
========================================

* A tool which controls the generation of executables and other non-source files of a program from the program's source files.
* "Generation" is controlled by one or more Makefiles.
* GNU Make features:
    * Build/install without knowing how
    * Build only what you need
    * Language independent
    * Can do more than just build

Source: https://www.gnu.org/software/make/ 

.. note::

	FULL DEFINITION: GNU Make is a tool which controls the generation of executables and other non-source files of a program from the program's source files. 

	ANALOGY: Liken "make" to a compiler and "Makefiles" to source files.

	GNU: "GNU's Not Unix" is a completely free operating system, upwards compatible with Unix.  See - https://www.gnu.org/

----

Key Terms
========================================

* *rule* - One or more commands needed to generate a target
* *target* - A "thing" to generate
* *dependencies* - A list of zero or more pre-requisites to generate a target

Here is what a simple rule looks like:

.. code:: makefile

	target:   dependencies ...
              commands
              ...

.. note::

	<PRESENTER_NOTE>

----

:class: center-image

Basic Examples
========================================

Example 1: Basic Rule

Makefile

.. image:: images/06-17_001_01-Basic_Makefile-cropped.png

Usage

.. image:: images/06-17_001_02-Basic_Makefile_execution-cropped.png

.. note::

	Makefile targets don't *have* to reference files

----

:class: center-image

Basic Examples
========================================

Example 2: Simple Rule

Makefile

.. image:: images/06-17_002_01-Simple_Makefile-cropped.jpg

Usage

.. image:: images/06-17_002_02-Simple_Makefile_execution-cropped.jpg

.. note::

	This is a more realistic example since it's actually compiling as "generation"

----

make why?
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

COMMON PITFALLS
=========================

* Using spaces instead of tabs
* Trying to mix Make "code" with shell "code"
* Misleading error output
    * "missing rule" message when it should be "missing dependency"

.. note::

	"Misleading error output" example: If a target is missing dependency and there's no rule to *make* that dependency, the error will be "No rule to make target" instead of something like "target yadda is missing dependency yaddayadda and there's not rule to make yaddayadda".

----

RESOURCES
=========================

* GNU Make homepage: https://www.gnu.org/software/make/

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
