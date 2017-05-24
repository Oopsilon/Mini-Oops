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
template <typename T> struct Oop
{
    typedef T dtype;

    union {
        struct
        {
            Smi smiValue : smiBits;
            /* Don't change this to a bool. Doing so fucks the packing.
             * It has to be the same type as the other member of the packed
             * struct. */
            Smi isSmiOop : 1;
        } PACKSTRUCT;
        T * memOopValue;
    } PACKSTRUCT;

    Oop () : memOopValue (NULL) {}
    Oop (Smi aNumber) : isSmiOop (true) {}
    Oop (T * anObj) : memOopValue (anObj) {}

    bool operator! () const { return memOopValue == 0; }
    bool operator== (const Oop<T> & rhs)
    {
        return memOopValue == rhs.memOopValue;
    }
    bool operator!= (const Oop<T> & rhs) { return !operator== (rhs); }

    T * operator* () const { return memOopValue; }
    T * operator-> () const { return memOopValue; }
} PACKSTRUCT;

#include "oops-cxx/endpack.h"