/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <map>
#include <string>
#include <vector>

#include "oops-cxx/Object.h"

#include "oops-platform/compats.h"
#include "oops-platform/cxx.h"
#include "oops-platform/misc.h"

#include "front/state.h"

struct Context;
struct ProgramContext;
struct ClassContext;
struct CodeContext;
struct BlockContext;
struct MethodContext;

namespace AST
{

struct Visitor;

struct Literal;
struct Expr;
struct TypeRepr;
struct InferenceClause;
struct Protocol;
struct FunctionType;
struct TypeWithInferenceClause;

/* abstract */
struct AST : public Object
{
    virtual void accept (Visitor & aVisitor);
    virtual std::string toString () { return "<UNIMPLEMENTED>"; }
};

struct Symbol : public AST, public std::string
{
    typedef std::list<Symbol> List;
    typedef std::map<Symbol, Symbol> SymMap;

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
    Symbol (std::string);

  public:
    static Symbol & oopSymbol ();
    static Symbol & selfSymbol ();
    static Symbol & SelfSymbol ();
    static Symbol & InstanceTypeSymbol ();

    Symbol ()
        : symType (ESymLiteral),
          lineInfo (9999, 9999), std::string ("<INVALID SYMBOL>")
    {
    }
    Symbol (ParserState * pS);

    void print ();

    void setSymLiteral () { symType = ESymLiteral; }
    void setStringLiteral () { symType = EStringLiteral; }
    void setCQuoteLiteral () { symType = EStringLiteral; }
};

/* abstract */
struct Directive : public AST
{
    typedef std::list<Directive *> List;
};

struct Program : public AST
{
    Directive::List directives;

    /* ANCO */
    ProgramContext * _ctx;
    ProgramContext * ctx () { return _ctx; }

    virtual void accept (Visitor & aVisitor);

    void addDirective (Directive * aDir) { directives.push_back (aDir); }
    void compile ();
};

} // namespace AST
