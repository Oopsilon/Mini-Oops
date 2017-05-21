/* Oopsilon
 * Object-oriented pointers - basic descriptor.
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

#include "Memory/Oop.h"

/* An oop is the root type of any object in the Mini-Oops system.
 * It may be a MemOop (which is an allocated object) or an SmiOop (which is an
 * integer stored inline.
 *
 * The OopDesc is the actual structure. It is accessed via an Oop<someOopDesc>
 * object - the Oop acts as a handle. Note that only a MemOop is a real object.
 * SmiOops are phoneys which work by manipulating their own this-pointer. For
 * that reason they are immutable objects. */
class OopDesc
{
  public:
    bool is_smi () const
    {
        return (new ((void *)this) Oop<OopDesc> ())->isMemOop;
    }
};