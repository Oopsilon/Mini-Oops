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

#include "VM/VM.h"

#include "../MethodDesc.h"

#include "MethodKlass.h"

methodOop MethodKlass::allocate_method (symbolOop sel, smiOop args,
                                        smiOop temps, smiOop heapvars,
                                        objVecOop<>::type literals,
                                        byteVecOop code)
{
    methodOop r =
        vm.mem.lowLevelAlloc<methodOop> (instanceSize (vm.mem.methodClass ()));
    r->basic_init ();
    r->set_isa (vm.mem.methodClass ());

    return r;
}