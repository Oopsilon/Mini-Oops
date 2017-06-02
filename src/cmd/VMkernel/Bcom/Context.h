/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <string>
#include <vector>

#include "AST.h"
#include "Variable.h"

struct Context
{
    Context * enclosing;
    Variable::SymTab vars;

    Variable * lookup (AST::Symbol aSym);

    void register_var (AST::Symbol name, Variable * var) { vars[name] = var; }

    Context (Context * anEnclosing) : enclosing (anEnclosing) {}
};

struct ProgramContext : public Context
{
    AST::Program * ast;
    ProgramContext (AST::Program * anAst) : ast (anAst), Context (NULL) {}
};

/* Context of types within a class, methods within a class, etc. */
struct ClassContext : public Context
{
    AST::Class * ast;
    ClassContext (Context * anEnclosing, AST::Class * anAst)
        : ast (anAst), Context (anEnclosing)
    {
    }
};

struct AbstractCodeContext : Context
{
    AbstractCodeContext (Context * anEnclosing) : Context (anEnclosing) {}
};

struct MethodContext : AbstractCodeContext
{
    AST::Method * ast;
    MethodContext (Context * anEnclosing, AST::Method * anAst)
        : ast (anAst), AbstractCodeContext (anEnclosing)
    {
    }
};