/* Oopsilon
 * Object descriptors: Small integer object
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

#include "Desc.h"

/* An Smi is a small integer's underlying representation. */
typedef uintptr_t Smi;

/* The SmiOopDesc is actually empty. It is zero-length. So it simply operates
 * on its own 'this' value - which is not actually a pointer to any valid
 * region of memory, but is an integer with an LSB of 1. */
class SmiOopDesc : OopDesc
{
  public:
    /* Retrieve the value of the integer.
     * Notice that it works by placement-constructing an Oop on its own
     * this-pointer, and then consulting said Oop to request the value.
     * This is why an SmiOop is immutable. A new one should be constructed if a
     * value is to be updated, and the location of the old SmiOop have the new
     * Oop<SmiOopDesc> assigned. */
    Smi value () const
    {
        return (new ((void *)this) Oop<SmiOopDesc> ())->smiValue;
    }
};