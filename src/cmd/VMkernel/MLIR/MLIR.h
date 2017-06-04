/* Oopsilon
 * MLIR: Mid-level intermediate representation.
 * This is an intermediate representation which is constructed from the AST and
 * in which variable access semantics have been made concrete rather than
 * abstract as in the AST.
 *
 * This means that, for example, access to a variable in `self` is explicitly
 * done through a SelfVarAccess operation. More importantly, heapvars (the
 * environment vectors used to implement block closure) are now made extant and
 * can therefore be reasoned about.
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

namespace MLIR
{

struct Decl;
struct Def;
struct Stmt;
struct Expr;
struct ExprStmt;

struct Type
{
    enum TypeType
    {
        ECType,
        EPointerType,
        ESelfType,
        EHeapVarType,
        EOopType,
    } type;

    Type (TypeType aType) : type (aType) {}

    virtual std::string cType () = 0;
};

struct CType : public Type
{
    std::string c_type;

    CType (std::string aCType) : c_type (aCType), Type (ECType) {}
    std::string cType () { return c_type; }
};

struct SelfType : public Type
{
    std::string priv_struct_typename;

    SelfType (std::string clsName)
        : priv_struct_typename ("T_" + clsName + "_PRIVATE"), Type (ESelfType)
    {
    }
    std::string cType () { return "struct" + priv_struct_typename; }
};

struct PointerType : public Type
{
    Type * ptrType;

    PointerType (Type * aType) : ptrType (aType), Type (EPointerType) {}
    std::string cType () { return ptrType->cType () + "*"; }
};

struct Expr
{
};

/* An access to the self struct. */
struct SelfVarExpr
{
    /* The ivar name. */
    std::string name;
};

/* An access to a heapvar struct. */
struct HeapVarAccessExpr : public Expr
{
    /* Heapvar struct identifier. */
    int id;
    /* The name of the captured variable. */
    std::string name;
};

struct AssignExpr : public Expr
{
    Expr & lhs;
    Expr & rhs;
};

struct ExprStmt
{
    Expr & expr;
};

struct Stmt
{
    typedef std::list<Stmt *> List;
};

struct Field
{
    Type * type;
    std::string name;

    Field (Type * aType, std::string aName) : type (aType), name (aName) {}
};

struct Method
{
    typedef std::list<Method *> List;

    std::string name;
    /* This must include private type, SEL. */
    std::list<Field> formals;
    Stmt::List stmts;

    Method (std::string aName) : name (aName) {}
};

struct Class
{
    Method::List clsMeths, nstMeths;
};

struct Program
{
};
};