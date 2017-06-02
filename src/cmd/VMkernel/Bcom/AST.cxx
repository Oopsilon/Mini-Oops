/* Oopsilon
 * Oops C++ Compiler (Base AST struct)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "oops-platform/cxx.h"

#include "AST.h"
#include "Defs.h"

#include "VM/QuickSilverAsm.h"
#include "VM/QuickSilverDisasm.h"
#include "VM/Syscall.h"

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
    QuickSilverAssembler enc (cCtx.comp.bytecode);
    methodOop result;

    bcom.notice ("Compiling method " BLDTEXT ("%c %s>>%s") "\n",
                 (isClass ? '+' : '-'), className.c_str (),
                 selector.selName ().c_str ());

    comp.cls = vm.mem.findClass (className);
    if (!comp.cls)
        fatalError ("Could not find class " BLDTEXT ("%s") ".\n",
                    className.c_str ());

    if (isClass)
        comp.cls = comp.cls->isa ();
    if (!comp.cls)
        fatalError ("Could not find class " BLDTEXT ("%s Metaclass") ".\n",
                    className.c_str ());

    cCtx.synthesiseInCodeContext (NULL);

    cCtx.code.compileInCodeContextWithEncoder (cCtx, enc);

    QuickSilverDisassembler dis (cCtx.comp.bytecode);

    bcom.notice ("\n\n%s\n\n", dis.disassemble ().c_str ());

    comp.cls->add_method (vm.mem.factory.new_method (
        selector.selName (), cCtx.formals_count (), cCtx.temps_count (),
        cCtx.heapvars_count (), cCtx.literals (), cCtx.bytecode ()));
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