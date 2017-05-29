/* Oopsilon
 * Oop: object reference handle (either points to an object, or is an inline
 * Smi.)
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

#include <cstdint>

#include "oops-platform/misc.h"

#include "oops-cxx/packstrc.h"

const size_t platformBits = sizeof (void *);
const size_t smiBits      = platformBits - 1;

/* An Smi is a small integer's underlying representation. */
typedef uintptr_t Smi;

/* An Oop is an Object-Oriented Pointer.
 * It is the handle used to refer to OopDescs. */
template <class T> struct Oop
{
    /* The type the Oop points to. Use this for e.g. allocation size choice. */
    typedef T dtype;

    /* Note - we should really use an object table */
    T * memOopValue;

    Oop () { memOopValue = NULL; }
    Oop (Smi aNumber) { memOopValue = 1 & (aNumber << 1); }
    Oop (T * anObj) { memOopValue = (anObj); }
    Oop (const T * anObj) { memOopValue = ((T *)anObj); }

    Smi smiValue () { return uintptr_t (memOopValue) >> 1; }
    bool isSmiOop () { return uintptr_t (memOopValue) & 1; }
    bool isSmiZero ()
    {
        return isSmiOop () && uintptr_t (memOopValue) >> 1 == 0;
    }

    template <class R> R cast ()
    {
        return R ((typename R::dtype *)memOopValue);
    }

    /* Is it nil? */
    operator bool () const { return memOopValue != 0; }
    bool operator! () const { return memOopValue == 0; }
    bool operator== (const Oop<T> & rhs) const
    {
        return memOopValue == rhs.memOopValue;
    }
    bool operator!= (const Oop<T> & rhs) const { return !operator== (rhs); }

    T * operator* () const { return memOopValue; }
    T * operator-> () const { return memOopValue; }
} PACKSTRUCT;

#include "oops-cxx/endpack.h"