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

#include <cstdarg>

#include "ObjectMemory.h"
#include "Oops/Klass/ClassKlass.h"

template <class T> classOop ObjectMemory::lowLevelAllocClass ()
{
    classOop r     = lowLevelAlloc<ClassOopDesc> (sizeof (ClassOopDesc));
    r->getKlass () = new T;
    return r;
}

void ObjectMemory::notice (const char * format, ...)
{
    va_list args;
    va_start (args, format);

    printf (KMAG "ObjectMemory: " KNRM);
    vprintf (format, args);

    va_end (args);
}

template <typename T> Oop<T> ObjectMemory::lowLevelAlloc (size_t bytes)
{
    return Oop<T> ((T *)calloc (1, bytes));
}

void ObjectMemory::preboot ()
{
    notice ("Using %d-bit Object-Oriented Pointers\n",
            sizeof (Oop<ClassOopDesc>) * 8);
    /* Reasoning: we copy the vptr of the Klass when we subclass something.
     * Perhaps we could use a virtual function in Klass to construct a new Klass
     * for the copied object instead? That would certainly be cleaner. */
    notice ("Following sizes should be equal: %d, %d\n", sizeof (Klass),
            sizeof (ClassKlass));
    notice ("Setting up initial Object Memory...\n");

    /* The Object Metaclass */
    _objectMetaClass = lowLevelAllocClass<ClassKlass> ();
    _objectMetaClass->set_isa (_objectMetaClass);

    /* The Object Class */
    _objectClass = lowLevelAllocClass<MemKlass> ();
    _objectClass->set_isa (_objectMetaClass);

    /* Set the Object Metaclass' superClass to the Object Class. */
    _objectMetaClass->getKlass ()->set_superClass (_objectClass);

    notice ("Initial Object Memory setup.\n");
}