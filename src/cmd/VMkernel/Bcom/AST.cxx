/* Oopsilon
 * Oops C++ Compiler (Base AST struct)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "oops-platform/cxx.h"

#include "AST.h"
#include "Defs.h"

#include "VM/VM.h"

void AST::Class::compile ()
{
    vm.notice ("Compiling class %s...\n", name.c_str ());
}

void AST::Method::compile ()
{
    vm.notice ("Compiling method %c %s>>%s\n", (isClass ? '+' : '-'),
               className.c_str (), selector.selName ().c_str ());
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