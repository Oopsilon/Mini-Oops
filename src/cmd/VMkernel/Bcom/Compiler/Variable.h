/* Oopsilon
 * Variable access.
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

#include <memory>

struct Variable
{
    typedef std::shared_ptr<Variable> Ptr;

    enum Type
    {
        EGlobal,
        ENstVar,
        EFreeVar,
        EHeapVar,
    } type;

    Variable (Type aType) : type (aType) {}
};

struct FreeVariable : public Variable
{
    /* Offset into the free variables list. */
    size_t index;

    FreeVariable (size_t anIndex) : index (anIndex), Variable (EFreeVar) {}
};

struct HeapVariable : public Variable
{
    /* Offset into the context in which this variable is stored. */
    size_t index;

    HeapVariable (size_t anIndex) : index (anIndex), Variable (EHeapVar) {}
};