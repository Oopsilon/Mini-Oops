/* Oopsilon Static Compiler
 * Denot access.
 *
 *      Copyright Notice
 *
 * Copyright (c) 2017 D. Mackay. All rights reserved.
 *
 * This file and its contents are supplied under the terms of the Peer
 * Production Licence as found in the Oopsilon project's source repository,
 * and David Mackay is the sole copyright holder.
 *
 *      End Copyright Notice
 */

#pragma once

#include <map>
#include <memory>
#include <string>

#include "oops-platform/cxx.h"

#include "front/ast/ast.h"
#include "front/ast/field.h"

/* A Denot[ation] represents a meaning for something that may be referenced. */

struct Denot : public Object
{
    typedef std::map<AST::Symbol, Denot *> SymTab;

  public:
    enum Kind
    {
        EGlobalVar,
        ESelfVar,
        EClsVar,
        ENstVar,
        EArgVar,
        ELocalVar,
    } kind;

    AST::Field * field;

    Denot (Kind varType, AST::Field * name) : kind (varType), field (name) {}
};

/* A global var is a global-scope class object. */
struct GlobalDenot : public Denot
{

    GlobalDenot (AST::Field * aName) : Denot (EGlobalVar, aName) {}
};

struct SelfDenot : public Denot
{
    /* TO-DO: Change this. Don't make a new Field! */
    /*SelfDenot ()
        : Denot (ESelfVar, new AST::Field (new AST::NamedTypeRepr (
                                                  AST::Symbol::selfSymbol ()),
                                              AST::Symbol ("self")))
    {
    }*/
};

struct ClsDenot : public Denot
{
    ClsDenot (AST::Field * aName) : Denot (EClsVar, aName) {}
};

struct NstDenot : public Denot
{
    NstDenot (AST::Field * aName) : Denot (ENstVar, aName) {}
};

struct ArgDenot : public Denot
{
    ArgDenot (AST::Field * aName) : Denot (EArgVar, aName)
    {
        dbg ("New ArgDenot: %p %s\n", this, aName->name.c_str ());
    }
};

struct LocalDenot : public Denot
{
    LocalDenot (AST::Field * aName) : Denot (ELocalVar, aName) {}
};