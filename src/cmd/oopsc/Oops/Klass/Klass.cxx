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

#include "ObjectMemory/ObjectFactory.inl.h"

void Klass::init ()
{
    //_nstVars = vm.mem.factory.newObjVec<symbolOop> ();
    //_methods = vm.mem.factory.newObjVec<methOop> ();
}

void Klass::init (classOop aClass)
{
    aClass->set_nstVars (vm.mem.factory.newObjVec<symbolOop> ());
}

size_t Klass::instanceSize (classOop aClass)
{
    return sizeof (OopDesc) + (sizeof (oop) * aClass->nstVars ()->size ());
}