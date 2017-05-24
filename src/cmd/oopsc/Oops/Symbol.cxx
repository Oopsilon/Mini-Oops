/* Oopsilon
 * Object descriptors: Symbol object
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

#include "SymbolDesc.h"

bool SymbolOopDesc::operator== (std::string aString) const
{
    return std::string (_contents.begin (), _contents.end ()) == aString;
}

bool SymbolOopDesc::operator== (const char * aString) const
{
    return std::string (_contents.begin (), _contents.end ()) == aString;
}