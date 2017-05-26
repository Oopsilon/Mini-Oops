/* Oopsilon
 * Object descriptors: Symbol object
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

#pragma once

#include "VecDesc.h"

class SymbolDesc : public ByteVecDesc
{
  public:
    byteVecOop as_byteVecOop () { return byteVecOop (this); }

    bool operator== (std::string aString) const;
    bool operator== (const char * aString) const;
};