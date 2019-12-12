/* Oopsilon Static Compiler
 * Analyser environment
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include "Context.h"

struct Environment
{
    /* Stack of lexical contexts. */
    std::stack<Context *> ctxes;
};