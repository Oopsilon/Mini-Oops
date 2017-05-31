/* Oopsilon
 * Context class definition.
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

class Context : Mem
<contextOop> pfp;

<methodOop> method;

<objVecOop<oop>::type> environment;

<std::vector<oop *>> args;
<std::vector<oop *>> temps;
<std::vector<oop *>> stack;

<smiOop> pc;

constructor (<contextOop> prev, <methodOop> meth, <std::vector<oop> *> args)
{
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
}

end