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

#include "ObjectMemory.h"

template <typename T> Oop<T> ObjectMemory::lowLevelAlloc (size_t bytes)
{
    return Oop<T> ((T *)calloc (1, bytes));
}

void ObjectMemory::preboot ()
{
    _objectMetaClass = lowLevelAlloc<ClassOopDesc> (sizeof (ClassOopDesc));
    printf ("Preboot objectmemory\n");
}