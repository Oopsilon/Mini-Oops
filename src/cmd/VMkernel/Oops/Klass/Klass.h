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

#include "ObjectMemory/Oop.h"

#include "../Hierarchy.h"

/* The Klass object is special as it has a C++ VTable due to its use of C++
 * virtual functions. Klass holds the data needed in an Oopsilon ClassOopDesc
 * (vector of methods, vector of instance variables,) too. This is where most of
 * the logic for a Class goes. The ClassOopDesc contains a Klass inline. */
class Klass
{
  public:
    /* Setup */

    void init (classOop aClass);
    void initNstVars (classOop aClass);
    void initMethods (classOop aClass);

    void add_method (classOop cls, methodOop meth);

    /* Enquiry on Klass */

    /* Return the size of an instance of this class - forbidden for Smi. */
    virtual size_t instanceSize (classOop aClass);

    /* Return the size of an instance's indexed vars component. */
    size_t indexableNstVarsSize (classOop aClass);

    /* Enquiry on Object
     * These are despatched from an OOP, not directly to a Klass. */

    /* Describes an object. */
    virtual std::string describe (oop anObject) { return "<Unknown Object>"; }
};