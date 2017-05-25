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

#include <map>

#include "oops-platform/cxx.h"

#include "Oops/ClassDesc.h"
#include "Oops/Hierarchy.h"

#include "ObjectFactory.h"

class ObjectMemory
{
    /* Map of classes in the system. */
    std::map<std::string, classOop> classes;

    memOop _true;
    memOop _false;

    classOop _objectMetaClass;
    classOop _objectClass;
    classOop _smiClass;
    classOop _objVecClass;
    classOop _byteVecClass;
    classOop _symbolClass;

    void setup_metaclass ();
    void setup_metaclass_layout ();

    /* Allocates a new Class for the corresponding Klass type T. */
    template <class T> classOop lowLevelAllocClass ();

    void notice (const char * format, ...);

  public:
    ObjectFactory factory;

    /* Setup */
    void preboot ();

    /* Basic functionality */
    classOop smiClas () { return _smiClass; }
    classOop objVecClass () { return _objVecClass; }
    classOop symbolClass () { return _symbolClass; }

    /* Allocates an object of length bytes, all fields initialised to nil/0. */
    template <typename T> T lowLevelAlloc (size_t bytes)
    {
        notice ("<T = %s> Allocating %d bytes...\n", DemangledTypeName (T),
                bytes);
        return T ((typename T::dtype *)calloc (1, bytes));
    }
};
