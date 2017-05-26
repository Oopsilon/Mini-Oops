/* Oopsilon
 * oopsc Oopsilon Compiler: Message syntax.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>

#include "Expressions.h"

struct MsgChainEntry
{
    enum
    {
        EUnary,
        EBin,
        EKeyw,
    } entryType;

    union {
        AST::UnaryMsg * unary;
        AST::BinMsg * bin;
        AST::KeywMsg * keyw;
    };

    typedef std::list<MsgChainEntry> List;

    MsgChainEntry (AST::UnaryMsg * anUnary)
        : entryType (EUnary), unary (anUnary)
    {
    }
    MsgChainEntry (AST::BinMsg * anUnary) : entryType (EBin), bin (anUnary) {}
    MsgChainEntry (AST::KeywMsg * someKeyws)
        : entryType (EKeyw), keyw (someKeyws)
    {
    }
};

AST::MsgExpr * unpackMsgChain (AST::Expr * rcvr, MsgChainEntry::List * chain);
