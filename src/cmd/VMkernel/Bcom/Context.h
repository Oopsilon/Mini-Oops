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
     * not. */
    virtual Variable *& lookup (AST::Symbol aSym);

    /* Promotion semantics. */
    virtual void using_name_in_block (AST::Symbol aSym)
    {
        fatalError ("Should not be called on a Context that isn't a subtype of "
                    "AbstractCodeContext.\n");
    }

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

struct BlockContext;

struct AbstractCodeContext : public Context
{
    virtual void using_name_in_block (AST::Symbol aSym);
    AbstractCodeContext (Context * anEnclosing) : Context (anEnclosing) {}
};

struct MethodContext : public AbstractCodeContext
{
    AST::Method * ast;

    AST::Class * cls ()
    {
        return dynamic_cast<ClassContext *> (enclosing)->ast;
    }

    MethodContext (Context * anEnclosing, AST::Method * anAst)
        : ast (anAst), AbstractCodeContext (anEnclosing)
    {
    }
};

struct BlockContext : public AbstractCodeContext
{
    AST::Block * ast;

    /* This adjusted lookup function invokes the using_name_in_block function on
     * its enclosing context if the variable referenced is not a block formal or
     * temporary. */
    Variable *& lookup (AST::Symbol aSym);

    BlockContext (Context * anEnclosing, AST::Block * anAst)
        : ast (anAst), AbstractCodeContext (anEnclosing)
    {
    }
};