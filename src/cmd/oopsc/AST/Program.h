/* Oopsilon
 * oopsc Oopsilon Compiler: Program AST representation
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <memory>

#include "AST.h"

namespace AST
{

struct Program : public AST
{
    AST::List directives;

    void addDirective (AST * aDir) { directives.push_back (aDir); }
};
}
