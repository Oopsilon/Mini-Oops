/* Oopsilon
 * Object-oriented pointers
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

#include "Memory/Tag.h"

/* An oop is the root type of any object in the Mini-Oops system.
 * It may be a memOop (which is an allocated object) or an smiOop (which is an
 * integer stored inline. */

typedef uintptr_t smi;

class Oop
{
  public:
    bool is_smi () const { return (new ((void *)this) Tag ())->isMemOop; }
};