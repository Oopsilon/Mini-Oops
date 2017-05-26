/* Oopsilon
 * Object descriptors: Memory Object
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

#include <vector>

#include "Desc.h"

/* A MemOopDesc is an Oop which points to an object - i.e. an object with
 * memory, not a tagged pointer like an smi. */
class MemOopDesc : public OopDesc
{
    /* Every object in the system has a class - and every class is some subtype
     * of the class descriptor type KlassDesc. */
    /* classOop isa; */
    /* ^ This has been moved to OopDesc in order to deal with a C++ compiler
     * issue. But in fact it should be located here, as only MemOops have an
     * isa field. */

    /* The instance variables follow immediately:
     * oop _nstVars[0];
     * They are accessed by a 1-based (*NOT* zero-based!) indexing scheme, where
     * nstVar_at(off_t index) called with an index of 1 will access the first
     * instance variable.
     * Note that isa is not regarded as an instance variable; if you are really
     * into zero-based addressing, try imagining that every object has isa as
     * its 0th nstVar. */

  public:
    void basic_init () {}

    template <class T = oop> T nstVar_at (off_t index)
    {
        return ((T *)(this + 1))[index - 1];
    }

    template <class T = oop> void nstVar_at_put (off_t index, T newVal)
    {
        ((T *)(this + 1))[index - 1] = newVal;
    }

    /* Places the specified oop into the specified instance variable.
     * If an instance variable already exists there, destroy the old one. */
    template <class T = oop> void nstVar_at_replace (off_t index, T newVal)
    {
        /* implement destroying later */
        nstVar_at_put (index, newVal);
    }
};