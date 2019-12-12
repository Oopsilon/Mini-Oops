Preface
=======

Under Construction
~~~~~~~~~~~~~~~~~~

Oopsilon is not ready for use yet, in fact, it isn't even *useful* yet. I am
writing the documentation in advance to act as a guide for myself. 

If you are interested in what you see, please do contact me. But bear in mind
that almost nothing is set in stone yet. Having yet to be implemented, what is
described here may be as-yet unworkable. The spirit of the language is what
really matters.

The Oopsilon Programming Language
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Oopsilon is a new programming language, but its lineage direcetly descends from
that school of programming language design which stresses dynamism and extreme
late-binding, and which was incepted with McCarthy’s *Lisp* and advanced via
*Logo* and others, through to its defining member, *Smalltalk-80*.

The most visible immediate changes are the introduction of a gradual
typing scheme, known as *OGTS*, which allows for fine-grained choice in
whether or not some given code should be statically type-checked or not,
and the use of a mixin-like system for composition of functionality.

The Red Book
~~~~~~~~~~~~

This book is my attempt to provide a comprehensive introduction to my
programming philosophy, to the Oopsilon language, and to overview its
use and implementation. It is divided into several parts:

-  Section I: collects philosophical discussion on the problems of programming
   today, and outlines the ideas that make Oopsilon what it is.
-  Section II: describes the core concepts, semantics, and syntax of the
   language.
-  Section III: an overview of the Foundation Library.
-  Section IV: formal description of syntax, and the grammar and rules of
   the type system.

Section I shall introduce the fundamental philosophy that Oopsilon proceeds
from.

Section II is the point of entry for those wish to read about the language
itself. It will introduce first the essential concepts of Oopsilon - *object*,
*class*, *instance*, *message*, *protocol*, *method* - then the *OGTS*, the
Gradual Typing Scheme, which offers a system of static typing that may be used
as much or as little as needed. Exemplars of the Oopsilon syntax will be shown
alongside non-technical, plain-language explanations of the semantics.

Section III covers the Foundation Library, or *OFL*. The OFL is the standard
library for Oopsilon; it comprises the *runtime*: the set of core
classes and objects that is essential to an Oopsilon system's operation;
and the *object kit*: a set of useful classes and protocols for
collections and other uses. These classes are not unique or 'built-in' -
they are just like those which a programmer-user of Oopsilon may write.

Section IV is the standard reference for the Oopsilon '17 language, the
Oopsilon language that this book was written to support. An EBNF
description of the Oopsilon syntax is listed here. The OGTS type grammar
and a formal semantics of the type system is also provided.

On Reading the Book
~~~~~~~~~~~~~~~~~~~

This book has been written assuming it will be read by those of
technical mind, who understand already the fundamentals of programming
as a general matter. It is not a beginners' tutorial; it is intended for
those who already program, including those who may have learnt to
program in Oopsilon and now seek to understand the system more formally.

This should not be taken as dissuasion from trying to read the book if
you are not so technically knowledgeable. It may be interesting
regardless, and the subject matter is not overly complicated. The
philosophy chapter in particular is relevant to all.

Oopsilon is a very different system to a lot of programming languages.
The most obvious impact for the reader is that terminology used differs
in a lot of areas. Any jargon used will be explained in advance. More
importantly, the difference underscores the importance of approaching with an
open mind this book and the philosophy behind Oopsilon.