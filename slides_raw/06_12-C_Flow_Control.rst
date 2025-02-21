:title: C Programming - Flow Control
:data-transition-duration: 1500
:css: keri.css

Overview of flow control in C

----

Flow Control
========================================
6.10, 6.12

----

Objectives
========================================

* Perform data validation
* Use flow control statements in C

----

Overview
========================================

* Conditional Statements
* Loops
* Other Jumps

----

Conditional Statements
========================================
if, else, else if, switch

----

if
========================================

.. code:: C

	if(expression)
		// Do This
	if(expression)
	{
		// Do This
		// And This
	}
	if(0 != expression)
		// Do This

----

else
========================================

.. code:: c

	if(expression)
		// Do This
	else
		// Do this other thing

----

if else if
========================================

.. code:: c

	if (expression1)
	{
		// Do This
		// And this
	}
	else if (expression2)
		// Do this
	else
	{
		// Do this
		// And this
	}

----

switch
========================================

.. code:: c

	switch (expression)
    {
    case value1:
        // Do This
		// And This
        break;
	case value2:
		// Do This
		break;    
    default:
		// Do This
        break;
    }

----

loops
========================================
for, while, do-while

----

for
=========================

.. code:: c

	for(initialization; expression; updation)
	{
		// Do this
	}

----

do
========================================

.. code:: c

	while(expression)
	{
		// Do this
	}

----

do-while
========================================

.. code:: c

	do
	{
		// Do this
	}while (expression)

----

Other jumps
========================================
break, continue, goto

----

break
=========================

* Exit loop/switch statement
* Only exit one level

.. code:: c

	int i;
	for(i = 0; i < 10; i++)
	{
		if(i > 0)
			break;
		printf("i: %d\n", i);
	}
	printf("i: %d\n", i);

----

continue
========================================

* Resets to beginning of loop statement

.. code:: c

	int i;
	for(i = 0; i < 10; i++)
	{
		if(i > 0)
			continue;
		printf("i: %d\n", i);
	}
	printf("i: %d\n", i);

----

goto
========================================

* unconditional jump

.. code:: c

	int i;
	pre_loop:
	for(i = 0; i < 10; i++)
	{
		if(i > 0)
			goto post_loop;
		else
			goto pre_loop;
		printf("i: %d\n", i);
	}
	post_loop:
	printf("i: %d\n", i);

----

Summary
========================================

* Conditional Statements
* Loops
* Other Jumps
