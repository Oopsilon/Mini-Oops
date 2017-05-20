/* Oopsilon
 * oopsc Oopsilon Compiler: Generator interface
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <list>
#include <stack>
#include <string>

#include "ANSYN/State.h"

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
    string astGraphViz ();
    string generate ();
};
