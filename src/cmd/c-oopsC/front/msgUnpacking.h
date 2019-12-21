/* Oopsilon
 * oopsc Oopsilon Compiler: Message unpacking.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include "ast/ast.h"
#include "ast/expr.h"
#include "ast/typeRepr.h"
#include <utility>

typedef std::pair<AST::Symbol, AST::TypeExpr *> SymTypeExprPair;

struct Msg
{
    virtual AST::Symbol sel ()      = 0;
    virtual AST::Expr::List args () = 0;
};

struct UnaryMsg : Msg
{
    typedef std::list<UnaryMsg> List;
    AST::Symbol unary;

    UnaryMsg (AST::Symbol anUnary) : unary (anUnary) {}

    AST::Symbol sel () { return unary; }
    AST::Expr::List args () { return AST::Expr::List (); }
};

struct BinMsg : Msg
{
    typedef std::list<BinMsg> List;
    AST::Symbol bin;
    AST::Expr * arg;

    BinMsg (AST::Symbol aSel, AST::Expr * anArg) : bin (aSel), arg (anArg) {}

    AST::Symbol sel () { return bin; }
    AST::Expr::List args () { return AST::Expr::List ({arg}); }
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

struct KeywMsg : Msg
{
    KeywMsgPart::List keyws;

    KeywMsg (KeywMsgPart::List someKeyws) : keyws (someKeyws) {}

    AST::Symbol sel ()
    {
        AST::Symbol r;
        for (auto keywPart : keyws)
            r += keywPart.keyw;
        return r;
    }
    AST::Expr::List args ()
    {
        AST::Expr::List a;
        for (auto keywPart : keyws)
            a.push_back (keywPart.arg);
        return a;
    }
};

struct MsgChainEntry
{
    enum
    {
        EUnary,
        EBin,
        EKeyw,
    } entryType;

    Msg * entry;

    typedef std::list<MsgChainEntry> List;

    MsgChainEntry (UnaryMsg * anUnary) : entryType (EUnary), entry (anUnary) {}
    MsgChainEntry (BinMsg * anUnary) : entryType (EBin), entry (anUnary) {}
    MsgChainEntry (KeywMsg * someKeyws) : entryType (EKeyw), entry (someKeyws)
    {
    }

    AST::Symbol sel () { return entry->sel (); }
    AST::Expr::List args () { return entry->args (); }
};

AST::MsgExpr * unpackMsgChain (AST::Expr * rcvr, MsgChainEntry::List * chain);