/* Oopsilon
 * Variable access.
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

#include "AST.h"

struct Variable : public Object
{
    typedef std::map<AST::Symbol, Variable *> SymTab;
    enum Type
    {
        EClassVar,
        EClsVar,
        ENstVar,
        EFreeVar,
        EHeapVar,
    } type;

    Variable (Type aType) : type (aType) {}
};

struct ClassVar : public Variable
{
    AST::Class * cls;

    ClassVar (AST::Class * aCls) : cls (aCls), Variable (EClassVar) {}
};

struct ClsVar : public Variable
{
    ClsVar () : Variable (EClsVar) {}
};

struct NstVar : public Variable
{
    NstVar () : Variable (ENstVar) {}
};

struct FreeVar : public Variable
{
    FreeVar (size_t anIndex) : Variable (EFreeVar) {}
};

struct HeapVar : public Variable
{
    HeapVar (size_t anIndex) : Variable (EHeapVar) {}
};