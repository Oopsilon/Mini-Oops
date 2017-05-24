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
    symbolOop r = vm.mem.lowLevelAlloc<symbolOop> (sizeof (SymbolOopDesc));
    r->set_isa (vm.mem.symbolClass ());
    init_binary_object (r->as_byteVecOop (),
                        std::vector<char> (s.begin (), s.end ()));
}