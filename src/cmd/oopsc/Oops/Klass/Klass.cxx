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

void Klass::init (classOop aClass)
{
    initNstVars (aClass);
    initMethods (aClass);
}

void Klass::initNstVars (classOop aClass)
{
    aClass->set_nstVars (vm.mem.factory.newObjVec<symbolOop> ());
}

void Klass::initMethods (classOop aClass)
{
    aClass->set_methods (vm.mem.factory.newObjVec<methodOop> ());
}

size_t Klass::instanceSize (classOop aClass)
{
    return sizeof (OopDesc) + indexableNstVarsSize (aClass);
}

size_t Klass::indexableNstVarsSize (classOop aClass)
{
    return (sizeof (oop) * aClass->nstVars ()->size ()) +
           (aClass->superClass ()
                ? aClass->superClass ()->indexableNstVarsSize ()
                : 0);
}