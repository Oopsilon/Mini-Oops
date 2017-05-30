/* Oopsilon
 * Object Factory
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

#include "Oops/Klass/ClassKlass.h"
#include "Oops/Klass/ContextKlass.h"
#include "Oops/Klass/MethodKlass.h"
#include "Oops/Klass/ObjVecKlass.h"
#include "Oops/Klass/SymbolKlass.h"

#include "ObjectFactory.inl.h"
#include "ObjectMemory.h"
#include "VM/VM.h"

byteVecOop ObjectFactory::newByteVec (std::vector<char> bytes)
{
    return ((ByteVecKlass *)vm.mem.byteVecClass ()->getKlass ())
        ->allocateByteVec (bytes);
}

symbolOop ObjectFactory::newSymbol (std::string text)
{
    return ((SymbolKlass *)vm.mem.symbolClass ()->getKlass ())
        ->allocateSymbol (text);
}

objVecOop<symbolOop>::type
ObjectFactory::newSymVec (const std::vector<std::string> contents)
{
    std::vector<symbolOop> newVec;
    objVecOop<symbolOop>::type result;

    for (const auto & str : contents)
        newVec.push_back (newSymbol (str));

    return newObjVec<symbolOop> (newVec);
}

methodOop ObjectFactory::new_method (std::string sel, size_t args, size_t temps,
                                     size_t heapvars, std::vector<oop> literals,
                                     std::vector<char> code)
{
    vm.mem.notice ("Allocating new method " BLDTEXT ("%s") "\n", sel.c_str ());
    return ((MethodKlass *)vm.mem.symbolClass ()->getKlass ())
        ->allocate_method (vm.mem.factory.newSymbol (sel), args, temps,
                           heapvars, vm.mem.factory.newObjVec (literals),
                           vm.mem.factory.newByteVec (code));
}