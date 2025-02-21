:title: C Programming - Input/Output Part 1: Console
:data-transition-duration: 1500
:css: c-prog.css

Introduction to file management through stdout/stdin

----

I/O Part 1
========================================
6.8

----

Objectives
========================================

* Use data streams to provide data input/output with console
* Use functions to write to stdout/stderr
* Use functions to read from stdin

----

Overview
========================================

* Standard Data streams
* Writing to data streams
* Reading from data streams

----

Standard Data Streams
========================================
stdin stdout stderr

----

What are they?
========================================

FIFO data structures available to a program once main is invoked.
* stdin - conventionally used to taking input into the program
* stdout - conventionally used for providing output from a program
* stderr - conventionally used to report errors from a program

.. note::

	We care because:
		printline debugging has its place
		interacting with file descriptors is groundwork of file management

----

Writing to data streams - Characters
========================================

.. code:: c

	int putchar(int c); // putc(c, stdout);
	int putc(int c, FILE *stream); //fputc(c, stream);
	int fputc(int c, FILE *stream);

.. note:: 

	Pull up documentation, show how to read/interpret

----

Writing to data streams - Strings
========================================

.. code:: c

	int puts(const char *s); //fputs(s, stdout);
	int fputs(const char *s, FILE *stream);

.. note:: 

	Pull up documentation, show how to read/interpret

----

Writing to data streams - Format Strings
========================================

.. code:: c

	int printf(const char *format, ...);
	int fprintf(FILE *stream, const char *format, ...);
	int dprintf(int fd, const char *format, ...);
	int vprintf(const char *format, va_list ap);
	int vfprintf(FILE *stream, const char *format, va_list ap);
	int vdprintf(int fd, const char *format, va_list ap);
	
.. note:: 

	Pull up documentation, show how to read/interpret

----

Reading from data streams - Characters
========================================

.. code:: c

	int getchar(void); // getc(stdin);
	int getc(FILE *stream); //fgetc(stream);
	int fgetc(FILE *stream);

.. note:: 

	Pull up documentation, show how to read/interpret

----

Reading from data streams - Strings
========================================

.. code:: c

	int gets(const char *s); //Deprecated
	int fgets(char *s, int size, FILE *stream);

.. note:: 

	Pull up documentation, show how to read/interpret

----

Reading from data streams - Format Strings
==========================================

.. code:: c

	int scanf(const char *format, ...);
	int fscanf(FILE *stream, const char *format, ...);
	int vscanf(const char *format, va_list ap);
	int vfscanf(FILE *stream, const char *format, va_list ap);
	
.. note:: 

	Pull up documentation, show how to read/interpret

----

Lab
========================================

wk1/hello_world.c

Practice reading/writing to standard streams

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
