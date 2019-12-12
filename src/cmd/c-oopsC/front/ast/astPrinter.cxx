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

#include "ASTPrinter.h"

using namespace std;

namespace AST
{

string Printer::dashes ()
{
    std::string dashes;
    for (int i = 0; i < depth; i++)
        dashes += "-";
    return dashes;
}

void Printer::visitSymbol (Symbol & aNode) {}

/* Fields */
void Printer::visitField (Field & aNode)
{
    depth++;
    cout << dashes () + "field (name: " + aNode.name + ")\n";
    depth--;
}
/*void Printer::visitClassField (ClassField & aNode) {}
void Printer::visitIVarField (IVarField & aNode) {}
void Printer::visitCVarField (CVarField & aNode) {}
void Printer::visitArgField (ArgField & aNode) {}
void Printer::visitLocalField (LocalField & aNode) {}*/

void Printer::visitNode (AST & aNode)
{
    depth++;
    cout << dashes () + "node\n";
    depth--;
}

/* Expressions */

void Printer::visitExpr (Expr & aNode)
{
    depth++;
    cout << dashes () + "expr\n";
    depth--;
}
void Printer::visitIdentExpr (IdentExpr & aNode) {}
void Printer::visitLiteralExpr (LiteralExpr & aNode) {}
void Printer::visitReturnExpr (ReturnExpr & aNode) {}
void Printer::visitMsgExpr (MsgExpr & aNode) {}
void Printer::visitBlockExpr (BlockExpr & aNode) {}

/* Program */
void Printer::visitProgram (Program & aNode) { Visitor::visitProgram (aNode); }

/* Code */
void Printer::visitMethodBlockCommon (MethodBlockCommon & aNode) {}

/* Directives */
void Printer::visitClassLike (ClassProtocolCommon & aNode)
{

    Visitor::visitClassLike (aNode);
}
void Printer::visitClass (Class & aNode)
{
    depth++;

    cout << dashes () + "class\n";
    for (meth : aNode.clsVars)
        this->visitField (*meth);
    for (meth : aNode.nstVars)
        this->visitField (*meth);
    this->visitClassLike (dynamic_cast<ClassProtocolCommon &> (aNode));
    depth--;
}
void Printer::visitProtocol (Protocol & aNode)
{
    Visitor::visitProtocol (aNode);
}

/* Class members */
void Printer::visitMethod (Method & aNode) {}

/* Type reprs */
void Printer::visitTypeRepr (TypeRepr & aNode) {}
void Printer::visitIdTypeRepr (IdTypeRepr & aNode) {}
void Printer::visitSelfTypeRepr (SelfTypeRepr & aNode) {}
void Printer::visitInstanceTypeRepr (InstanceTypeRepr & aNode) {}
void Printer::visitClassTypeRepr (ClassTypeRepr & aNode) {}
void Printer::visitNilTypeRepr (NilTypeRepr & aNode) {}
void Printer::visitNamedTypeRepr (NamedTypeRepr & aNode) {}
void Printer::visitPlaceholderTypeRepr (PlaceholderTypeRepr & aNode) {}
void Printer::visitParameterisedTypeReprDecl (ParameterisedTypeReprDecl & aNode)
{
}
void Printer::visitTypeInvocationRepr (TypeInvocationRepr & aNode) {}
// void Printer::visitTypeProtQualRepr (TypeProtQualRepr & aNode){ }
void Printer::visitSumTypeRepr (SumTypeRepr & aNode) {}
void Printer::visitBlockTypeRepr (BlockTypeRepr & aNode) {}
} // namespace AST