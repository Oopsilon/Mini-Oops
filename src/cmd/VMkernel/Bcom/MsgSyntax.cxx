/* Oopsilon
 * oopsc Oopsilon Compiler: Message syntax
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "MsgSyntax.h"

AST::MsgExpr * unpackMsgChain (AST::Expr * rcvr, MsgChainEntry::List * chain)
{
    AST::Expr * result = rcvr;

    for (auto & entry : *chain)
    {
        if (entry.entryType == MsgChainEntry::EUnary)
            result = new AST::MsgExpr (result, entry.unary);
        if (entry.entryType == MsgChainEntry::EBin)
            result = new AST::MsgExpr (result, entry.bin);
        else if (entry.entryType == MsgChainEntry::EKeyw)
            result = new AST::MsgExpr (result, entry.keyw);
    }

    return static_cast<AST::MsgExpr *> (result);
}