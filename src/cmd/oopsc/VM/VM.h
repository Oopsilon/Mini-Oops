/* Oopsilon
 * VM class definition.
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

#include "ObjectMemory/ObjectMemory.h"

class VM
{
  public:
    static VM globalVM;
    ObjectMemory mem;

    void notice (const char * format, ...);

    VM ();

    void boot ();
};

extern VM & vm;