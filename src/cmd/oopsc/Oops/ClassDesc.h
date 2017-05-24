/* Oopsilon
 * Object descriptors: Class object
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

#include "Desc.h"
#include "Klass/Klass.h"

/* Memory layout:
 * oop isa;
 * Klass * klass;
 *   -> nstVars, methods, etc.
 */
class ClassOopDesc : public OopDesc
{
    Klass * klass;

  public:
    /* These is a non-standard setter because it doesn't involve an Oops.
     * A Klass' lifetime is the lifetime of the ClassDesc it belongs to. */
    inline Klass * getKlass () { return klass; }
    inline void setKlass (Klass * newKlass) { klass = newKlass; }

    inline size_t instanceSize () { return klass->instanceSize (); }
};