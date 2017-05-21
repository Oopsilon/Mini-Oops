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

class ClassOopDesc : public OopDesc
{
    Klass klass;

  public:
    inline Klass * getKlass () { return &klass; }
};