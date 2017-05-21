/* Oopsilon
 * Tag: object reference handle
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

const size_t platformBits = sizeof (void *);
const size_t smiBits      = platformBits - 1;

/* An Oop is an Object-Oriented Pointer.
 * It is the handle used to refer to OopDescs. */
template <typename T> struct Oop
{
    union {
        struct
        {
            uintptr_t smiValue[smiBits];
            uintptr_t isMemOop[1];
        };
        T * memOopValue;
    };

    T * operator* () const { return memOopValue; }
    T * operator-> () const { return memOopValue; }
};