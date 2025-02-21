:title: C Programming - Expressions
:data-transition-duration: 1500
:css: c-prog.css

Introduction to expressions in C

----

C Expressions and Operators
========================================
6.6, 6.18

----

Objectives
========================================

* Use operators to create relevant expressions
* Understand operator precedence

----

Overview
========================================

* Arithmetic Operators
* Relational Operators
* Logical Operators
* Bitwise Operators
* Assignment Operators
* Operator Precedence

----

Punctuator, Identifier, Expression
========================================
Operand, Operator

.. note::

	Term check
	Punctuator = Characters with *special meaning* to a C compiler.
	Identifier = Names/aliases you provide
	Expression = Sequence of operators and operands that compute a value, designate an object or function, and/or generate side effects.
	Expressions in () become operands
	Operand = what operation is done on
	Operator = context for what operation should be done

----

Arithmetic Operators
========================================

\+ ++ - -- * / % >> <<

.. note:: 
	Used to operate/work on operands to change value
	Unary works on one operand
	Binary works on 2 operands

----

Relational Operators
========================================

== > >= < <= !=

.. note::

	Used to compare two operands

----

Logical Operators
========================================

&& || !

.. note::

	Boolean logic used to combine operands

----

Bitwise Operators
========================================

& | ~ ^ >> <<

.. note::

	Boolean logic to combine bits from two operands
	Special note on logical vs arithmetic right shift


----

Assignment Operators
========================================

.. code:: c

	= += -= *= /= %= &= |= ^=

.. note::

	Used to assign expression result to identifier
	Value on right is assigned to identifier on left

----

Other Operators
=========================

?: ; (data_type) & * sizeof ,

.. note::

	Ternary Operator for shorthand if/else

----

Operator Precedence != PEMDAS
========================================

Because punctuators are overloaded, their evaluation is context dependent, but does have a defined precedence order.
Using parenthesis for grouping is part of precedence 1

.. note::

	https://en.cppreference.com/w/c/language/operator_precedence

----

Lab
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
