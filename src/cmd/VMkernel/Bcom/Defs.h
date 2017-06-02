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

#include <map>

#include "AST.h"

#include "Compiler/Variable.h"

namespace AST
{

struct Expr;
struct Method;
struct CodeContext;



struct CodeContext
{
    /* A structure of this type is used to represent a mapping from the index
     * into a list of formals, temporaries, or literals, to an index into the
     * heapVars list of the home context. */
    typedef std::map<size_t, size_t> PromotionList;

    Symbol::List formals;
    Symbol::List temps;
    Code code;

    CodeContext * enclosingContext;
    Method * method;

    struct
    {
        /* Heap variable names. */
        Symbol::List heapVars;

        /* Variable for self. */
        Variable::Ptr selfVar;

        /* Mappings from indexes of temporaries and formals to their index in
         * the heapVars environment. On entering the method formals are put into
         * the heapvar slots associated with them. */
        PromotionList promotedFormals;
        PromotionList promotedTemps;

        /* Need to think about how these are promoted. Probably need to keep a
         * list of mappings of indexes into the heapVars to names of literals.
         */
        std::map<Symbol, Symbol> literals;
    } comp;

    CodeContext (Symbol::List someFormals, Symbol::List someTemps,
                 Code someCode, Method * someMeth)
        : formals (someFormals), temps (someTemps), code (someCode),
          enclosingContext (NULL), method (someMeth)
    {
        temps.push_front (Symbol ("self"));
        comp.selfVar = Variable::Ptr (new FreeVariable (0));
    }

    CodeContext (Symbol::List someFormals, Symbol::List someTemps,
                 Code someCode)
        : formals (someFormals), temps (someTemps), code (someCode),
          enclosingContext (NULL), method (NULL)
    {
        temps.push_front (Symbol ("self"));
        comp.selfVar = Variable::Ptr (new FreeVariable (0));
    }
};

struct Method : public Directive
{
    bool isClass;
    Symbol className;
    SelectorDecl selector;
    CodeContext cCtx;

    Method (bool aBool, Symbol aName, SelectorDecl aSel, Symbol::List someTemps,
            Code aCode)
        : isClass (aBool), className (aName), selector (aSel),
          cCtx (aSel.formalNames (), someTemps, aCode, this)
    {
    }
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
};
}