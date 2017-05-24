/* Oopsilon
 * Object descriptors: Context object
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

#include "MemDesc.h"

class ContextDesc : public MemOopDesc
{
    /* Method being executed. */
    methodOop method;

    /* Arguments, temporary variables, and stack. */
    std::vector<oop> args;
    std::vector<oop> temps;
    std::vector<oop> stack;

    /* Program counter. */
    smiOop pc;

    /* Previous context. */
    contextOop previous;

  public:
};