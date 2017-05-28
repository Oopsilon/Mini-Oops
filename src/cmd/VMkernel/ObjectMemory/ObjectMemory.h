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
    classOop _booleanClass;
    classOop _trueClass;
    classOop _falseClass;
    classOop _contextClass;
    classOop _methodClass;
    classOop _objVecClass;
    classOop _byteVecClass;
    classOop _symbolClass;

    void setup_metaclass ();
    void setup_kernel_classes ();

    /* Allocates a new Class for the corresponding Klass type T. */
    template <class T> classOop lowLevelAllocClass ();

    void notice (const char * format, ...);

  public:
    ObjectFactory factory;

    /* Setup */
    void preboot ();

    /* Allocates an object of length bytes, all fields initialised to nil/0. */
    template <typename T> T lowLevelAlloc (size_t bytes)
    {
        notice ("<T = %s> Allocating %d bytes...\n", DemangledTypeName (T),
                bytes);
        return T ((typename T::dtype *)calloc (1, bytes));
    }

    /* Basic enquiry on the object memory state. */
    classOop smiClass () { return _smiClass; }
    classOop contextClass () { return _contextClass; }
    classOop methodClass () { return _methodClass; }
    classOop objVecClass () { return _objVecClass; }
    classOop byteVecClass () { return _byteVecClass; }
    classOop symbolClass () { return _symbolClass; }

    classOop findClass (const std::string name) { return classes[name]; }

    /* Creation. */
    /* Bootstrap-level method. Find a classpair; if it hasn't been found, create
     * it. If a class is found but lacks a metaclass, create the metaclass. */
    classOop findOrCreateClass (const std::string name,
                                const std::string superName,
                                const std::vector<std::string> clsVars,
                                const std::vector<std::string> nstVars);
};
