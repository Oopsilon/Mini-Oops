/* Oopsilon
 * Oops C++ Compiler (Lexer symbols)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "ast.h"
#include "visitor.h"

namespace AST
{

void AST::accept (Visitor & aVisitor) { aVisitor.visitNode (*this); }

Symbol::Symbol (string str) : symType (ESymLiteral), string (str) {}

Symbol & Symbol::oopSymbol ()
{
    static Symbol sym = (Symbol ("oop"));
    return sym;
}

Symbol & Symbol::selfSymbol ()
{
    static Symbol sym = (Symbol ("self"));
    return sym;
}

Symbol & Symbol::SelfSymbol ()
{
    static Symbol sym = (Symbol ("Self"));
    return sym;
}

Symbol & Symbol::InstanceTypeSymbol ()
{
    static Symbol sym = (Symbol ("InstanceType"));
    return sym;
}

Symbol::Symbol (ParserState * pS)
    : lineInfo (pS->lineInfo ()), AST (), string ()
{
}

void Symbol::print () { printf ("<Symbol: %s>", c_str ()); }
}