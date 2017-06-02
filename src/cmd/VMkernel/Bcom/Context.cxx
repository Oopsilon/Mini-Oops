/* Oopsilon
 * oopsc Oopsilon Compiler: Parser state.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "Context.h"

Variable * Context::lookup (AST::Symbol aSym)
{
    if (vars.find (aSym) != vars.end ())
        return vars[aSym];
    else if (enclosing)
        return enclosing->lookup (aSym);
    else
        fatalError ("Couldn't resolve symbol %s\n", aSym.c_str ());
}
