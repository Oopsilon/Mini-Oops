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
#include "SymbolDesc.h"

class MethodDesc : public MemDesc
{
  public:
    enum
    {
        ESelector = 1,
        EArgCount,
        ETempCount,
        EEnvironmentCount,
        ELiteralVec,
        EBytecode,
    } Layout;

    static std::vector<std::string> & nstVarNames ()
    {
        const char * varnames[] = {
            /* <symbolOop>: Selector. Nil for blocks. */
            "selector",

            /* <smiOop>: Arguments count. */
            "argCount",

            /* <smiOop>: Temporaries count. */
            "tempCount",

            /* <smiOop>: Environment (closure-modifiable) variables count. */
            "environmentCount",

            /* <objVecOop>: Literal objects. */
            "literalVec",

            /* <byteVecOop>: Bytecode. */
            "bytecode",
        };

        static std::vector<std::string> varnamesVec = std::vector<std::string> (
            std::begin (varnames), std::end (varnames));
        return varnamesVec;
    }

    bool is_named (std::string name)
    {
        return **nstVar_at<symbolOop> (ESelector) == name;
    }
};