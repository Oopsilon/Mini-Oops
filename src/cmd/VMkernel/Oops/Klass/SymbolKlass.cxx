/* Oopsilon
 * Klasses: Klass type for Symbol objects.
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

#include "VM/VM.h"

#include "../SymbolDesc.h"
#include "SymbolKlass.h"

symbolOop SymbolKlass::allocateSymbol (std::string s)
{
    symbolOop r = vm.mem.lowLevelAlloc<symbolOop> (sizeof (SymbolDesc));
    r->basic_init ();
    r->set_isa (vm.mem.symbolClass ());
    init_binary_object (r->as_byteVecOop (),
                        std::vector<char> (s.begin (), s.end ()));
    return r;
}

std::string SymbolKlass::describe (oop o)
{
    symbolOop s = o.cast<symbolOop> ();
    return "<Symbol: " +
           std::string (s->contents ().data (), s->contents ().size ()) + ">";
}