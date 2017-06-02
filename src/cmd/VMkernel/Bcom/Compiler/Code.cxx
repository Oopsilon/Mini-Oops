/* Oopsilon
 * Code generation.
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

#include "../../VMkernel.h"
#include "Oops/ClassDesc.h"
#include "VM/QuickSilverAsm.h"
#include "VM/Syscall.h"

#include "../Defs.h"
#include "../Expressions.h"

void AST::Expr::compileInCodeContextWithEncoder (CodeContext & meth,
                                                 QuickSilverAssembler & enc)
{
    bcom.notice ("Compilation requested on expression <" BLDTEXT ("%s") ">\n",
                 DemangledTypeName (*this));
}

void AST::SyscallStmt::compileInCodeContextWithEncoder (
    CodeContext & meth, QuickSilverAssembler & enc)
{
    if (name == "Isa")
        enc.EmitSyscall (EIsa);
    else
        fatalError ("Unknown syscall: %s\n", name.c_str ());
}

void AST::Code::compileInCodeContextWithEncoder (CodeContext & meth,
                                                 QuickSilverAssembler & enc)
{
    for (auto & expr : exprs)
    {
        expr->compileInCodeContextWithEncoder (meth, enc);
        enc.EmitPop ();
    }

    if (lastExpr)
    {
        lastExpr->compileInCodeContextWithEncoder (meth, enc);
        enc.EmitReturn ();
    }
    else
        enc.EmitReturnSelf ();
}
