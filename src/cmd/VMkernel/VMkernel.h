/* Oopsilon
 * Program definitions
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

#include <list>
#include <stack>
#include <string>

#include "Bcom/State.h"

class Oopsc
{
    friend class ParserState;
    std::string rootDir;
    std::stack<ParserState> pStateStack;
    AST::Program & program;

    ParserState & pState () { return pStateStack.top (); }

  public:
    Oopsc (std::string RootDir);
    void parse (std::string filename, bool isImported = false);
    void compile ();
};
