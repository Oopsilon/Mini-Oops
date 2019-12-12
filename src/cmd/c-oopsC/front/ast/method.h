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

#include "expr.h"

namespace AST
{

struct Method : public MethodBlockCommon
{
    typedef std::list<Method *> List;

    /* Syntax */
    enum
    {
        ECls,
        ENst,
    } kind;

    /* Anco */
    MethodContext * _ctx;
    MethodContext * ctx () override { return _ctx; }

    Method (bool isCls, TypeRepr * retTypeRepr, Symbol name,
            Field::List formals, Field::List temps, Expr::List code)
        : kind (isCls ? ECls : ENst),
          MethodBlockCommon (retTypeRepr, formals, {}, {})
    {
    }
};
};