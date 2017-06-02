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
#include "oops-cxx/cxxgen.h"
#include "oops-platform/misc.h"

#include "AST.h"

std::string Instruction::describe_fn_impl () const
{
    std::string r = "inline std::string " + describe_fn_name () + "(" +
                    reftoptr (vm->type, "array") + ")\n{\n";

    for (const auto & param : *params)
        r += "\t" +
             assign (param.decl (),
                     read_type_from_array (vm->type, *param.type)) +
             ";\n";

    r += "\treturn std::string(\"" + *name + " (\")";

    for (const auto & param : *params)
        r += " + std::to_string(" + *param.name + ")";
    r += " + \")\";\n";

    r += "}\n\n";

    return r;
}

CXXFunction Instruction::asm_fn () const
{
    std::list<std::string> args;
    std::string b;

    b += scnl (call ("code.push_back", enum_entry ()));

    for (const auto & param : *params)
    {
        args.push_back (declare (*param.type, *param.name));
        b += scnl (write_type_to_vector (vm->type, *param.type, *param.name));
    }

    return CXXFunction (vm->asm_cls_name (), "void", asm_fn_name (), args, b);
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

std::string VM::disasm_func_body () const
{
    std::string r, do_bod;
    r += scnl (declare ("std::string", "dis"));

    do_bod += scnl (assign (declare (opcode_enum_type (), "op"),
                            cast (opcode_enum_type (), "*(code++)")));
    do_bod += nl ("switch (op)\n{");
    for (const auto instr : instrs)
        do_bod += case_x_break (
            instr.enum_entry (),
            sc ("dis +=" +
                call ("__nl", call (instr.describe_fn_name (), "code"))));
    do_bod += nl ("}");

    r += do_while (do_bod, "code != limit");
    r += return_x ("dis");

    return r;
}

std::string VM::dis_intf () const
{
    std::string c, r;

    r += pragmaonce;
    r += includesys ("string");
    r += includeuser ("QuickgenSupport.h");

    r += disasm_cls->gen_decl ();

    return r;
}

std::string VM::dis_impl () const
{
    std::string r;

    r += includeuser ("QuickgenSupport.h");
    r += includeuser (opcode_intf_filename ());
    r += includeuser (dis_intf_filename ());

    for (const auto instr : instrs)
        r += instr.describe_fn_impl ();

    r += disasm_cls->gen_def ();
    return r;
}

std::string VM::opcode_intf () const
{
    std::string r;

    /* for std::to_string */
    r += pragmaonce;
    r += includesys ("string");
    r += opcode_enum ();

    return r;
}

void VM::generate_disasm_cls ()
{
    CXXFunction dis (disasm_cls_name (), "std::string", "disassemble", {},
                     disasm_func_body ());
    std::string cons = declare_fn ("", disasm_cls_name (),
                                   declare (ref (vec_type ()), "_code")) +
                       nl (" : code(_code.data()), limit (&_code.back()) {}");
    std::list<std::string> vars = {declare (ptr (type), "code"),
                                   declare (ptr (type), "limit")};

    disasm_cls = new CXXClass (disasm_cls_name (), "", vars, {dis}, cons);
}

void VM::generate_asm_cls ()
{
    std::list<CXXFunction> funs;
    std::string cons = asm_cls_name () +
                       bracket (declare (ref (vec_type ()), "aCode")) +
                       ": code(aCode) {}";

    for (const auto & instr : instrs)
        funs.push_back (instr.asm_fn ());

    asm_cls = new CXXClass (asm_cls_name (), "",
                            {declare (ref (vec_type ()), "code")}, funs, cons);
}

std::string VM::asm_intf () const
{
    std::string r;

    r += pragmaonce;
    r += includesys ("vector");
    r += asm_cls->gen_decl ();

    return r;
}

std::string VM::asm_impl () const
{
    std::string r;

    r += includeuser ("QuickgenSupport.h");
    r += includeuser (opcode_intf_filename ());
    r += includeuser (asm_intf_filename ());
    r += asm_cls->gen_def ();

    return r;
}

void VM::generate ()
{
    for (auto & instr : instrs)
        ((Instruction &)instr).set_vm ((VM *)this);
    generate_disasm_cls ();
    generate_asm_cls ();
}
