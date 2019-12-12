/* Oopsilon Static Compiler (Oopsilon)
 * AST: Classes.
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

#include "clsProto.h"
#include "field.h"

namespace AST
{

struct Class : public ClassProtocolCommon
{
    TypeRepr * superRepr;

    Field::List nstVars, clsVars;

    Class (TypeDecl * decl, TypeRepr * superRepr, TypeRepr::List protoList,
           Field::List cVars, Field::List iVars, Method::List meths)
        : ClassProtocolCommon (decl, protoList, meths), superRepr (superRepr),
          nstVars (iVars), clsVars (cVars)
    {
        for (auto & var : clsVars)
            printf ("Var: %s\n", var->name.c_str ());

        for (auto & var : clsVars)
            var->fieldType = Field::CVAR;
        for (auto & var : nstVars)
            var->fieldType = Field::IVAR;
    }

    virtual void accept (Visitor & aVisitor);
};
}; // namespace AST