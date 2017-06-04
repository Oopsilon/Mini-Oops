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

struct Program
{
};
};