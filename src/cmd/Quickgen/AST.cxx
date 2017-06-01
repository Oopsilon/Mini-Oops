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

std::string sc (std::string line) { return line + ";"; }
std::string nl (std::string line) { return line + "\n"; }
std::string nlseq (std::list<std::string> lines)
{
    std::string r;
    for (const auto & str : lines)
        r += nl (str);
    return r;
}

std::string includesys (std::string file)
{
    return nl ("#include <" + file + ">");
}
std::string includeuser (std::string file)
{
    return nl ("#include \"" + file + "\"");
}

std::string scnl (std::string line) { return nl (sc (line)); }

std::string quote (std::string aStr) { return "\"" + aStr + "\""; }

std::string return_x (std::string ret) { return scnl ("return " + ret); }

std::string assign (std::string lval, std::string rval)
{
    return lval + " = " + rval;
}

std::string declare (std::string type, std::string name)
{
    return type + " " + name;
}

std::string declare_class (std::string name, std::string contents)
{
    return nl ("struct " + name) + nl ("{") + contents + nl ("};");
}

std::string declare_fn (std::string type, std::string name, std::string args)
{
    return type + " " + name + " (" + args + ")";
}

std::string ptr (std::string type) { return type + " *"; }

std::string ref (std::string type) { return type + " &"; }

std::string reftoptr (std::string type, std::string name)
{
    return ref (ptr (type)) + name;
}

std::string comma_seq (std::list<std::string> things)
{
    std::string r;
    bool onFirst = true;

    for (const auto & str : things)
        r += (onFirst ? "" : (onFirst = false, ", ")) + str;

    return r;
}

std::string bracket (std::string txt) { return "(" + txt + ")"; }

std::string cast (std::string type, std::string expr)
{
    return bracket (bracket (type) + bracket (expr));
}

std::string call (std::string func, std::string args)
{
    return func + bracket (args);
}

std::string do_while (std::string todo, std::string condition)
{

    return "do\n{\n" + todo + "}\nwhile(" + condition + ");\n";
}

std::string case_x_break (std::string cond, std::string todo)
{
    return nl (nl ("case " + cond + ":") + "\t" + nl (todo) + nl ("\tbreak;"));
}

std::string read_type_from_array (std::string artype, std::string type,
                                  std::string arname = "array")
{
    return "read_type_from_array<" + artype + ", " + type + ">(" + arname + ")";
}

struct CXXFunction
{
    std::string cls;
    std::string rtype;
    std::string name;
    std::list<std::string> params;
    std::string body;

    CXXFunction (std::string aCls, std::string aRtype, std::string aName,
                 std::list<std::string> aParams, std::string aBody)
        : cls (aCls), rtype (aRtype), name (aName), params (aParams),
          body (aBody){};

    std::string gen_inclass_decl ()
    {
        return scnl (declare_fn (rtype, name, comma_seq (params)));
    }
    std::string gen_def ()
    {
        return nl (
            nl (declare_fn (rtype, cls + "::" + name, comma_seq (params))) +
            nl ("{") + nl (body) + nl ("}"));
    }
};

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

    r += includesys ("string");
    r += includeuser ("QuickgenSupport.h");

    c += scnl (declare (ptr (type), "code"));
    c += scnl (declare (ptr (type), "limit"));
    c += scnl (declare_fn ("std::string", "disassemble", ""));
    c += declare_fn ("", disassembler_class_name (),
                     declare (ref (vec_type ()), "_code")) +
         nl (" : code(_code.data()), limit (&_code.back()) {}");

    r += declare_class (disassembler_class_name (), c);

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

    r += disasm_func->gen_def ();

    return r;
}

std::string VM::opcode_intf () const
{
    std::string r;

    /* for std::to_string */
    r += includesys ("string");
    r += opcode_enum ();

    return r;
}

void VM::generate ()
{
    for (auto & instr : instrs)
        ((Instruction &)instr).set_vm ((VM *)this);
    disasm_func = new CXXFunction (disassembler_class_name (), "std::string",
                                   "disassemble", {}, disasm_func_body ());
    qg.notice ("\n%s\n%s\n", opcode_enum ().c_str (),
               opcode_str_table ().c_str ());
}
