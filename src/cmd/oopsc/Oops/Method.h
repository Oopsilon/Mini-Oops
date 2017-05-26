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

class Method : public MemOopDesc
{
    enum
    {
        ESelector = 1,
        ETempCount,
        ELiteralVec,
        EBytecode,
    } Layout;

  public:
    static std::vector<std::string> & nstVarNames ()
    {
        const char * varnames[] = {
            /* <symbolOop>: Selector */
            "selector",

            /* <smiOop>: Temporaries count. */
            "tempCount",

            /* <std::vector<oop> *>: Literal objects. */
            "literalVec",

            /* <std::vector<char> *>: Bytecode. */
            "bytecode",
        };

        static std::vector<std::string> varnamesVec = std::vector<std::string> (
            std::begin (varnames), std::end (varnames));
        return varnamesVec;
    }

    symbolOop selector () { return nstVar_at<symbolOop> (ESelector); }
    void set_selector (symbolOop val) { return nstVar_at_put (ESelector, val); }

    smiOop tempCount () { return nstVar_at<smiOop> (ETempCount); }
    void set_tempCount (smiOop val) { return nstVar_at_put (ETempCount, val); }

    std::vector<oop> * literalVec ()
    {
        return nstVar_at<std::vector<oop> *> (ELiteralVec);
    }
    void set_literalVec (std::vector<oop> * val)
    {
        return nstVar_at_put (ELiteralVec, val);
    }

    std::vector<char> * bytecode ()
    {
        return nstVar_at<std::vector<char> *> (EBytecode);
    }
    void set_bytecode (std::vector<char> * val)
    {
        return nstVar_at_put (EBytecode, val);
    }

    bool is_named (std::string name) { /*return *selector == name;*/}
};