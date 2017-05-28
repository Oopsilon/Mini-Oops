/* Oopsilon
 * Encoder: creates bytecode for a method. (What about blocks? Perhaps we ought
 * to add a bool isBlockEncoder or something.)
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

#include "Bytecode/Bytecode.h"
#include "Bytecode/Syscall.h"
#include "Oops/VecDesc.h"

class Encoder
{
    std::vector<char> & code;

  public:
    Encoder (std::vector<char> & someCode) : code (someCode) {}

    void emitSyscall (std::string opName)
    {
        emitSyscall (Syscall::op (opName));
    }

    void emitSyscall (uint8_t op)
    {
        code.push_back (Bytecode::ESysCall0);
        code.push_back (op);
    }
};