/* Oopsilon
 * oopsc Oopsilon Compiler: Message unpacking.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include "ast/ast.h"
#include "ast/expr.h"
#include "ast/typeRepr.h"
#include <utility>

typedef std::pair<AST::Symbol, AST::TypeExpr *> SymTypeExprPair;

/* Components of a MsgAST::Expr */
struct UnaryMsg
{
    typedef std::list<UnaryMsg> List;
    AST::Symbol unary;

    UnaryMsg (AST::Symbol anUnary) : unary (anUnary) {}
};

struct BinMsg
{
    typedef std::list<BinMsg> List;
    AST::Symbol sel;
    AST::Expr * arg;
    BinMsg (AST::Symbol aSel, AST::Expr * anArg) : sel (aSel), arg (anArg) {}
};

struct KeywMsgPart
{
    typedef std::list<KeywMsgPart> List;
    AST::Symbol keyw;
    AST::Expr * arg;

    KeywMsgPart (AST::Symbol aKeyw, AST::Expr * anArg)
        : keyw (aKeyw), arg (anArg)
    {
    }
};

struct KeywMsg
{
    KeywMsgPart::List keyws;

    KeywMsg (KeywMsgPart::List someKeyws) : keyws (someKeyws) {}
};

struct MsgChainEntry
{
    enum
    {
        EUnary,
        EBin,
        EKeyw,
    } entryType;

    union {
        UnaryMsg * unary;
        BinMsg * bin;
        KeywMsg * keyw;
    };

    typedef std::list<MsgChainEntry> List;

    MsgChainEntry (UnaryMsg * anUnary) : entryType (EUnary), unary (anUnary) {}
    MsgChainEntry (BinMsg * anUnary) : entryType (EBin), bin (anUnary) {}
    MsgChainEntry (KeywMsg * someKeyws) : entryType (EKeyw), keyw (someKeyws) {}
};

AST::MsgExpr * unpackMsgChain (AST::Expr * rcvr, MsgChainEntry::List * chain);