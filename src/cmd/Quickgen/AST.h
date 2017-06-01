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

struct VM;

struct Field
{
    std::string * type;
    std::string * name;

    std::string decl () const { return *type + " " + *name; }
};

struct Instruction
{
    std::string * name;
    std::list<Field> * params;
    std::list<Field> * stackTook;
    std::list<Field> * stackGave;
    std::string * impl;

    VM * vm;

    void set_vm (VM * aVM) { vm = aVM; }

    std::string enum_entry () const { return "E" + *name; }
    std::string describe_fn_name () const { return "Describe" + *name; }
    std::string describe_fn_impl () const;
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

    std::string opcode_enum () const;
    std::string opcode_enum_type () const { return "T" + name + "Opcodes"; }
    std::string opcode_enum_name () const { return name + "Opcodes"; }
    std::string opcode_str_table () const;
    std::string opcode_str_table_name () const { return name + "OpcodeNames"; }

    /* Shut C++ up. */
    VM () {}

    void generate () const;
};