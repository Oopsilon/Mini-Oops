/* Oopsilon
 * Klasses: Base Klass type.
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

#include "Memory/Oop.h"

#include "../Hierarchy.h"

/* The Klass object is special as it has a C++ VTable due to its use of C++
 * virtual functions. Klass holds the data needed in an Oopsilon ClassOopDesc
 * (vector of methods, vector of instance variables,) too. This is where most of
 * the logic for a Class goes. The ClassOopDesc contains a Klass inline. */
class Klass
{
    classOop superClass;
    vecOop<symbolOop>::type nstVars;
    vecOop<methOop>::type methods;

  public:
    /* Return the size of an instance of this class. */
    virtual size_t instanceSize ();
};