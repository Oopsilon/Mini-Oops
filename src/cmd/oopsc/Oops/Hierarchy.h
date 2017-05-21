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

/* Preserve the indentation. */
/* clang-format off */

template <class T> class Oop;

typedef Oop<class OopDesc> oop;
typedef Oop<class   SmiOopDesc> smiOop;
typedef Oop<class   MemOopDesc> memOop;
typedef Oop<class     ClassOopDesc> classOop;
typedef Oop<class     MethOopDesc> methOop;
/*          class     VecOopDesc */

/* C++ STL wrapper objects */

template <class T> class VecOopDesc;

template <typename T>
struct vecOop
{
    typedef Oop<VecOopDesc<T> > type;
};

/* clang-format on */