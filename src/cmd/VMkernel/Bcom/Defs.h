/* Oopsilon
 * AST: Definitions
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

#include "Oops/Hierarchy.h"

class Encoder;

namespace AST
{

struct Expr;
struct Method;

struct Code
{
    std::list<Expr *> exprs;
    Expr * lastExpr;

    Code (std::list<Expr *> someExprs, Expr * theLast = NULL)
        : exprs (someExprs), lastExpr (theLast)
    {
    }

    void compileInMethodWithEncoder (Method & meth, Encoder & enc);
};

struct SelectorDecl
{

    struct KeywDecl
    {
        Symbol keyw;
        Symbol argname;
    };

    enum
    {
        EUnary,
        EBinary,
        EKeyw,
    } selType;

    Symbol unary;
    struct
    {
        Symbol sel;
        Symbol argname;
    } binary;
    std::vector<KeywDecl> keywords;

  public:
    SelectorDecl () : selType (EUnary), unary ("Invalid Selector") {}

    SelectorDecl (Symbol anUnary) : selType (EUnary), unary (anUnary) {}
    SelectorDecl (std::pair<Symbol, Symbol> aBinary)
        : selType (EBinary), binary ({aBinary.first, aBinary.second})
    {
    }
    SelectorDecl (std::vector<KeywDecl> someKeyws)
        : selType (EKeyw), keywords (someKeyws)
    {
    }

    std::string selName ();
};

struct Method : public Directive
{
    bool isClass;
    Symbol className;
    SelectorDecl selector;
    Symbol::List temps;
    Code code;

    Method (bool aBool, Symbol aName, SelectorDecl aSel, Symbol::List someTemps,
            Code aCode)
        : isClass (aBool), className (aName), selector (aSel),
          temps (someTemps), code (aCode)
    {
    }

    void compile ();
};

struct Class : public Directive
{
    Symbol name, superName;
    Symbol::List nstVars, clsVars;

    Class (Symbol aName, Symbol aSuper, Symbol::List someNstVars,
           Symbol::List someClsVars)
        : name (aName), superName (aSuper), nstVars (someNstVars),
          clsVars (someClsVars)
    {
    }

    void compile ();
};
}