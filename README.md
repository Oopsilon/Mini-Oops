<img src="Doc/Logo/Oopsilon.png" alt="Oopsilon logo" height="132">

| Windows | Linux |
| ------- | :---- |
[![Linux build status][1]][2] | [![Windows build status][3]][4] |

[1]: https://img.shields.io/appveyor/ci/JX7P/oopsilon.svg
[2]: https://ci.appveyor.com/project/JX7P/oopsilon
[3]: https://img.shields.io/travis/Oopsilon/Oopsilon.svg
[4]: https://travis-ci.org/Oopsilon/Oopsilon


![Oopsilon 05/2017](https://img.shields.io/badge/Oopsilon-05%2F2017-red.svg)
![Platforms: Windows, FreeBSD, OS X, Linux](https://img.shields.io/badge/platforms-FreeBSD%20|%20OS%20X%20|%20Windows%20|%20Linux-lightgrey.svg)


### Overview

This is the source code for Oopsilon.

**Oopsilon** is an experimental programming system. For a fuller treatment of
Oopsilon than provided in this readme, please see
[The Red Book](http://oopsilon.readthedocs.io/en/latest/index.html).

Oopsilon is not yet ready for any serious use.

#### Oopsilon

The name is an acronym;
it stands for **O**bject **O**riented **P**rogramming **S**ystem
**I**ncorporating the **L**atest **O**bject Theory and I**n**novative Thought.

#### Design

The language belongs to the Smalltalk family of programming languages, which is
characterised by its total dynamic approach and pure object-oriented paradigm.

Several documents related to the design of Oopsilon are available:
 * [The Red Book](http://oopsilon.readthedocs.io/en/latest/index.html):
   *Oopsilon '17: The Language and its Implementation* is the Oopsilon reference manual.
   **Start here.**
 * [Oopsilon Implementation Diaries](Doc/Implementation%20Diaries/Diaries.md):
   some reports on how Oopsilon is being implemented.

#### Licence

**Oopsilon**'s source code, herein defined as that code found within this
repository, is available for use under the terms of the copyfarleft
*Peer Production Licence*; please see
[CPYRIGHT](Doc/CPYRIGHT.md) for further information.

Alternatively, Oopsilon's source code may be used under the terms of the
*Creative Commons Attribution-NonCommercial-ShareAlike (Scotland) Licence 2.5*;
please find these terms in full at
[creativecommons.org](https://creativecommons.org/licenses/by-nc-sa/2.5/scotland/legalcode).

#### FAQs

A few frequently asked questions about **Oopsilon**:

> On what platforms does Oopsilon work?

 * FreeBSD, DragonFly BSD, NetBSD, OpenBSD, and OS X
 * GNU/Linux
 * Solaris and OpenIndiana
 * Windows
 * ArcaOS and OS/2

> How is Oopsilon built?

 * Oopsilon uses the CMake system.
 * Building  Oopsilon Distribution requires a modern C++ compiler.
   * The build is tested with Microsoft C/C++ Optimising Compiler, with GNU 
     G++, and with LLVM Clang.
   * Support for Open Watcom is desirable but not yet available. If Open Watcom
     adds C++11 ranged loops and the `auto` deducing type, it should work.
   * Other compilers may work but are untested. If you make it work, please
     consider contributing your efforts.
 * The Fast Lexical Analyser FLEX is required for building. For Windows a copy
   of FLEX is included.
 * On UNIX platforms, use [Nightly](Doc/Nightly.md) to assist you in building
   the tree.
 * On Windows, use WinBuild to assist in building the tree.