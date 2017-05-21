/* Oopsilon
 * Tag: object reference handle
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

#include <cstdint>

#include "oops-platform/misc.h"

const int platformBits = sizeof (void *);

struct Tag
{
    union {
        struct
        {
            uintptr_t smiValue[platformBits - 1];
            uintptr_t isMemOop[1];
        };
        uintptr_t value;
    };
};