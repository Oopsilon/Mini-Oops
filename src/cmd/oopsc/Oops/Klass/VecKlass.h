/* Oopsilon
 * Klasses: Klass type for Vec objects.
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

#include "../VecDesc.h"
#include "MemKlass.h"

template <class T> class VecKlass : public MemKlass
{
  public:
    size_t instanceSize () { return sizeof (VecOopDesc<T>); }
};
