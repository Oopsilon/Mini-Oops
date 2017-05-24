/* Oopsilon
 * Klasses: Klass type for Object vector objects.
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

#include "../ObjVecDesc.h"
#include "VM/VM.h"

#include "ObjVecKlass.h"

/* Klass of Object Vectors - T must be an Oop<> type! */
template <class T> typename objVecOop<T>::type ObjVecKlass<T>::allocateObjVec ()
{
    typedef typename objVecOop<T>::type rType;
    rType r = vm.mem.lowLevelAlloc<rType> (sizeof (ObjVecOopDesc<oop>));
    r->basic_init ();
    r->set_isa (vm.mem.objVecClass ());
    r->set_contents (std::vector<T> ());
    return r;
}