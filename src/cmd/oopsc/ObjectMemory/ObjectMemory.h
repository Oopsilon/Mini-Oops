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
    classOop _memOopClass;
    classOop _smiOopClass;
    classOop _symbolOopClass;

  public:
    void preboot ();

    template <typename T> Oop<T> lowLevelAlloc (size_t bytes);
};