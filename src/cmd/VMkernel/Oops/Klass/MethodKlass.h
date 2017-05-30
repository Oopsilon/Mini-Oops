/* Oopsilon
 * Klasses: Klass type for Method objects.
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

#include "../Hierarchy.h"
#include "MemKlass.h"

class MethodKlass : public MemKlass
{
  public:
    methodOop allocate_method (symbolOop sel, smiOop args, smiOop temps,
                               smiOop heapvars, objVecOop<>::type literals,
                               byteVecOop code);
    methodOop allocate_method (std::string sel, size_t args, size_t temps,
                               size_t heapvars, std::vector<oop> literals,
                               std::vector<char> code);
};