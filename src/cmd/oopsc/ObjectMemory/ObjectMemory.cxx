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

classOop ObjectMemory::lowLevelAllocMetaClass ()
{
    classOop r     = lowLevelAlloc<ClassOopDesc> (sizeof (ClassOopDesc));
    r->getKlass () = new ClassKlass;
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
    notice ("Installing kernel scaffolding...\n");
    _objectMetaClass = lowLevelAllocMetaClass ();
}