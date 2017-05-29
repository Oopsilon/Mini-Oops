
#include "../Encoder.h"
#include "Oops/ClassDesc.h"

#include "../Defs.h"
#include "../Expressions.h"

#include "../../VMkernel.h"

void AST::Expr::compileInCodeContextWithEncoder (CodeContext & meth,
                                                 Encoder & enc)
{
    bcom.notice ("Compilation requested on expression <" BLDTEXT ("%s") ">\n",
                 DemangledTypeName (*this));
}

void AST::SyscallStmt::compileInCodeContextWithEncoder (CodeContext & meth,
                                                        Encoder & enc)
{
    bcom.notice ("Syscall emit\n");
    enc.emitSyscall (name);
}

void AST::Code::compileInCodeContextWithEncoder (CodeContext & meth,
                                                 Encoder & enc)
{
    for (auto & expr : exprs)
    {
        expr->compileInCodeContextWithEncoder (meth, enc);
        enc.emitPop ();
    }

    if (lastExpr)
    {
        lastExpr->compileInCodeContextWithEncoder (meth, enc);
        enc.emitReturn ();
    }
    else
        enc.emitReturnSelf ();
}
