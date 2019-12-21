/* Oopsilon
 * oopsc Oopsilon Compiler: Message syntax
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "msgUnpacking.h"

AST::MsgExpr * unpackMsgChain (AST::Expr * rcvr, MsgChainEntry::List * chain)
{
    AST::Expr * result = rcvr;

    for (auto & entry : *chain)
        result = new AST::MsgExpr (result, entry.sel (), entry.args ());

    return static_cast<AST::MsgExpr *> (result);
}
