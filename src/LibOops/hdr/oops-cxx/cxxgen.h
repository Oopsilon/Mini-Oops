/* Oopsilon
 * C++ code generation.
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

static std::string pragmaonce ("#pragma once\n");

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
        r += (onFirst ? (onFirst = false, "") : ", ") + str;

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

std::string while_do (std::string condition, std::string bod)
{
    return "while (" + condition + ")\n{\n" + bod + "\n}\n";
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

std::string write_type_to_vector (std::string artype, std::string type,
                                  std::string arg, std::string arname = "code")
{
    return "write_type_to_vector<" + artype + ", " + type + ">(" +
           comma_seq ({arname, arg}) + ")";
}

struct CXXField
{
    std::string type;
    std::string name;

    operator std::string () { return type + " " + name; }
};

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

    std::string gen_inclass_decl () const
    {
        return scnl (declare_fn (rtype, name, comma_seq (params)));
    }
    std::string gen_def () const
    {
        return nl (
            nl (declare_fn (rtype, cls + "::" + name, comma_seq (params))) +
            nl ("{") + nl (body) + nl ("}"));
    }
};

struct CXXClass
{
    std::string name;
    std::string superName;
    std::list<std::string> members;
    std::list<CXXFunction> funcs;
    std::string intf_extra;

    CXXClass (std::string aName, std::string aSuperName,
              std::list<std::string> aMembers, std::list<CXXFunction> aFuncs,
              std::string anIntf_extra = "")
        : name (aName), superName (aSuperName), members (aMembers),
          funcs (aFuncs), intf_extra (anIntf_extra)
    {
    }

    std::string gen_decl () const
    {
        std::string r;

        r += nl ("struct " + name + (superName != "" ? " : " + superName : ""));
        r += nl ("{");
        for (const auto & memb : members)
            r += scnl (memb);
        for (const auto & func : funcs)
            r += func.gen_inclass_decl ();
        r += nl (intf_extra);
        r += nl (scnl ("}"));

        return r;
    }

    std::string gen_def () const
    {
        std::string r;

        for (const auto & func : funcs)
            r += nl (func.gen_def ());

        return r;
    }
};
