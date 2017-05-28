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

namespace AST
{

struct Literal;

struct AST
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
};

struct Directive
{
    typedef std::list<Directive *> List;
    virtual void compile () { dbg ("Unknown compile request\n"); }
};

struct Program : public AST
{
    Directive::List directives;

    void addDirective (Directive * aDir) { directives.push_back (aDir); }
    void compile ()
    {
        for (auto & directive : directives)
            directive->compile ();
    }
};
}
