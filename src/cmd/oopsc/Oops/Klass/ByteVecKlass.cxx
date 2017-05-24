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

#include "ByteVecKlass.h"
#include "../VecDesc.h"

void ByteVecKlass::init_binary_object (byteVecOop obj, std::vector<char> bytes)
{
    obj->set_contents (bytes);
}