/* Oopsilon
 * Method class definition.
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

class Method : Mem

klass_intf_requires
{
    #include <vector>
}

klass_impl_requires
{
    #include "VM/VM.h"
    #include "ObjectMemory/ObjectFactory.inl.h"
}

<symbolOop> selector;

<smiOop> argCount;
<smiOop> tempCount;
<smiOop> environmentCount;

<objVecOop<>::type> environment;
<objVecOop<>::type> literals;
<byteVecOop> bytecode;

/* Allocates a (non-block) method. */
constructor allocate_method (<symbolOop> sel, <smiOop> args, <smiOop> temps,
                               <smiOop> heapvars, <objVecOop<>::type> literals,
                               <byteVecOop> code);
{
    r->set_selector(sel);
    r->set_argCount(args);
    r->set_tempCount(temps);
    r->set_environmentCount(heapvars);
    r->set_literals(literals);
    r->set_bytecode(code);
}

end