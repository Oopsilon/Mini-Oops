/* Oopsilon
 * Object Memory: the Oopsilon object-oriented memory space.
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

#include <cstdarg>
#include <type_traits>

#include "Oops/Klass/ClassKlass.h"
#include "Oops/Klass/ObjVecKlass.h"
#include "Oops/Klass/SymbolKlass.h"
#include "Oops/ObjVecDesc.h"
#include "Oops/SymbolDesc.h"

#include "ObjectMemory.h"

const size_t metaClassSize = sizeof (OopDesc) + (sizeof (oop) * 5);

template <class T> classOop ObjectMemory::lowLevelAllocClass ()
{
    classOop r;

    // static_assert (std::is_base_of <typename Oop, T>::value,
    //               "Attempted to allocate a Class without valid Klass");

    r = lowLevelAlloc<classOop> (metaClassSize);
    /* Set its Klass pointer to a new instance of the Klass T. */
    r->setKlass (new T);

    return r;
}

void ObjectMemory::notice (const char * format, ...)
{
    va_list args;
    va_start (args, format);

    printf (KMAG "ObjectMemory: " KNRM);
    vprintf (format, args);

    va_end (args);
}

/* Set up the self-referential metaclass and class structure. */
void ObjectMemory::setup_metaclass ()
{
    /* The Object Metaclass. */
    _objectMetaClass = lowLevelAllocClass<ClassKlass> ();
    _objectMetaClass->set_isa (_objectMetaClass);

    /* The Object Class: objects have Klass of type MemKlass by default. */
    _objectClass = lowLevelAllocClass<MemKlass> ();
    _objectClass->set_isa (_objectMetaClass);

    /* Set the Object Metaclass' superClass to the Object Class. */
    _objectMetaClass->set_superClass (_objectClass);
}

void ObjectMemory::setup_metaclass_layout ()
{
    std::vector<std::string> metaClassNstVarStrs = {
        "_klass_CXX", "name", "superClass", "nstVarVec", "methodVec"};
    std::vector<symbolOop> metaClassNstVars;

    /* These are the essential Class objects for higher-level initialisation
     * functions to work. */
    _objVecClass  = lowLevelAllocClass<ObjVecKlass<oop> > ();
    _byteVecClass = lowLevelAllocClass<ByteVecKlass> ();
    _symbolClass  = lowLevelAllocClass<SymbolKlass> ();

    /* We will now set up metaclass with its instance variables. */
    for (const auto & nstVarStr : metaClassNstVarStrs)
        metaClassNstVars.push_back (factory.newSymbol (nstVarStr));

    _objectMetaClass->init ();
    _objectMetaClass->nstVars ()->set_contents (metaClassNstVars);
}

void ObjectMemory::preboot ()
{
    notice ("Using %d-bit Object-Oriented Pointers\n",
            sizeof (Oop<ClassOopDesc>) * 8);
    /* Reasoning: we copy the vptr of the Klass when we subclass something.
     * Perhaps we could use a virtual function in Klass to construct a new Klass
     * for the copied object instead? That would certainly be cleaner. */
    notice ("Following sizes should be equal: %d, %d\n", sizeof (Klass),
            sizeof (ClassKlass));
    notice ("Setting up initial Object Memory...\n");

    setup_metaclass ();
    setup_metaclass_layout ();

    /* Now we can initialise all those classes. */
    notice ("Initialising kernel classes...\n");

    _objectClass->getKlass ()->init ();
    _objVecClass->getKlass ()->init ();
    _byteVecClass->getKlass ()->init ();
    _symbolClass->getKlass ()->init ();

    classes["Object"]       = _objectClass;
    classes["ObjectVector"] = _objVecClass;
    classes["Bytes"]        = _byteVecClass;
    classes["Symbol"]       = _symbolClass;

    /* Note: I'm pretty sure that, by defining the hierarchy in the kernel
     * files, we automatically patch up the class hierarchy anyway, so I don't
     * think we really need to set up all the base classes explicitly; not even
     * set up their inheritance links, it should be adequate simply to define
     * each class that has a special Klass. */

    symbolOop sym = ((SymbolKlass *)_symbolClass->getKlass ())
                        ->allocateSymbol ("Hello, world!\n");
    printf ("%s\n", sym->describe ().c_str ());

    notice ("Initial Object Memory set up.\n");
}