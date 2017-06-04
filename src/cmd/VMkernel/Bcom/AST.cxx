/* Oopsilon
 * Oops C++ Compiler (Base AST struct)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "oops-platform/cxx.h"

#include "AST.h"
#include "Defs.h"

#include "../VMkernel.h"
#include "Context.h"
#include "Expressions.h"
#include "MLIR/MLIR.h"

void AST::Program::compile ()
{
    ctx = new ProgramContext (this);
    for (auto & dir : directives)
        dir->compile (ctx);
    mlir = new MLIR::Program;
    for (auto & dir : directives)
        dir->toMLIR (mlir);
}

void AST::IdentExpr::compile (Context * ctx) { var = &ctx->lookup (name); }

void AST::AssignExpr::compile (Context * parent)
{
    lhs->compile (parent);
    rhs->compile (parent);
}

void AST::MsgExpr::compile (Context * ctx)
{
    rcvr->compile (ctx);

    if (msgType == EBin)
        bin->arg->compile (ctx);
    else if (msgType == EKeyw)
        for (auto & key : keyw->keyws)
            key.arg->compile (ctx);
}

void AST::Code::compile (Context * ctx)
{
    for (const auto expr : exprs)
        expr->compile (ctx);
    if (lastExpr)
        lastExpr->compile (ctx);
}

void AST::Block::compile (Context * parent)
{
    ctx = new BlockContext (parent, this);

    for (const auto & formal : formals)
        ctx->register_var (formal, new FormalVar);

    for (const auto & temp : temps)
        ctx->register_var (temp, new FreeVar);
    code.compile (ctx);
}

MLIR::Method * AST::Method::toMLIR (MLIR::Class * parent)
{
    bool promotedSelf     = false;
    bool promotedHeapvars = false;
    Variable::SymTab heapVars;
    std::string clsName =
        (isClass ? ctx->cls ()->name + "Meta" : ctx->cls ()->name);
    MLIR::Method * mlir =
        new MLIR::Method (clsName + "_" + selector.selName ());
    MLIR::Type * selfType = new MLIR::SelfType (clsName);

    mlir->formals.push_back (MLIR::Field (selfType, "self"));
    mlir->formals.push_back (MLIR::Field (new MLIR::CType ("SEL"), "sel"));

    for (const auto & var : ctx->vars)
    {
        if (var.second->type == Variable::EHeapVar)
            heapVars.insert (var);
    }

    if (heapVars.size ())
    {
        /* create heapvar statement */
        /* put into heapvar statement */
        dbg ("We have %d heapvars\n", heapVars.size ());
    }
}

void AST::Method::compile (Context * parent)
{
    ctx = new MethodContext (parent, this);

    ctx->register_var (Symbol::selfSymbol (), new NstVar);

    for (const auto & formal : selector.formalNames ())
        ctx->register_var (formal, new FormalVar);

    for (const auto & temp : temps)
        ctx->register_var (temp, new FreeVar);

    code.compile (ctx);
}

void AST::Class::register_vars (Context * ctx)
{
    if (super_ast)
        super_ast->register_vars (ctx);

    /* TO-DO: This certainly doesn't hold true in all cases. What about the
     * class-var v.s. ivar distinction? We need to, probably, have an Instance
     * Context and a Class Context distinct. */
    for (const auto & iv : nstVars)
        ctx->register_var (iv, new NstVar);

    for (const auto & cv : clsVars)
        ctx->register_var (cv, new NstVar);

    for (auto & m : nstMeths)
        m.compile (ctx);

    for (auto & m : clsMeths)
        m.compile (ctx);
}

void AST::Class::toMLIR (MLIR::Program * parent)
{
    mlir = new MLIR::Class;

    for (auto & m : clsMeths)
        mlir->clsMeths.push_back (m.toMLIR (mlir));
    for (auto & m : nstMeths)
        mlir->nstMeths.push_back (m.toMLIR (mlir));
}

void AST::Class::compile (Context * parent)
{
    ctx = new ClassContext (parent, this);

    bcom.notice ("Registering class %s...\n", name.c_str ());
    parent->register_var (name, new ClassVar (this));

    if (superName != "noSuper")
        super_ast = parent->lookup (superName)->asAPtr<ClassVar> ()->cls;
    else
        super_ast = NULL;

    register_vars (ctx);
}

std::string AST::SelectorDecl::selName ()
{
    std::string result;

    if (selType == EUnary)
        result = unary;
    else if (selType == EBinary)
        result = binary.sel;
    else
    {
        for (const auto & keyw : keywords)
            result += keyw.keyw;
    }

    return result;
}