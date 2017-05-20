/* Oopsilon
 * Oopslib: Compatibility functions.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#include <typeinfo>

#include "oops-platform/compats.h"

#ifdef HAVE_CXXABI_H
#include <cxxabi.h>

inline const char * demangledTypeID2 (const char * typeID)
{
    int status = 0;
    return abi::__cxa_demangle (typeID, NULL, NULL, &status);
}

#define DemangledTypeName(aType) demangledTypeID2 (typeid (aType).name ())

#else

#define DemangledTypeName(aType) typeid (aType).name ()

#endif
