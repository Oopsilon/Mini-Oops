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

#include "Oops/Hierarchy.h"
#include "Oops/SymbolDesc.h"

#include "Compiler/Variable.h"

class Encoder;

namespace AST
{

struct Expr;
struct Method;
struct CodeContext;

struct Code
{
    std::list<Expr *> exprs;
    Expr * lastExpr;

    Code (std::list<Expr *> someExprs, Expr * theLast = NULL)
        : exprs (someExprs), lastExpr (theLast)
    {
    }

    void synthesiseInCodeContext (CodeContext & aCCtx);
    void compileInCodeContextWithEncoder (CodeContext & aCCtx, Encoder & enc);
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
    Symbol::List formalNames ()
    {
        Symbol::List result;
        if (selType == EBinary)
            result.push_back (binary.argname);
        if (selType == EKeyw)
            for (const auto & keyw : keywords)
                result.push_back (keyw.argname);
        return result;
    }
};

struct CodeContext
{
    /* A structure of this type is used to represent a mapping from the index
     * into a list of formals, temporaries, or literals, to an index into the
     * heapVars list of the home context. */
    typedef std::map<size_t, size_t> PromotionList;

    Symbol::List temps;
    Code code;

    CodeContext * enclosingContext;
    Method * method;

    Symbol::List formals;

    struct
    {
        /* Temps that aren't captured by-reference by a closure. Only Method
         * Contexts have these. */
        Symbol::List freeVars;
        /* Temps that should be placed into a heap-allocated Environment. only
         * method context has this. */
        Symbol::List heapVars;

        /* Mappings from indexes of temporaries and formals to their index in
         * the heapVars environment. On entering the method formals are put into
         * the heapvar slots associated with them. */
        PromotionList promotedFormals;
        /* Need to think about how these are promoted. Probably need to keep a
         * list of mappings of indexes into the heapVars to names of literals.
         */
        std::map<Symbol, oop> literals;
        std::vector<char> bytecode;
    } comp;

    CodeContext (Symbol::List someFormals, Symbol::List someTemps,
                 Code someCode, Method * someMeth)
        : formals (someFormals), temps (someTemps), code (someCode),
          enclosingContext (NULL), method (someMeth)
    {
    }

    CodeContext (Symbol::List someFormals, Symbol::List someTemps,
                 Code someCode)
        : formals (someFormals), temps (someTemps), code (someCode),
          enclosingContext (NULL), method (NULL)
    {
    }

    void synthesiseInCodeContext (CodeContext * aCtx);

    size_t addHeapVar (Symbol aVarName)
    {
        if (isMethodContext ())
        {
            comp.heapVars.push_back (aVarName);
            return comp.heapVars.size () - 1;
        }
        else
            return homeContext ().addHeapVar (aVarName);
    }
    Variable usingVarInBlock (Symbol aVarName);
    Variable variableForSymbol (Symbol aName);

    CodeContext & homeContext ();

    bool isMethodContext () { return method != 0; }
    bool isBlockContext () { return method == NULL; }
};

struct Method : public Directive
{
    bool isClass;
    Symbol className;
    SelectorDecl selector;
    CodeContext cCtx;

    /* Stuff associated with compilation. */
    struct
    {
        classOop cls;
    } comp;

    Method (bool aBool, Symbol aName, SelectorDecl aSel, Symbol::List someTemps,
            Code aCode)
        : isClass (aBool), className (aName), selector (aSel),
          cCtx (aSel.formalNames (), someTemps, aCode, this)
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