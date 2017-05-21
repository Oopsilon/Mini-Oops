/* Oopsilon
 * Object descriptors: Memory Object
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

/* A MemOopDesc is an Oop which points to an object - i.e. an object with
 * memory, not a tagged pointer like an smi. */
class MemOopDesc : public OopDesc
{
    /* Every object in the system has a class - and every class is some subtype
     * of the class descriptor type KlassDesc. */
    Oop<KlassDesc> klass;

  public:
};