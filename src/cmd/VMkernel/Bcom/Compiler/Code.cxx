
#include "../Encoder.h"
#include "Oops/ClassDesc.h"

#include "../Defs.h"
#include "../Expressions.h"

#include "../../VMkernel.h"

void AST::Expr::compileInMethodWithEncoder (Method & meth, Encoder & enc)
{
    bcom.notice ("Compilation requested on expression <" BLDTEXT ("%s") ">\n",
                 DemangledTypeName (*this));
}

void AST::SyscallStmt::compileInMethodWithEncoder (Method & meth, Encoder & enc)
{
    bcom.notice ("Syscall emit\n");
    enc.emitSyscall (name);
}

void AST::Code::compileInMethodWithEncoder (Method & meth, Encoder & enc)
{
    for (auto & expr : exprs)
    {
        expr->compileInMethodWithEncoder (meth, enc);
        enc.emitPop ();
    }

    if (lastExpr)
    {
        lastExpr->compileInMethodWithEncoder (meth, enc);
        enc.emitReturn ();
    }
    else
        enc.emitReturnSelf ();
}
