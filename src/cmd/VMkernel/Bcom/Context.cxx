/* Oopsilon
 * oopsc Oopsilon Compiler: Parser state.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include "Context.h"

Variable *& Context::lookup (AST::Symbol aSym)
{
    if (vars.find (aSym) != vars.end ())
        return vars[aSym];
    else if (enclosing)
        return enclosing->lookup (aSym);
    else
        fatalError ("Couldn't resolve symbol %s\n", aSym.c_str ());
}

Variable *& BlockContext::lookup (AST::Symbol aSym)
{
    if (vars.find (aSym) == vars.end ())
        /* Variable is not a block formal or parameter. */
        enclosing->using_name_in_block (aSym);
    return Context::lookup (aSym);
}

void AbstractCodeContext::using_name_in_block (AST::Symbol aSym)
{
    bool isOurs;
    Variable::SymTab::iterator candidate;
    if ((isOurs = (candidate = vars.find (aSym)) != vars.end ()) &&
        candidate->second->type != Variable::EHeapVar)
        vars[aSym] = new HeapVar (vars[aSym]);
    else if (!isOurs)
        /* Variable isn't one of our formals or temporaries.
         * We must therefore create a new heapvar locally. */
        vars[aSym] = new HeapVar (lookup (aSym));
    /* If neither of these cases holds true then the variable is already a
     * heapvar. */
}
