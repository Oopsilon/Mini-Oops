/* Oopsilon
 * Klasses: Klass type for Byte vector objects.
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

#include "../VecDesc.h"
#include "ByteVecKlass.h"

void ByteVecKlass::init_binary_object (byteVecOop obj, std::vector<char> bytes)
{
    obj->set_contents (bytes);
}

byteVecOop ByteVecKlass::allocateByteVec (std::vector<char> bytes)
{
    byteVecOop r = vm.mem.lowLevelAlloc<byteVecOop> (sizeof (ByteVecDesc));
    r->basic_init ();
    r->set_isa (vm.mem.byteVecClass ());
    init_binary_object (r, bytes);
    return r;
}