/* Oopsilon Static Compiler (Oopsilon)
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

#pragma once

#include "oops-platform/cxx.h"

#include "MethBlk.h"

namespace AST
{

struct Expr
{
    typedef std::list<Expr *> List;
};

struct IdentExpr : public Expr
{
    Symbol name;

    IdentExpr (Symbol aName) : name (aName) {}

    // Variable ** var;
};

struct LiteralExpr : public Expr
{
};

struct ReturnExpr : public Expr
{
    Expr * returnVal;

    ReturnExpr (Expr * aReturn) : returnVal (aReturn) {}
};

struct AssignExpr : public Expr
{
    IdentExpr * lval;
    Expr * rval;

    AssignExpr (IdentExpr * l, Expr * r) : lval (l), rval (r) {}
};

struct MsgExpr : public Expr
{
    Expr * rcvr;
    Symbol sel;
    Expr::List args;

    MsgExpr (Expr * aRcvr, Symbol aSel, Expr::List someArgs)
        : rcvr (aRcvr), sel (aSel), args (someArgs)
    {
    }
};

struct BlockExpr : public Expr, MethodBlockCommon
{
    /* Anco */
    BlockContext * _ctx;
    BlockContext * ctx () override { return _ctx; }

    BlockExpr (TypeExpr * retTypeRepr, Field::List someFormals,
               Field::List someTemps, Expr::List code)
        : MethodBlockCommon (retTypeRepr, someFormals, someTemps, code)
    {
    }
};
}; // namespace AST