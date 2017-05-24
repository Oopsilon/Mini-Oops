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

symbolOop SymbolKlass::allocateSymbol (std::string text)
{
    symbolOop r = vm.mem.lowLevelAlloc<symbolOop> (sizeof (SymbolOopDesc));
}