/* Oopsilon
 * Klasses: Klass type for Method objects.
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
#include "VM/VM.h"

#include "../MethodDesc.h"

#include "MethodKlass.h"

methodOop MethodKlass::allocate_method (symbolOop sel, smiOop args,
                                        smiOop temps, smiOop heapvars,
                                        objVecOop<>::type literals,
                                        byteVecOop code)
{
    methodOop r = vm.mem.lowLevelAlloc<methodOop> (
        vm.mem.methodClass ()->instanceSize ());
    r->basic_init ();
    r->set_isa (vm.mem.methodClass ());
    r->nstVar_at_put (MethodDesc::ESelector, sel);
    r->nstVar_at_put (MethodDesc::EArgCount, args);
    r->nstVar_at_put (MethodDesc::ETempCount, temps);
    r->nstVar_at_put (MethodDesc::EEnvironmentCount, heapvars);
    r->nstVar_at_put (MethodDesc::ELiteralVec, literals);
    r->nstVar_at_put (MethodDesc::EBytecode, code);

    return r;
}