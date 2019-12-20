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
 *
 * Oopsilon's type system is conceived of as an object language. We have type
 * expressions which work with type objects - type objects can be types, type
 * classes (which have their constructors), or arrays of types.
 *
 * Accordingly what we call a 'type' has greater meaning than it sounds.
 */

#pragma once

#include "oops-platform/cxx.h"

#include "AST.h"

namespace AST
{

struct TypeObject
{
};

struct TypeExpr
{
    typedef std::list<TypeExpr *> List;

    virtual bool isConcreteType () { return isId (); }
    virtual bool isId () { return false; }
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
struct IdTypeExpr : TypeExpr, Singleton<IdTypeExpr>
{
    virtual bool isId () { return true; }
};

/* A pseudo-type referring to the type of self in this context.
 * Equivalent to ClassType if the context is a class method; otherwise, to
 * InstanceType. */
struct SelfTypeExpr : TypeExpr, Singleton<SelfTypeExpr>
{
};

/* A pseudo-type referring to the instance type of the current type. */
struct InstanceTypeExpr : TypeExpr, Singleton<InstanceTypeExpr>
{
};

/* A pseudo-type referring to the instance type of the current type. */
struct ClassTypeExpr : TypeExpr, Singleton<ClassTypeExpr>
{
};

struct NilTypeExpr : TypeExpr, Singleton<NilTypeExpr>
{
};

struct NamedTypeExpr : TypeExpr
{
    Symbol name;

    NamedTypeExpr (Symbol aName) : name (aName) {}
};

/* A placeholder for during inference. ( Do we need this? ) */
struct PlaceholderTypeExpr : NamedTypeExpr, Singleton<PlaceholderTypeExpr>
{
    PlaceholderTypeExpr () : NamedTypeExpr (std::string ("Placeholder!")) {}
};

struct TypeInvocationExpr : TypeExpr
{
    TypeExpr * base;
    TypeExpr::List params;
    TypeExpr::List prots;

    TypeInvocationExpr (TypeExpr * base, TypeExpr::List params,
                        TypeExpr::List prots)
        : base (base), params (params), prots (prots)
    {
    }
};

/* struct SumTypeExpr : TypeWxpr
{
    TypeExpr * lhs;
    TypeExpr * rhs;

    SumTypeExpr (TypeExpr * anLhs, TypeExpr * anRhs) : lhs (anLhs), rhs (anRhs)
    {
    }
};

struct BlockTypeExpr : TypeExpr
{
    TypeExpr * ret;
    TypeExpr::List formals;

    BlockTypeExpr (TypeExpr * ret, TypeExpr::List formals)
        : ret (ret), formals (formals)
    {
    }
}; */

/* Type Objects */

/* A type array is a literal only at the moment - so is also an expression.  */
struct TypeArray : TypeObject
{
    TypeExpr::List entries;

    TypeArray (TypeExpr::List entries) : entries (entries) {}
};

struct ParameterisedTypeConstructor : TypeObject
{
    // TypeRepr * type;
    /* Selector for its constructor. */
    Symbol constructor;
    /* list of parameter names */
    Symbol::List params;
    TypeExpr::List prots;

    ParameterisedTypeConstructor (Symbol constructor, Symbol::List params,
                                  TypeExpr::List prots)
        : constructor (constructor), params (params)
    {
    }
};

}; // namespace AST