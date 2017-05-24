/* Oopsilon
 * Object descriptors: CompiledMethod object.
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

#include "MemDesc.h"

class CompiledMethod : public MemOopDesc
{
    symbolOop selector;
    smiOop tempCnt;
    objVecOop literals;
    byteVecOop bytecode;

  public:
    bool is_named (std::string name) { return *selector == name; }
};