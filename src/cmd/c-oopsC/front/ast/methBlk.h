/* Oopsilon Static Compiler (Oopsilon)
 * AST: Common Method/Block structure.
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

#include "TypeRepr.h"

#include "Anco/Context.h"

namespace AST
{

class Expr;

struct MethodBlockCommon : public AST
{
    TypeRepr * retTypeRepr;
    Field::List formals;
    Field::List temps;
    std::list<Expr *> code;

    /* Anco */
    virtual CodeContext * ctx () = 0;

    MethodBlockCommon (TypeRepr * retTypeRepr, Field::List formals,
                       Field::List temps, std::list<Expr *> code)
        : formals (formals), temps (temps), code (code)
    {
    }
};
};