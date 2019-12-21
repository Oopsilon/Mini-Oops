/* Oopsilon Static Compiler (Oopsilon)
 * AST: Visitor default methods
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

#include "visitor.h"

using namespace std;

namespace AST
{

/* Basic Node */
void Visitor::visitNode (AST & aNode) {}

/* Symbols */

void Visitor::visitSymbol (Symbol & aNode) {}

/* Fields */
void Visitor::visitField (Field & aNode) {}
/*void Visitor::visitClassField (ClassField & aNode) {}
void Visitor::visitIVarField (IVarField & aNode) {}
void Visitor::visitCVarField (CVarField & aNode) {}
void Visitor::visitArgField (ArgField & aNode) {}
void Visitor::visitLocalField (LocalField & aNode) {}*/

/* Expressions */

void Visitor::visitExpr (Expr & aNode) {}
void Visitor::visitIdentExpr (IdentExpr & aNode) {}
void Visitor::visitLiteralExpr (LiteralExpr & aNode) {}
void Visitor::visitReturnExpr (ReturnExpr & aNode) {}
void Visitor::visitMsgExpr (MsgExpr & aNode) {}
void Visitor::visitBlockExpr (BlockExpr & aNode) {}

/* Code */
void Visitor::visitMethodBlockCommon (MethodBlockCommon & aNode) {}

/* Program */
void Visitor::visitProgram (Program & aNode)
{
    for (auto d : aNode.directives)
        d->accept (*this);
}

/* Directives */
void Visitor::visitClassLike (ClassProtocolCommon & aNode)
{
    for (meth : aNode.clsMeths)
        this->visitMethod (*meth);
    for (meth : aNode.nstMeths)
        this->visitMethod (*meth);
}
void Visitor::visitClass (Class & aNode)
{
    for (meth : aNode.clsVars)
        this->visitField (*meth);
    for (meth : aNode.nstVars)
        this->visitField (*meth);
    this->visitClassLike (dynamic_cast<ClassProtocolCommon &> (aNode));
}
void Visitor::visitProtocol (Protocol & aNode)
{
    this->visitClassLike (dynamic_cast<ClassProtocolCommon &> (aNode));
}

/* Class members */
void Visitor::visitMethod (Method & aNode) {}

/* Type reprs */
/*void Visitor::visitTypeRepr (TypeRepr & aNode) {}
void Visitor::visitIdTypeRepr (IdTypeRepr & aNode) {}
void Visitor::visitSelfTypeRepr (SelfTypeRepr & aNode) {}
void Visitor::visitInstanceTypeRepr (InstanceTypeRepr & aNode) {}
void Visitor::visitClassTypeRepr (ClassTypeRepr & aNode) {}
void Visitor::visitNilTypeRepr (NilTypeRepr & aNode) {}
void Visitor::visitNamedTypeRepr (NamedTypeRepr & aNode) {}
void Visitor::visitPlaceholderTypeRepr (PlaceholderTypeRepr & aNode) {}
void Visitor::visitParameterisedTypeReprDecl (ParameterisedTypeReprDecl & aNode)
{
}
void Visitor::visitTypeInvocationRepr (TypeInvocationRepr & aNode) {}
// void Visitor::visitTypeProtQualRepr (TypeProtQualRepr & aNode){ }
void Visitor::visitSumTypeRepr (SumTypeRepr & aNode) {}
void Visitor::visitBlockTypeRepr (BlockTypeRepr & aNode) {}*/
} // namespace AST