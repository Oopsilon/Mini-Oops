/* Oopsilon
 * Object-oriented pointers - forward declaration of the hierarchy.
 *
 *      Copyright Notice
 *
 * Copyright (c) 2017 D. Mackay. All rights reserved.
 *
 * This file and its contents are supplied under the terms of the Peer
 * Production Licence as found in the Oopsilon project's source repository,
 * and David Mackay is the sole copyright holder.
 *
 *      End Copyright Notice
 */

#pragma once

template <class T> class Oop;

/* C++ STL wrapper objects */
template <class T> class VecOopDesc;

template <class T> struct objVecOop
{
    typedef Oop<VecOopDesc<T> > type;
};

typedef Oop<VecOopDesc<char> > byteVecOop;

/* Preserve the indentation. */
/* clang-format off */

typedef Oop<class OopDesc>      oop;
typedef Oop<class SmiOopDesc>     smiOop;
typedef Oop<class MemOopDesc>     memOop;
/* (this is where vecOop fits in)   vecOop; */
typedef Oop<class SymbolOopDesc>      symbolOop;
typedef Oop<class ClassOopDesc>     classOop;
typedef Oop<class MethOopDesc>      methOop;

/* clang-format on */