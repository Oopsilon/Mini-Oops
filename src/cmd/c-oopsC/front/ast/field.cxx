/* Oopsilon Static Compiler (Oopsilon)
 * AST: Fields implementation
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

#include <iostream>

#include "field.h"
#include "visitor.h"

namespace AST
{

void Field::accept (Visitor & aVisitor) { aVisitor.visitField (*this); }

} // namespace AST