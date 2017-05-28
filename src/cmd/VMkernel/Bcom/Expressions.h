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

#pragma once

#include "AST.h"
#include "Defs.h"

namespace AST
{

struct Expr
{
    typedef std::list<Expr *> List;

    virtual void compileInMethodWithEncoder (Method & aMeth);
};

struct IdentExpr : public Expr
{
    Symbol name;

    IdentExpr (Symbol aName) : name (aName) {}

  private:
    enum
    {
        ENstVar,
        ETemp,
        EClassName,
    } Type;
};

struct LiteralExpr : public Expr
{
    Symbol value;

    LiteralExpr (Symbol aVal) : value (aVal) {}
};

struct AssignExpr : public Expr
{
    Expr *lhs, *rhs;

    AssignExpr (Expr * anLhs, Expr * anRhs) : lhs (anLhs), rhs (anRhs) {}
};

struct SyscallStmt : public Expr
{
    Symbol syscall;

    SyscallStmt (Symbol aSyscall) : syscall (aSyscall) {}
};

struct ReturnStmt : public Expr
{
    Expr * returnVal;

    ReturnStmt (Expr * aReturn = NULL) : returnVal (aReturn) {}
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

struct Block : public Expr
{
    Symbol::List formals;
    Symbol::List temps;
    Code code;

    Block (Symbol::List someFormals, Symbol::List someTemps, Code aCode)
        : formals (someFormals), temps (someTemps), code (aCode)
    {
    }
};
};