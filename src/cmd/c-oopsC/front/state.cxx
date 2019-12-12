/* Oopsilon
 * oopsc Oopsilon Compiler: Parser state.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "state.h"
#include "AST/AST.h"
#include "OopsC.h"

void ParserState::addDirective (AST::Directive * aDir)
{
    oc.program.addDirective (aDir);
}