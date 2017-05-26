/* Oopsilon
 * oopsc Oopsilon Compiler: Parser state.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "State.h"
#include "AST.h"
#include "VMkernel.h"

void ParserState::addDirective (AST::Directive * aDir)
{
    oc.program.addDirective (aDir);
}