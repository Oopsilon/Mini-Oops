/* Oopsilon
 * AST: Expressions
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

#include "AST.h"

namespace AST
{

struct Expr
{
};

struct IdentExpr
{
    Symbol name;

    IdentExpr (Symbol aName) : name (aName) {}
};

/* Components of a MsgExpr */
struct UnaryMsg
{
    typedef std::list<UnaryMsg> List;
    Symbol unary;

    UnaryMsg (Symbol anUnary) : unary (anUnary) {}
};

struct BinMsg
{
    typedef std::list<BinMsg> List;
    Symbol sel;
    Expr * arg;
    BinMsg (Symbol aSel, Expr * anArg) : sel (aSel), arg (anArg) {}
};

struct KeywMsgPart
{
    typedef std::list<KeywMsgPart> List;
    Symbol keyw;
    Expr * arg;

    KeywMsgPart (Symbol aKeyw, Expr * anArg) : keyw (aKeyw), arg (anArg) {}
};

struct KeywMsg
{
    KeywMsgPart::List keyws;

    KeywMsg (KeywMsgPart::List someKeyws) : keyws (someKeyws) {}
};

/* The actual Msg expression. */

struct MsgExpr : public Expr
{
    Expr * rcvr;

    enum
    {
        EUnary,
        EBin,
        EKeyw,
    } msgType;

    union {
        UnaryMsg * unary;
        BinMsg * bin;
        KeywMsg * keyw;
    };

    MsgExpr (Expr * aRcvr, UnaryMsg * msg)
        : rcvr (aRcvr), msgType (EUnary), unary (msg)
    {
    }
    MsgExpr (Expr * aRcvr, BinMsg * msg)
        : rcvr (aRcvr), msgType (EBin), bin (msg)
    {
    }
    MsgExpr (Expr * aRcvr, KeywMsg * msg)
        : rcvr (aRcvr), msgType (EKeyw), keyw (msg)
    {
    }
};
};