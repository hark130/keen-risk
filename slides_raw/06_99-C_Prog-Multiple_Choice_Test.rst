:title: C Programming - Knowledge Test
:data-transition-duration: 1500
:css: keri.css

CCD Basic JQR v1.0
6.2, 6.15, 6.16, 6.17, 6.19, 6.21 Related Questions

----

Multiple Guess Test
========================================

----

\1. What is the purpose the C library function calloc?

\A. allocates memory and sets allocated memory to zero

\B. allocates memory and sets allocated memory to NULL

\C. allocates memory but does not modify the memory

\D. captures allocated memory created by the malloc function

.. note::

	\A.

	The C library function void \*calloc(size_t nitems, size_t size) allocates the requested memory and returns a pointer to it. The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero.

----

\2. What is the result of this C code snippet?

.. code:: c

    1011 | 0010

\A. 1011

\B. 0011

\C. 0010

\D. 1001

.. note::

	\A.

	Binary OR Operator retains a bit if it exists in either operand in that position.

----

\3. Given the C code snippet, where is the memory being allocated with the malloc command?

.. code:: c

    int x [10];
    int *y = malloc(sizeof(x));

\A. cache

\B. heap

\C. registers

\D. stack

.. note::

	\B.

	All memory created with malloc is allocated on the heap.

----

\4. Given the C code snippet, where is the value of x being stored?

.. code:: c
	
	int main(void)
	{
		int x = 90;
		/* snip */
		return x;
	}
	

\A. cache

\B. heap

\C. registers

\D. stack

.. note::

	\D.

----

\5. How do you prevent multiple dependencies from causing compilation errors?

\A. Only #include source files

\B. #include will overwrite the previous #include if they are the same file.

\C. Use the preprocessor directives #ifndef, #define, and #endif to check if a header file was already included

\D. Only one file can be #include into a file.

.. note::

	\C.

	You should use include guards in your header files to stop the declarations from running if they were declared already.

----

\6. To utilize a header file like stdio.h in C programming, you use the __________ preprocessor directive.

\A. #define

\B. #using

\C. #import

\D. #include

.. note::

	\D.

    Incorrect: although #define is a valid preprocessor directive, it is not used to utilize header files. this is used to define named constants

    Incorrect: #using is not a valid preprocessor directive

    Incorrect: #import is not a valid preprocessor directive in C

    Correct: #include allows you to utilize standard C library headers as well as locally defined header files

----

\7. Which of the following C Compilation stages takes assembly as an input and produces object code?

\A. Preprocessing

\B. Compilation

\C. Assembling

\D. Linking

.. note::

	\C.

----

\8. Which of the following is an example of a recursive variable in GNU Make?

\A. #define VAR_A "choice A"

\B. VAR_B = "choice B"

\C. VAR_C := "choice C"

\D. export VAR_D="choice D"

.. note::

	\B.

----

\9. Which binary section is also a writeable region of memory?

\A. .text

\B. .rodata

\C. .rdata

\D. .data

.. note::

	\D.

----

\10. Which memory region is managed by C programmers?

\A. heap

\B. stack

\C. Both A && B

\D. None of the above

.. note::

	\A.

----

BONUS QUESTION

Which of the following is *NOT* a technique to reduce dynamic memory BUGs?

\A. Always Be Checking

\B. Establish a clear ownership model

\C. Use memory debuggers

\D. Let pointer variables go out of scope

.. note::

	\D.

----

STUDENT LABS
========================================

6-99 Instructions

Define this function with as many of the listed features as possible.

.. code:: c

	/*
	 *	@brief Split a long string of letters into a new string of separate words.
	 *
	 * 	@param str - A C-string that contain no spaces
	 *	@return A heap-allocated char pointer with spaces in between each word with only
	 *          the first word capitalized
	 *	@note 
	 *		- Capital letters in the string of characters represents a start of a word.
	 * 		- The string returned should be a newly allocated array.
	 *	@example
	 *		- ILikeCheese   should result in:  I like cheese
	 *		- WhereAreYou   should result in:  Where are you
	 */
	char *makeSentence(const char *str);

* Software library
* Shared library
* Header guards
* Macros
* ABCs
* Memory Debugging (e.g., Valgrind, ASAN)
* Makefile
* Build by linking object code

.. note::

	Ensure the Valgrind BUG is temporary.
