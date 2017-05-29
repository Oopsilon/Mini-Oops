/* Oopsilon
 * Object descriptors: Class object.
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

#include "ClassDesc.h"
#include "Desc.h"
#include "MethodDesc.h"
#include "ObjVecDesc.h"

methodOop ClassDesc::findMethod (std::string name)

{
    classOop ourSuper;
    for (const auto & meth : methods ()->contents ())
        if (meth->is_named (name))
            return meth;
    if ((ourSuper = superClass ()))
        return ourSuper->findMethod (name);
    fatalError ("Could not find method %s!\n", name.c_str ());
}
