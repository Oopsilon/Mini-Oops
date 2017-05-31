/* Oopsilon
 * Classgen: Oops class generator.
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

#include "Classgen.h"
#include "oops-platform/misc.h"

#include "AST.h"

std::string lower_first (std::string nam)
{
    std::string r = nam;
    r[0]          = std::tolower (r[0]);
    return r;
}

std::string oopName (std::string cls) { return lower_first (cls) + "Oop"; }
std::string className (std::string cls) { return cls + "Class"; }

std::string generate_comma_separated_fields (std::list<Field> * fields)
{
    std::string r;
    bool onFirst = true;

    for (const auto & field : *fields)
        r += (onFirst ? (onFirst = false, "") : ", ") + field.generate ();

    return r;
}

std::string Field::generate () const { return *type + " " + *name; }

std::string Method::return_type () const
{
    if (methType == EConstructor)
        return oopName (*cls->name);
    else
        return *_return_type;
}

std::string Method::generate_klass_intf () const
{
    return return_type () + " " + *name + "(classOop our_class, " +
           generate_comma_separated_fields (args) + ")";
}

std::string Method::generate_klass_impl () const
{
    std::string r = generate_klass_intf () + "\n{\n";

    if (methType == EConstructor)
        r += "    " + return_type () + " r = vm.mem.lowLevelAlloc<" +
             return_type () +
             ">(our_class->instanceSize());\n"
             "    r->basic_init();\n"
             "    r->set_isa(our_class);\n";

    r += *code;

    if (methType == EConstructor)
        r += "    return r;\n";

    return r + "}\n";
}

std::string generate_ivar_accessor (Field field)
{
    std::string r;

    r += *field.type + " " + *field.name + "() { return nstVar_at<" +
         *field.type + "> (E" + *field.name + "); }\n";

    r += "void set_" + *field.name + "(" + *field.type +
         "val) { return nstVar_at_put (E" + *field.name + ", val); }\n";

    return r;
}

std::string Class::generate_field_info () const
{
    bool onFirst = true;
    std::string r;

    r += "enum\n{\n";

    for (const auto & field : *fields)
        r += "    E" + *field.name +
             (onFirst ? (onFirst = false, " = 1") : "") + ",\n";

    r += "} Layout;\n\n";

    r += "static std::vector<std::string> & nstVarNames ()\n"
         "{\n"
         "    const char * varnames[] = {\n";

    for (const auto & field : *fields)
        r += "        \"" + *field.name + "\",\n";

    r += "    };\n"
         "    static std::vector<std::string> varnamesVec = "
         " std::vector<std::string> (\n"
         "            std::begin (varnames), std::end (varnames));\n"
         "        return varnamesVec;\n"
         "}\n\n";

    for (const auto & field : *fields)
        r += generate_ivar_accessor (field) + "\n";

    return r + "\n";
}

void Class::generate ()
{
    cg.notice ("Compiling class definition for " BLDTEXT ("%s") "\n",
               name->c_str ());

    for (auto & meth : *methods)
        meth.set_class (this);

    cg.FDescH += "class " + *name + "Desc" + " : " + *superName + "Desc\n";
    cg.FDescH += "{\n";
    cg.FDescH += generate_field_info ();
    cg.FDescH += "};\n";

    printf ("<DESC HEADER>\n%s</DESC HEADER>\n", cg.FDescH.c_str ());

    printf ("<KLASS STUFF>\n");
    for (const auto & meth : *methods)
        printf ("%s\n", meth.generate_klass_impl ().c_str ());
}