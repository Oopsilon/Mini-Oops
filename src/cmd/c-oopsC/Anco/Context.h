/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <string>
#include <vector>

#include "oops-cxx/optional.h"

//#include "Type.h"
#include "Denot.h"

struct Context
{
    Context * enclosing;

    /* These are the variables available in a context and to descendent
     * contexts. */
    Denot::SymTab vars;

    virtual bool isGlobalScope () { return false; }
    virtual bool isClassScope () { return false; }
    /* Block or method. */
    virtual bool isCodeScope () { return false; }
    virtual bool isBlockScope () { return false; }
    virtual bool isMethodScope () { return false; }
};

struct ProgramContext : public Context
{
    bool isGlobalScope () { return true; }
};

/* Context of types within a class, methods within a class, etc. */
struct ClassContext : public Context
{
    bool isClassScope () { return true; }
};

struct CodeContext : public Context
{
    bool isCodeScope () { return true; }
};

struct MethodContext : public CodeContext
{
    bool isMethodScope () { return true; }
};

struct BlockContext : public CodeContext
{
    bool isBlockScope () { return true; }
};