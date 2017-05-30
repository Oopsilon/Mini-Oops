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
template <class T> class VecDesc;
template <class T> class ObjVecDesc;
typedef VecDesc<char> ByteVecDesc;

/* Preserve the indentation. */
/* clang-format off */

typedef Oop<class Desc>      oop;
typedef Oop<class SmiDesc>     smiOop;
typedef Oop<class MemDesc>     memOop;
typedef Oop<class ClassDesc>     classOop;
typedef Oop<class MethodDesc>    methodOop;
typedef Oop<class ContextDesc>   contextOop;
/* (this is where vecOop fits in)  vecOop; */
/*                                   objVecOop */
typedef Oop<      ByteVecDesc>       byteVecOop;
typedef Oop<class SymbolDesc>          symbolOop;

template <class T = oop> struct objVecOop
{
    typedef Oop<ObjVecDesc<T> > type;
};

/* clang-format on */