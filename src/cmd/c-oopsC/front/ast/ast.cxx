/* Oopsilon Static Compiler (Oopsilon)
 * AST: Printing visitor implementation
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

#include "ast.h"
#include "class.h"
#include "protocol.h"
#include "visitor.h"

namespace AST
{

void Program::accept (Visitor & aVisitor) { aVisitor.visitProgram (*this); }

void Protocol::accept (Visitor & aVisitor) { aVisitor.visitProtocol (*this); }
void Class::accept (Visitor & aVisitor) { aVisitor.visitClass (*this); }

} // namespace AST