/* Oopsilon Static Compiler (Oopsilon)
 * AST: Common Class/Protocol structure.
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

#include <algorithm>

#include "ast.h"
#include "method.h"
#include "typeRepr.h"

namespace AST
{

struct TypeDecl : public AST
{
    Symbol name;
    Field::List formals;
    TypeRepr::List protoReprs;

    TypeDecl (Symbol name, Field::List formals = {},
              TypeRepr::List protoReprs = {})
        : name (name), formals (formals), protoReprs (protoReprs)
    {
    }
};

/* abstract */
struct ClassProtocolCommon : public Directive
{
    /* Syntax */
    TypeDecl * decl;
    Method::List clsMeths, nstMeths;

    /* ANCO */
    ClassContext * _ctx;
    virtual ClassContext * ctx () { return _ctx; }

    ClassProtocolCommon (TypeDecl * decl, TypeRepr::List protoList,
                         Method::List meths)
        : decl (decl)
    {
        decl->protoReprs = protoList;
        std::copy_if (meths.begin (), meths.end (),
                      std::back_inserter (clsMeths),
                      [](Method * m) { return m->kind == Method::ECls; });
        std::copy_if (meths.begin (), meths.end (),
                      std::back_inserter (nstMeths),
                      [](Method * m) { return m->kind == Method::ENst; });
    }
};
} // namespace AST