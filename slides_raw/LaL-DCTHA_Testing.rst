.. role:: sup
   :class: superscript

:title: DCTHA Testing Lunch-and-Learn
:data-transition-duration: 1500
:css: keri.css

Dev Crew Team Happy Aku (DCTHA) Testing Lunch-and-Learn
20250828

----

Dev Crew Team Happy Aku (DCTHA) Testing
=======================================

----

Outline
==========

* Intro
* Vocabulary
* Our Workflow
* NEBS
* References

----

Intro
=================

* Who am I?
* Why am I talking?
* What am I talking about?

.. note::

    1. DCTHA Tech Lead (and defacto dime store TE/TAE)
    2. Someone (Sam Birch?) asked us to.
    3. DCTHA-approach to testing (OS/Language agnostic)

    TRANSITION: My examples may be agnostic to OS and programming language but we need to all be using the same vocabulary.

----

Vocabulary
=================

Testing "Levels":
  + **Unit Test** - Test a function/method
  + **Component Test** - A test level that focuses on individual hardware or software components\ :sup:`1`
  + **System Test** - A test level that focuses on verifying that a system as a whole meets specified requirements\ :sup:`1`

.. note::

    Sam Birch has identified a departure in verbiage between ISTQB and the DoD, which makes this glossary of definitions even more important for this brief.

    Unit Test definition; my words, not ISTQB
    Component Test; DCTHA uses "Functional Test" as a synonym (but ISTQB disagrees)
    System Test; DCTHA uses "End-to-end test" as a synonym

    TRANSITION: If a component test is NOT a functional test, then what is a functional test?

    See References slide for subscripts

----

Vocabulary
=================

Testing Types:
  + **Functional Test** - Testing performed to evaluate if a component or system satisfies functional requirements\ :sup:`1`
  + **Non-Functional Test** - Testing performed to evaluate that a component or system complies with non-functional requirements\ :sup:`1`
  + **White Box Test** - Testing based on an analysis of the internal structure of the component or system\ :sup:`1`
  + **Black Box Test** - Testing based on an analysis of the specification of the component or system\ :sup:`1`

.. note::

    It's important to note that these testing types are in exclusive pairs: func vs. non-func and white vs. black.

    Functional Test; Does it work?  E.g., Does it grind meat?
    Non-Functional Test; Does it work the right way?  E.g., BUG-free, non-attributable
    White Box Test; Was something instrumented into the code for a test?  E.g., ASAN.
    Black Box Test; No code, just artifacts.  E.g., Operational Acceptance testing.

    TRANSITION: Now that we're all using the same vocabulary, let's discuss DCTHA's general workflow.

    See References slide for subscripts

----

DCTHA Workflow
=================

* Requirement
* Production Code Design\ :sup:`*`
* Testing Design\ :sup:`*`
* Per-Component Testing...
* System Testing...

:sup:`*` Collaborative team meeting

.. note::

    So there we are.  All sitting in a room.  What are we talking about?
    We actually have a series of discussions/meetings.
    Most of the time, one developer takes the lead: research, documentation, leads a team discussion, documents discussions, adds necessary backlog tickets.

    Testing Design, for DCTHA, normally results in a combination of component and system testing.  Unit testing is optional, but I assert we unit test any cryptography utilization (e.g., the formation of a cipher blob, encryption, decryption).

    It's important to note that these bullets are just about in chronological order.
    Most important, T.C. Design --> T.C. Ticket --> Prod Code Ticket.

    TRANSITION: Design is all fine and good but somebody has to write it all.

----

DCTHA Workflow
=================

<snip>

Per-Component Testing

* Test Case Design\ :sup:`†`
* Test Case Implementation\ :sup:`‡`
* Production Code\ :sup:`‡`

<snip>

:sup:`†` One team member leads a team meeting

:sup:`‡` Dedicated backlog ticket

.. note::

    One developer takes the lead: research, documentation, leads a team discussion, documents discussions, adds necessary backlog tickets.

    Then, ticket(s) to implement test frameworks and test cases are completed.

    Then, the Production Code ticket makes the test cases pass.

    TRANSITION: Component testing is fine and good, but what about that Requirements Traceability Matrix and it's Functional Requirements?

    See References slide for subscripts

----

DCTHA Workflow
=================

<snip>

System Testing

* Test Case Design\ :sup:`‡¶`
* Test Case Implementation\ :sup:`‡¶`
* ORE Testing\ :sup:`‡`

:sup:`‡` Dedicated backlog ticket

:sup:`¶` Product Manager involved

.. note::

    System testing becomes easier.  The design is complete.  Test cases are (probably) already passing.
    Component test cases help inform system test case input.
    The final step is to work with the PM to line up system test cases that cover the functional requirements.
    Then, finally, execute those test cases on the ORE at the earliest appropriate time.

    TRANSITION: So DCTHA has a lot of meetings about testing.  What do y'all talk about?

----

DCTHA Workflow
=================

How to design a test case

* Clean environment
* Prepare test input
* Run it™
* Validate the results\ :sup:`*`

  * Environment
  * Artifacts
  * Output

:sup:`*` Functional component testing may require a mocked interface

.. note::

    Clean environment; What constitutes a clean environment?
    Prepare test input; Is it a file, value, condition, artifact, or some combination thereof?
    Run it; How do we run the code?  Where do we run the code?  How much can we automate?
    Validate the results; What is the test case expected to do?  First question is, "Should this test case succeed or fail?"

    TRANSITION: This sounds like a lot.  Why should I do all that work?

----

DCTHA Workflow
=================

PROS
  + Mitigate operational risk\ :sup:`4`
  + Test cases help document expected behavior
  + Legacy tests become regression tests for future updates
  + Meet external evaluation requirements\ :sup:`4`
  + We test to deliver high-quality code\ :sup:`4`
  + Meets SGM Testing Expectations\ :sup:`4`
  + Test-design-by-committee helps...
  + Verify bugs stay fixed

.. note::

    Regression Tests - A type of change-related testing to detect whether defects have been introduced or uncovered in unchanged areas of the software. 1

    Mitigate operational risk; We're moving risk left by testiing early
    Test cases help document expected behavior; SGM says, "Testing is for development first", Easiest way to answer questions about behavior (E.g., HYFI)
    Legacy tests become regression tests for future updates; Discuss KRAB v1.1.0
    Meet external evaluation requirements; J9 likes reports
    We test to deliver high-quality code; Good test case coverage helps highlight bugs/issues/oversights soonest
    Meets SGM Testing Expectations; 3.2.5.2 Testing Expectations
    Test-design-by-committee helps: raise team experience, generates better ideas, fosters buy-in.
    Verify bugs stay fixed; Found a bug?  1. Make it a test case that fails, 2. Fix the bug, 3. Test case passes, 4. The new test case now serves as regression testing

    TRANSITION: It's not all sunshine and roses.  This isn't a hard-sell.  There's a cost to be paid.

    See References slide for subscripts

----

DCTHA Workflow
=================

CONS
  + Writing test code can be more difficult than writing production code
  + Timelines are extended
  + Some developers hate making test cases pass (and meetings)

.. note::

    More difficult; Sometimes implementing a test case is easier said than done.  
    Doubly so when you decide to automate it.
    Timelines; All that test case design --> test case implementation takes time.
    Some developers...; Talk about you-know-who without saying their name

    TRANSITION: There's good, there's bad, and DCTHA deals with it.  Assuming for a moment I decide to extend test coverage beyond "good path" testing, what should I consider?  That's where NEBS come in.

----

NEBS
=================

What is it?

* "A technique to transform user stories into test cases"\ :sup:`2`
* A guide to good test coverage\ :sup:`3`
* A "mnemonic to remember to consider Normal, Error, Boundary, and Special test conditions"\ :sup:`3`

.. note::

    Don't linger here too long.

    TRANSITION: That still doesn't tell me much.  For instance, what *is* a Normal test case?

----

NEBS
=================

What is it really?

* **Normal** - Valid usage
* **Error** - Create an error
* **Boundary** - Test the edges of applicability
* **Special** - Weird cases

.. note::

    Normal; A good user that has read the user guide.
    Error; A Petty Officer with poor reading comprehension.
    Boundary; Very good, barely good, barely bad, very bad test input.
    Special; A catch-all category for the weird use cases a devious user might attempt.

    PLOT TWIST: It's ok to mis-bin a test case.  NEBS is really just "A guide to good test coverage".

    TRANSITION: That doesn't seem well defined.  Do you have an example?

----

NEBS
=================

Example

* **Requirement** - Return the sum of two integers in Python3.
* **Design** - Caller provides two integers as arguments and the function returns the sum.  Raise an Exception on error.
* **Prototype**:

.. code:: python

    int add_it_up(num1: int, num2: int) -> int:
            """Add it up.

            Returns num1 + num2 on success.
            Raises Exception on error.
            """

.. note::

    Unit tests are pretty simplistic.  If the assemblage riots, do a little improv.
    That, or use an operational example.
    Otherwise, poll the class for some NEBS test cases.

    TRANSITION: Those are some good ideas.  Let's see what an amateur TE came up with.

----

NEBS
=================

Example

======== ============================= ===========
NEBS     Test Input                    Exp. Result
======== ============================= ===========
Normal   add_it_up(-90, 318)           228
Error    add_it_up('90', [3, 1, 8])    TypeError
Boundary add_it_up(sys.maxsize - 1, 1) sys.maxsize
Special  add_it_up(-0, 0x2 * 0o3)      6
======== ============================= ===========

.. note::

    ISTQB recommends doubling up test cases: one test case --> N functional requirements.
    As an amateur TE, I only do that for system testing.
    For component and unit testing, I tend to write one test case per requirement.

    Normal; Covers basic usage for both positive and negative integers
    Error; Two different types of bad values
    Boundary; Arbitrary upper-end limit
    Special; "negative zero" is a DCTHA fan favorite

----

References
=================

1. International Software Testing Qualifications Board (ISTQB). ISTQB Glossary. https://glossary.istqb.org
2. Cline, Al. The NEBS Transform. https://confluence.90cos.cdl.af.mil/display/CRUCIBLE/The+NEBS+Transform+-+by+Al+Cline
3. Wiegmann, Terry. 4 Things to Remember to Ensure Good Test Coverage. https://www.stickyminds.com/article/4-things-remember-ensure-good-test-coverage
4. 90 COS. Squadron Guidance Memorandum (SGM). https://90cos.pages.blacklabel.mil/cyk/squadron-guidance/

----

Questions?
=======================================

----

Outline
==========

* Intro
* Vocabulary
* DCTHA Testing Workflow
* NEBS
* References
