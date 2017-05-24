/* Oopsilon
 * Object Memory: the Oopsilon object-oriented memory space.
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

#include "Oops/ClassDesc.h"
#include "Oops/Hierarchy.h"

class ObjectMemory
{
    memOop _true;
    memOop _false;

    classOop _objectMetaClass;
    classOop _objectClass;
    classOop _smiOopClass;
    classOop _objVecOopClass;
    classOop _byteVecOopClass;
    classOop _symbolOopClass;

    /* Allocates a new Class for the corresponding Klass type T. */
    template <class T> classOop lowLevelAllocClass ();

    void notice (const char * format, ...);

  public:
    /* Setup */
    void preboot ();

    /* Basic functionality */
    classOop symbolClass () { return _symbolOopClass; }

    /* Allocates an object of length bytes, all fields initialised to nil/0. */
    template <typename T> T lowLevelAlloc (size_t bytes)
    {
        return T ((typename T::dtype *)calloc (1, bytes));
    }
};