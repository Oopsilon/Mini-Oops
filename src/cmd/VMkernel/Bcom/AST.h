/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <string>
#include <vector>

#include "oops-cxx/Object.h"

#include "oops-platform/compats.h"
#include "oops-platform/misc.h"

#include "State.h"

struct Context;
struct ProgramContext;
struct ClassContext;
struct MethodContext;

namespace AST
{

struct Literal;
struct Expr;

typedef struct std::list<class Method> MethodList;

struct AST : public Object
{
};

struct Symbol : public AST, public string
{
    typedef std::list<Symbol> List;

    static std::vector<std::string> listAsStringVec (List aList)
    {
        std::vector<std::string> r;
        for (auto & sym : aList)
            r.push_back (sym);
        return r;
    }

    enum
    {
        ESymLiteral,
        EStringLiteral,
    } symType;
    LineInfo lineInfo;

    /* Special constructor used for basic symbols */
    Symbol (string);

  public:
    static Symbol & oopSymbol ();

    Symbol ()
        : symType (ESymLiteral), lineInfo (9999, 9999),
          string ("<INVALID SYMBOL>")
    {
    }
    Symbol (ParserState * pS);

    void print ();

    void setSymLiteral () { symType = ESymLiteral; }
    void setStringLiteral () { symType = EStringLiteral; }
    void setCQuoteLiteral () { symType = EStringLiteral; }
};

struct Directive
{
    typedef std::list<Directive *> List;
    virtual void compile (Context * parent)
    {
        dbg ("Unknown compile request\n");
    }
};

struct Program : public AST
{
    Directive::List directives;

    ProgramContext * ctx;

    void addDirective (Directive * aDir) { directives.push_back (aDir); }
    void compile ();
};

struct Code
{
    std::list<Expr *> exprs;
    Expr * lastExpr;

    void compile (Context * ctx);

    Code (std::list<Expr *> someExprs, Expr * theLast = NULL)
        : exprs (someExprs), lastExpr (theLast)
    {
    }
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

struct Method : public Directive
{
    bool isClass;
    SelectorDecl selector;
    Symbol::List temps;
    Code code;

    MethodContext * ctx;

    void compile (Context * parent);

    Method (bool aBool, SelectorDecl aSel, Symbol::List someTemps, Code aCode)
        : isClass (aBool), selector (aSel), temps (someTemps), code (aCode)
    {
    }
};

struct Class : public Directive
{
  protected:
    void register_vars (Context * ctx);

  public:
    Symbol name, superName;
    Symbol::List nstVars, clsVars;
    MethodList nstMeths, clsMeths;

    ClassContext * ctx;
    Class * super_ast;

    void compile (Context * parent);

    Class (Symbol aName, Symbol aSuper, Symbol::List someNstVars,
           Symbol::List someClsVars, MethodList methods)
        : name (aName), superName (aSuper), nstVars (someNstVars),
          clsVars (someClsVars)
    {
        for (auto & meth : methods)
            (meth.isClass ? clsMeths : nstMeths).push_back (meth);
    }
};
}
