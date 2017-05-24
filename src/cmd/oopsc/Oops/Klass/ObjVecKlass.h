/* Oopsilon
 * Klasses: Klass type for Object vector objects.
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

#include "../Hierarchy.h"
#include "MemKlass.h"

/* Klass of Object Vectors - T must be an Oop<> type! */
template <class T> class ObjVecKlass : public MemKlass
{
  public:
    typename objVecOop<T>::type allocateObjVec ();
};