<img src="Doc/Logo/Oopsilon.png" alt="Oopsilon logo" width="585" height="129">

![Travis CI](https://img.shields.io/travis/Oopsilon/Mini-Oops.svg)](https://travis-ci.org/Oopsilon/Mini-Oops)
![Oopsilon 05/2017](https://img.shields.io/badge/Oopsilon-05%2F2017-red.svg)
![Platforms: Windows, FreeBSD, OS X, Linux](https://img.shields.io/badge/platforms-FreeBSD%20|%20OS%20X%20|%20Windows%20|%20Linux-lightgrey.svg)


### Overview

This is the Oopsilon VM/F tree (Virtual Machine/Foundation tree.) This is
the source code to the Oopsilon Dynamic Compiler and the Foundation library
(including runtime.) It builds the Oopsilon VM/F Consolidation.

**Oopsilon** is an experimental programming system.

#### Oopsilon

The name is an acronym;
it stands for **O**bject **O**riented **P**rogramming **S**ystem
**I**ncorporating the **L**atest **O**bject Theory and I**n**novative Thought.
Oopsilon is a *critical* programming environment: it has a negative character,
that is to say, it attacks conventional paradigms of programming. At the same
time it proposes the way things might develop to build a better computing.

#### Design

The language belongs to the Smalltalk family of programming languages, which is
characterised by its total dynamic approach, pure object-oriented paradigm, and
a measure of similarity to the functional languages (the language feature
Blocks is essentially form of lambda function; blocks are used extensively.)

Several documents related to the design of Oopsilon are available:
 * [The Oopsilon Object Model](Doc/Objects.md): describes the object model
   used in Oopsilon.

#### Philosophy

Oopsilon takes as its starting point the idea that nothing can be taken for
granted: we must attempt to negate everything that is given. The meaning of
critique is shown in such works as Kant's Critique of Pure Reason or Adorno's 
'Negative Dialectics.' Not coincidentally, these thinkers enumerated above are
great philosophical influences on Oopsilon.

#### Licence

**Oopsilon**'s source code, herein defined as that code found within this
repository, is available for use under the terms of the
*Peer Production Licence*; please see
[CPYRIGHT](Doc/CPYRIGHT.md) for further information.

Alternatively, Oopsilon's source code may be used under the terms of the
*Creative Commons Attribution-NonCommercial-ShareAlike (Scotland) Licence 2.5*;
please find these terms in full at
[creativecommons.org](https://creativecommons.org/licenses/by-nc-sa/2.5/scotland/legalcode).

#### FAQs

A few frequently asked questions about **Oopsilon**:

> On what platforms does Oopsilon work?

 * FreeBSD, DragonFly BSD, NetBSD, OpenBSD, OS X
 * GNU/Linux, Musl/BusyBox/Linux
 * Solaris, OpenIndiana
 * Windows, ArcaOS, OS/2

> How is Oopsilon built?

 * Oopsilon leverages the CMake build system for building the C/FL 
   consolidation.
 * Building the VM/F consolidation requires a modern C++ compiler.
   * The build is tested with Microsoft C/C++ Optimising Compiler 19.0
     (MS Visual Studio 2017,) with GNU G++ 5.4.0, and with Clang 3.8.0.
   * Other compilers may work but are untested. If you make it work, please
     consider contributing your efforts.
   * Support for Open Watcom is desirable but not yet available. If Open Watcom
     adds C++11 ranged loops and the `auto` deducing type, it should work.
 * The Fast Lexical Analyser FLEX is required for building.
 * The VM/F consolidation is build with Nightly, a build script which prepares
   the build and then invokes CMake to build the consolidation. It is
   documented in [Nightly](Doc/Nightly.md).
