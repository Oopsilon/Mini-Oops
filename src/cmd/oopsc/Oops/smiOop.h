/* Oopsilon
 * Small integer
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

#include "Oop.h"

typedef uintptr_t Smi;

class SmiOop : Oop
{
  public:
    Smi value () { return *(new ((void *)this) Tag ())->smiValue; }
};