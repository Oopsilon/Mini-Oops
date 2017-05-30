/* Oopsilon
 * Klasses: Klass type for Context objects.
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

#include "../ContextDesc.h"
#include "../MethodDesc.h"
#include "../SmiDesc.h"

#include "ObjectMemory/ObjectFactory.inl.h"
#include "VM/VM.h"

#include "ContextKlass.h"

contextOop ContextKlass::allocate_context (
    methodOop meth /* std::vector<oop> * args, contextOop pfp */)
{
    size_t envCount;
    contextOop r = vm.mem.lowLevelAlloc<contextOop> (
        vm.mem.contextClass ()->instanceSize ());
    r->basic_init ();
    r->set_isa (vm.mem.contextClass ());

    r->nstVar_at_put (ContextDesc::EMethod, meth);

    if ((envCount = meth->nstVar_at<smiOop> (MethodDesc::EEnvironmentCount)
                        .smiValue ()) != 0)
        r->nstVar_at_put (ContextDesc::EEnvironment,
                          vm.mem.factory.newObjVec<oop> (/* envCount */));
    else if (objVecOop<oop>::type env = meth->nstVar_at<objVecOop<oop>::type> (
                 MethodDesc::EEnvironment))
        r->nstVar_at_put (ContextDesc::EEnvironment, env);

    r->nstVar_at_put (ContextDesc::EArgs, NULL);
    r->nstVar_at_put (ContextDesc::ETemps, new std::vector<oop>);
    r->nstVar_at_put (ContextDesc::EStack, new std::vector<oop>);

    r->nstVar_at_put (ContextDesc::EPC, Smi (0));
    r->nstVar_at_put (ContextDesc::EPFP, NULL);
    return r;
}