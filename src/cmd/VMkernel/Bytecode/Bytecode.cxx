/* Oopsilon
 * Bytecode: Bytecode functions.
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

#include "Bytecode.h"

int Bytecode::numOfArgs (type anOp)
{
    switch (anOp)
    {
    case EPop:
    case EReturn:
    case EReturnSelf:
    case EPushTrue:
    case EPushFalse:
    case EPushNil:
    case EPushSelf: return 0;

    default: return 1;
    }
}

void Bytecode::disassemble (std::vector<type> code)
{
    std::vector<type>::iterator it = code.begin ();

    while (it != code.end ())
    {
    }
}