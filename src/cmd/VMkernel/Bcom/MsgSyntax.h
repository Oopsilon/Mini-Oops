/* Oopsilon
 * oopsc Oopsilon Compiler: Message syntax.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>

//#include "AST/MsgExpr.h"

struct MsgChainEntry
{
    enum
    {
        EUnaryMsg,
        EBinaryMsg,
        EKeywList,
    } entryType;

    /*union {
        AST::UnaryMsg * unary;
        AST::BinaryMsg * binary;
        AST::KeywMsg::List * keyws;
    };*/

    typedef std::list<MsgChainEntry> List;

    /*MsgChainEntry (AST::UnaryMsg * anUnary)
        : entryType (EUnaryMsg), unary (anUnary)
    {
    }
    MsgChainEntry (AST::KeywMsg::List * someKeyws)
        : entryType (EKeywList), keyws (someKeyws)
    {
    }*/
};

// AST::MsgExpr * unpackMsgChain (AST::Expression * rcvr,
//                               MsgChainEntry::List * chain);
