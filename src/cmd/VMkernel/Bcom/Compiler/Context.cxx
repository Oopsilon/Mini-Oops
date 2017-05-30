/* Oopsilon
 * Lexical context handling in compilation.
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

#include "../Defs.h"
#include "../Expressions.h"

void AST::Code::synthesiseInCodeContext (CodeContext & aCCtx)
{
    for (auto & expr : exprs)
        expr->synthesiseInCodeContext (aCCtx);

    if (lastExpr)
        lastExpr->synthesiseInCodeContext (aCCtx);
}

void AST::Expr::synthesiseInCodeContext (CodeContext & aCCtx)
{
    bcom.notice ("Synthesis requested on expression <" BLDTEXT ("%s") ">\n",
                 DemangledTypeName (*this));
}

void AST::Block::synthesiseInCodeContext (CodeContext & aCCtx)
{
    cCtx.synthesiseInCodeContext (&aCCtx);
}

AST::CodeContext & AST::CodeContext::homeContext ()
{
    if (enclosingContext)
        return enclosingContext->homeContext ();
    else
        return *this;
}

void AST::CodeContext::synthesiseInCodeContext (CodeContext * aCCtx)
{
    enclosingContext = aCCtx;
    /* Are we a block? (blocks uniquely have enclosing context) */
    if (aCCtx)
    {
        /* Promote all our temporaries to the method's heap environment. */
        for (auto & temp : temps)
        {
            homeContext ().addHeapVar (temp);
        }
        temps.clear ();
    }
    code.synthesiseInCodeContext (*this);
}
