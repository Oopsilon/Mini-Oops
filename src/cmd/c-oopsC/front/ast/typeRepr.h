/* Oopsilon
 * AST: Types.
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

#include "AST.h"

namespace AST
{

/* Abstract superclass. */
struct TypeRepr
{
    typedef std::list<TypeRepr *> List;
};

template <class T> struct Singleton
{
    static T * instance ()
    {
        static T instance;
        return &instance;
    }
};

/* Any-object reference. */
struct IdTypeRepr : TypeRepr, Singleton<IdTypeRepr>
{
};

/* A pseudo-type referring to the type of self in this context.
 * Equivalent to ClassType if the context is a class method; otherwise, to
 * InstanceType. */
struct SelfTypeRepr : TypeRepr, Singleton<SelfTypeRepr>
{
};

/* A pseudo-type referring to the instance type of the current type. */
struct InstanceTypeRepr : TypeRepr, Singleton<InstanceTypeRepr>
{
};

/* A pseudo-type referring to the instance type of the current type. */
struct ClassTypeRepr : TypeRepr, Singleton<ClassTypeRepr>
{
};

struct NilTypeRepr : TypeRepr, Singleton<NilTypeRepr>
{
};

struct NamedTypeRepr : TypeRepr
{
    Symbol name;

    NamedTypeRepr (Symbol aName) : name (aName) {}
};

struct PlaceholderTypeRepr : NamedTypeRepr, Singleton<PlaceholderTypeRepr>
{
    PlaceholderTypeRepr () : NamedTypeRepr (std::string ("Placeholder!")) {}
};

/* type is set afterwards. */
struct ParameterisedTypeReprDecl : TypeRepr
{
    TypeRepr * type;
    /* Map of keyword entries to names (i.e. arg: T) */
    Symbol::List paramNames;

    ParameterisedTypeReprDecl (Symbol::List aNames) : paramNames (aNames) {}
};

struct TypeInvocationRepr : TypeRepr
{
    TypeRepr * base;
    TypeRepr::List params;

    TypeInvocationRepr (TypeRepr * base, TypeRepr::List params)
        : base (base), params (params)
    {
    }
};

struct ProtQualTypeRepr : TypeRepr
{
    TypeRepr * base;
    TypeRepr::List prots;

    ProtQualTypeRepr (TypeRepr * base, TypeRepr::List prots)
        : base (base), prots (prots)
    {
    }
};

struct SumTypeRepr : TypeRepr
{
    TypeRepr * lhs;
    TypeRepr * rhs;

    SumTypeRepr (TypeRepr * anLhs, TypeRepr * anRhs) : lhs (anLhs), rhs (anRhs)
    {
    }
};

struct BlockTypeRepr : TypeRepr
{
    TypeRepr * ret;
    TypeRepr::List formals;

    BlockTypeRepr (TypeRepr * ret, TypeRepr::List formals)
        : ret (ret), formals (formals)
    {
    }
};
};