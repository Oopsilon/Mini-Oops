/* Oopsilon
 * Klasses: Klass type for metaclasses.
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

#include "MemKlass.h"

/* This is the Klass of metaclasses. */
class ClassKlass : public MemKlass
{
  public:
    virtual size_t instanceSize ();
};