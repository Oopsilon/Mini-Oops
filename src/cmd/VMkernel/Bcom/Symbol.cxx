/* Oopsilon
 * Oops C++ Compiler (Lexer symbols)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "AST.h"

AST::Symbol::Symbol (string str) : symType (ESymLiteral), string (str) {}

AST::Symbol & AST::Symbol::oopSymbol ()
{
    static Symbol sym = (Symbol ("oop"));
    return sym;
}

AST::Symbol::Symbol (ParserState * pS)
    : lineInfo (pS->lineInfo ()), AST (), string ()
{
}

void AST::Symbol::print () { printf ("<Symbol: %s>", c_str ()); }