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

#include "Quickgen.h"
#include "oops-platform/misc.h"

#include "AST.h"

std::string quote (std::string aStr) { return "\"" + aStr + "\""; }

std::string assign (std::string lval, std::string rval)
{
    return lval + " = " + rval;
}

std::string ptrref (std::string type, std::string name)
{
    return "const " + type + " *& " + name;
}

std::string read_type_from_array (std::string artype, std::string type,
                                  std::string arname = "array")
{
    return "read_type_from_array<" + artype + ", " + type + ">(" + arname + ")";
}

std::string Instruction::describe_fn_impl () const
{
    std::string r = "inline std::string " + describe_fn_name () + "(" +
                    ptrref (vm->type, "array") + ")\n{\n";

    for (const auto & param : *params)
        r += "\t" +
             assign (param.decl (),
                     read_type_from_array (vm->type, *param.type)) +
             ";\n";

    r += "\treturn \"" + *name + " (\"";

    for (const auto & param : *params)
        r += " + std::to_string(" + *param.name + ")";
    r += " + \")\";\n";

    r += "}\n\n";

    return r;
}

std::string VM::opcode_enum () const
{
    std::string r = "enum " + opcode_enum_type () + "\n{\n";
    for (const auto & instr : instrs)
        r += "\t" + instr.enum_entry () + ",\n";
    r += "};\n\n";
    return r;
}

std::string VM::opcode_str_table () const
{
    std::string r = "static const char * " + opcode_str_table_name () + "[" +
                    std::to_string (instrs.size ()) + "] = {\n";
    for (const auto & instr : instrs)
        r += "\t" + quote (*instr.name) + ",\n";
    r += "};\n\n";
    for (const auto instr : instrs)
        qg.notice ("%s\n", instr.describe_fn_impl ().c_str ());
    return r;
}

void VM::generate () const
{
    for (auto & instr : instrs)
        ((Instruction &)instr).set_vm ((VM *)this);
    qg.notice ("\n%s\n%s\n", opcode_enum ().c_str (),
               opcode_str_table ().c_str ());
}
