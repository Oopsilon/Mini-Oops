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

#include "ObjectMemory/ObjectMemory.h"

class VM
{
    ObjectMemory mem;

  public:
    static VM globalVM;

    void notice (const char * format, ...);

    VM ();
};

extern VM & vm;