/* Oopsilon Static Compiler (Oopsilon)
 * AST: Protocols.
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

#include "ClsProto.h"

namespace AST
{
struct Protocol : public ClassProtocolCommon
{
    Protocol (TypeDecl * decl, TypeRepr::List protoList, Method::List meths)
        : ClassProtocolCommon (decl, protoList, meths)
    {
    }

    virtual void accept (Visitor & aVisitor);
};
};