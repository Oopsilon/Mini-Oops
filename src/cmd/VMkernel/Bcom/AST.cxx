/* Oopsilon
 * Oops C++ Compiler (Base AST struct)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "oops-platform/cxx.h"

#include "AST.h"
#include "Defs.h"
#include "Encoder.h"

#include "Bytecode/Syscall.h"

#include "VM/VM.h"

#include "../VMkernel.h"

void AST::Class::compile ()
{
    bcom.notice ("Compiling class " BLDTEXT ("%s") "...\n", name.c_str ());
    vm.mem.findOrCreateClass (name, superName,
                              Symbol::listAsStringVec (clsVars),
                              Symbol::listAsStringVec (nstVars));
}

void AST::Method::compile ()
{
    std::vector<char> bytecode;
    ::classOop cls;
    ::Encoder enc (bytecode);

    bcom.notice ("Compiling method " BLDTEXT ("%c %s>>%s") "\n",
                 (isClass ? '+' : '-'), className.c_str (),
                 selector.selName ().c_str ());

    cls = vm.mem.findClass (className);
    if (!cls)
        fatalError ("Could not find class " BLDTEXT ("%s") ".\n",
                    className.c_str ());

    if (isClass)
        cls = cls->isa ();
    if (!cls)
        fatalError ("Could not find class " BLDTEXT ("%s Metaclass") ".\n",
                    className.c_str ());

    code.compileInMethodWithEncoder (*this, enc);
}

std::string AST::SelectorDecl::selName ()
{
    std::string result;

    if (selType == EUnary)
        result = unary;
    else if (selType == EBinary)
        result = binary.sel;
    else
    {
        for (const auto & keyw : keywords)
            result += keyw.keyw;
    }

    return result;
}