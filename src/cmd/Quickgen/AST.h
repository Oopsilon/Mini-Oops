/* Oopsilon
 * Quickgen: VM generator.
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

#include <list>
#include <string>

struct Field
{
    std::string * type;
    std::string * name;
};

struct Instruction
{
    std::string * name;
    std::list<Field> * params;
    std::list<Field> * stackTook;
    std::list<Field> * stackGave;
    std::string * impl;
};

struct VM
{
    std::string name;
    std::string type;
    std::list<Instruction> instrs;

    VM (std::string aName, std::string anOpType,
        std::list<Instruction> someInstrs)
        : name (aName), type (anOpType), instrs (someInstrs)
    {
    }

    void generate () const;
};