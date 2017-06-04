/* Oopsilon
 * VM image builder (AST representation) declarations
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <string>
#include <vector>

#include "AST.h"
#include "Expressions.h"
#include "Variable.h"

struct Context
{
    Context * enclosing;

    /* These are the variables available in a context and to descendent
     * contexts. They reflect only the formals and temporaries within the
     * context in the case of Code Contexts, and the instance and class
     * variables for Class Contexts. */
    Variable::SymTab vars;

    /* Looks up a variable for the given name. Searches through parent contexts.
     * Returns a reference to the variable pointer if it is found, and NULL if
     * not. This function is not to be used except for the scope checking that
     * occurs in Stage 1 Semantic Analysis. (TO-CONSIDER: should it also be
     * usable after stage 2 is complete?) */
    Variable *& lookup (AST::Symbol aSym);
    /* Checks if the given variable is local to us.
     * All variables are known as local except for accesses to variables of any
     * kind within a block, other than that blocks' own formals and temporaries.
     * The purpose of this function is intended to be for the determination of
     * whether a heapvar must be created. A non-local variable must trigger the
     * allocation of a heapvar in the context to which it is local. */
    virtual bool variable_is_local (Variable * var) { return true; }

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

struct AbstractCodeContext : public Context
{
    AbstractCodeContext (Context * anEnclosing) : Context (anEnclosing) {}
};

struct MethodContext : public AbstractCodeContext
{
    AST::Method * ast;
    MethodContext (Context * anEnclosing, AST::Method * anAst)
        : ast (anAst), AbstractCodeContext (anEnclosing)
    {
    }
};

struct BlockContext : public AbstractCodeContext
{
    AST::Block * ast;

    BlockContext (Context * anEnclosing, AST::Block * anAst)
        : ast (anAst), AbstractCodeContext (anEnclosing)
    {
    }
};