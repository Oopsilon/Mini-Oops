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

constructor allocate_context (<contextOop> prev, <methodOop> meth,
                              <std::vector<oop> *> args)
{
    r->set_pfp(prev);
    r->set_method(meth);

    if ((envCount = meth->nstVar_at<smiOop> (MethodDesc::EEnvironmentCount)
                        .smiValue ()) != 0)
        r->set_environment(vm.mem.factory.newObjVec<oop> (/* envCount */));
    else if (objVecOop<oop>::type env = meth->nstVar_at<objVecOop<oop>::type> (
                 MethodDesc::EEnvironment))
        r->set_environment (env);

    r->set_args (args);
    r->set_temps (new std::vector<oop> (/* size? */));
    r->set_stack (new std::vector<oop>);

    r->set_pc (Smi (0));
}

end