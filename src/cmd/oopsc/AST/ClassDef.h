/* Oopsilon
 * AST: Class and method definitions.
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

namespace AST
{

struct SelectorDecl
{

    struct KeywDecl
    {
        Symbol keyw;
        Symbol argname;
    };

    enum
    {
        EUnary,
        EBinary,
        EKeyw,
    } selType;

    union {
        Symbol unary;
        struct
        {
            Symbol sel;
            Symbol argname;
        } binary;
        std::vector<KeywDecl> keywords;
    };

    SelectorDecl (Symbol anUnary) : selType (EUnary), unary (anUnary) {}
    SelectorDecl (std::pair<Symbol, Symbol> aBinary)
        : selType (EBinary), binary ({aBinary.first, aBinary.second})
    {
    }
    SelectorDecl (std::vector<KeywDecl> someKeyws)
        : selType (EKeyw), keywords (someKeyws)
    {
    }

    SelectorDecl (const SelectorDecl & copied)
    {
        selType = selType;
        if (copied.selType == EUnary)
            unary = copied.unary;
    }

    ~SelectorDecl () {}
};

struct Method
{
    bool isClass;
    SelectorDecl selector;
};

struct Class
{
    Symbol name, superName;
    Symbol::Vector nstVars, clsVars;
    std::list<Method> nstMeths, clsMeths;
};
}