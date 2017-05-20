/* Oopsilon
 * oopsc Oopsilon Compiler: Message syntax
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "MsgSyntax.h"

/*AST::MsgExpr * unpackMsgChain (AST::Expression * rcvr,
                               MsgChainEntry::List * chain)
{
    AST::Expression * result = rcvr;

    for (auto & entry : *chain)
        if (entry.entryType == MsgChainEntry::EUnaryMsg)
            result = new AST::MsgExpr (*result, *entry.unary);
        else if (entry.entryType == MsgChainEntry::EKeywList)
            result = new AST::MsgExpr (*result, *entry.keyws);

    return dynamic_cast<AST::MsgExpr *> (result);
}*/