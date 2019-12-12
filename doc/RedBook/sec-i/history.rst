The State of Programming
========================

Oopsilon is not a system designed by committee; it's not a system built
to help solve a single problem, either.

It is a language that exists as part of my effort to help solve a bigger open
question: what is wrong with programming? Is software whack? We can imagine a
world in which computers are instruments to help and assist us; why doesn't our
world look so perfect yet, why is "technical issues" the new normal culprit for
all kinds of problems?

The development of computing is not something that can be viewed as a line
from simple to complex, bad to good, primitive to modern, even while such a
view might appear to be *roughly* corect on the face of it. Thomas Kuhn
famously authored the concept of *paradigm shift*, a sudden development that
changes significantly the state of a science. 

A brief modern history of computer programming is probably an essential basis
for understanding the philosophical roots of Oopsilon. It is worth comparing
this history to the history of enlightenment outlined in
Adorno and Horkheimer's 'Dialectic of Enlightenment'.

Structured Programing Emerges
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There was once a time - and that time has left its mark on the computing
world - in which software was understood simply as the sequential
execution of instructions. Only well-positioned \_GOTO\_s provided any
control of flow; and thank the Lord that today even the basest
philistine acknowledges that *that* was not a good way to do things.

Structured programming was the prescription of CS pioneer Edgers
Dijkstra, and ALGOL 60 offered it. Now instead of \_go\_ing-\ *to* line
numbers and labels, we could organise our code into subroutines and
express directly such notions as "if X is true, then do Y, if not, then
do Z."

At last programming should have made sense - no longer become a pile of
incomprehensible instructions executed in sequence (except when they
weren't.)


Structured Programming Proves Inadequate
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Throughout the 70s and 80s a new system came about: Unix. It was swiftly
moved to the structured programming paradigm that C offered, pushing
unstructured assembly language to the sidelines.

Cultural values surrounding Unix tended to focus on the concept that a
program should "do one thing, but do it well." Programs were to
communicate by plain text, and all manner of behaviour could be achieved
by various programs communicating with one-another.

By the 1980s, the Unix kernel had ballooned into the much larger
BSD and System V derivatives. The kernel did not "do one
thing, but do it well." It was a behemoth. The Unix philosophy produced
a very coarse kind of separation-of-concerns; processes are typically
quite expensive, and within each program (including the kernel itself,)
messiness accrued. Structured programming hadn't managed to save us from
shambolic source code.

Object-oriented Programming
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Ivan Sutherland created in 1963 a revolutionary computer system. It was
called Sketchpad and it was a constraint-based computer drawing system.
Among its many features were an early concept of a graphical 'window.'
One of the most important features was a concept of 'master' and
'instance' drawings. A master drawing was a drawing which could be
instantiated; the instances could be modified independently in terms of
scale, position, and orientation, and editing the master drawing would
cause the instance drawings to reflect the changes to the master.

This was nothing less than the first object-oriented system, in many
respects. Later in the 60s, Kristen Nygaard and Ole-Johan Dahl invented
a programming language called Simula-67 which introduced analogous
concepts of 'classes' and 'instances.'

That work formed part of the basis for Smalltalk: a programming language based
on the concept of autonomous independent objects which communicate with one
another by sending messages. Alan Kay and others eventually came to
produce Smalltalk-80, the first publically available language in the
Smalltalk family. Now at last this new kind of programming could solve all our
problems.

The End of History
~~~~~~~~~~~~~~~~~~

In the 1990s, the "suit and tie" languages rose and a lot of the experimental
spirit of early CS was sidelined. Object-oriented programming suffered a cruel
fate. Instead of the vision of a different way it offered, it became a grouping
mechanism for procedures and mutable state. This is a far cry from creating a
world of objects which interact with each other by messages, and never by
'setting fields' in one another!

