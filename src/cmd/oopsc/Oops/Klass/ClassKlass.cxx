/* Oopsilon
 * Klasses: Klass descriptor for Class objects.
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

#include "ClassKlass.h"
#include "../ClassDesc.h"

size_t ClassKlass::instanceSize ()
{
    dbg ("Class dispatch works\n");
    return sizeof (ClassOopDesc);
}