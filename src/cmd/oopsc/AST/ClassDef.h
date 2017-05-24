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

struct Selector
{

    struct Keyw
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
        std::vector<Keyw> keywords;
    };
};

struct Method
{
    Symbol selector;
    Symbol args;
};

struct Class
{
    Symbol name, superName;
    Symbol::Vector nstVars, clsVars;
    std::list<Method> nstMeths, clsMeths;
};
}