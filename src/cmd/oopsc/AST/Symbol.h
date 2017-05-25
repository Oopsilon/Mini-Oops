/* Oopsilon
 * Oops C++ Compiler (Lexer symbols)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <vector>

#include "ANSYN/State.h"
#include "AST.h"

namespace AST
{

struct Symbol : public AST, public string
{
    typedef std::vector<Symbol> Vector;
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
};