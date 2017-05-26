/* Oopsilon
 * Object Memory: Object factory inline routines.
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

#include "Oops/Klass/ObjVecKlass.h"
#include "Oops/Klass/ObjVecKlass.inl.h"
#include "Oops/Klass/SymbolKlass.h"
#include "VM/VM.h"

#include "ObjectFactory.h"

symbolOop ObjectFactory::newSymbol (std::string text)
{
    return ((SymbolKlass *)vm.mem.symbolClass ()->getKlass ())
        ->allocateSymbol (text);
}

template <class T> typename objVecOop<T>::type ObjectFactory::newObjVec ()
{
    return ((ObjVecKlass<T> *)vm.mem.objVecClass ()->getKlass ())
        ->allocateObjVec ();
}

template <class T>
typename objVecOop<T>::type ObjectFactory::newObjVec (std::vector<T> contents)
{
    typename objVecOop<T>::type result =
        ((ObjVecKlass<T> *)vm.mem.objVecClass ()->getKlass ())
            ->allocateObjVec ();
    result->set_contents (contents);
    return result;
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
