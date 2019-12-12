/* Oopsilon Static Compiler (Oopsilon)
 * AST: Fields
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

#include "oops-platform/cxx.h"

#include "ast.h"

namespace AST
{

/* A field represents a declared or implied variable.
 * Classes, for example, imply the creation of a global field.
 */
struct Field : public AST
{
    typedef std::list<Field *> List;

    enum FieldType
    {
        CLASS,
        IVAR,
        CVAR,
        ARG,
        LOCAL
    } fieldType;

    TypeRepr * repr;
    Symbol name;

    Field (Symbol name) : name (name), repr (NULL) {}
    Field (Symbol name, TypeRepr * repr) : name (name), repr (repr) {}

    /* i.e. a class, or a protocol */
    virtual bool isGlobal () { return fieldType == CLASS; }

    virtual bool isClass () { return fieldType == CLASS; }

    virtual bool isIVar () { return fieldType == IVAR; }
    virtual bool isCVar () { return fieldType == CVAR; }

    virtual bool isArg () { return fieldType == ARG; }
    virtual bool isLocal () { return fieldType == LOCAL; }

    virtual void accept (Visitor & aVisitor);
};

}; // namespace AST