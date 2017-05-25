/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <string>

#include "oops-cxx/Object.h"

#include "oops-platform/compats.h"
#include "oops-platform/misc.h"

namespace AST
{

struct Literal;

struct AST
{
    typedef std::list<AST *> List;
};
}
