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

#include "Oops/ContextDesc.h"
#include "Oops/Klass/ClassKlass.h"
#include "Oops/Klass/ContextKlass.h"
#include "Oops/Klass/MethodKlass.h"
#include "Oops/Klass/ObjVecKlass.h"
#include "Oops/Klass/SmiKlass.h"
#include "Oops/Klass/SymbolKlass.h"
#include "Oops/MethodDesc.h"
#include "Oops/ObjVecDesc.h"
#include "Oops/SymbolDesc.h"

#include "ObjectMemory.h"

const size_t metaClassSize = sizeof (Desc) + (sizeof (oop) * 5);

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

void ObjectMemory::setup_kernel_classes ()
{
    /* These are the essential Class objects for higher-level initialisation
     * functions to work. */
    _smiClass     = lowLevelAllocClass<SmiKlass> ();
    _booleanClass = lowLevelAllocClass<MemKlass> ();
    _trueClass    = lowLevelAllocClass<MemKlass> ();
    _falseClass   = lowLevelAllocClass<MemKlass> ();
    _objVecClass  = lowLevelAllocClass<ObjVecKlass<oop> > ();
    _byteVecClass = lowLevelAllocClass<ByteVecKlass> ();
    _symbolClass  = lowLevelAllocClass<SymbolKlass> ();

    /* We will now set up metaclass with its instance variables. */
    _objectMetaClass->initMethods ();
    _objectMetaClass->set_nstVars (
        factory.newSymVec (ClassDesc::nstVarNames ()));

    /* Now the remaining VMkernel classes. */
    notice ("Initialising kernel classes...\n");

    /* Those classes with nstVars must have those described. */
    _contextClass = lowLevelAllocClass<ContextKlass> ();
    _methodClass  = lowLevelAllocClass<MethodKlass> ();

    _contextClass->initMethods ();
    _contextClass->set_nstVars (
        factory.newSymVec (ContextDesc::nstVarNames ()));

    _methodClass->initMethods ();
    _methodClass->set_nstVars (factory.newSymVec (MethodDesc::nstVarNames ()));

    /* All classes we've created must be in a defined state - i.e. they must
     * immediately have their method and nstVar vectors allocated. */
    _objectClass->init ();
    _smiClass->init ();
    _booleanClass->init ();
    _trueClass->init ();
    _falseClass->init ();
    _objVecClass->init ();
    _byteVecClass->init ();
    _symbolClass->init ();
}

void ObjectMemory::preboot ()
{
    notice ("Using %d-bit Object-Oriented Pointers\n", sizeof (oop) * 8);
    /* Reasoning: we copy the vptr of the Klass when we subclass something.
     * Perhaps we could use a virtual function in Klass to construct a new Klass
     * for the copied object instead? That would certainly be cleaner. */
    notice ("Following sizes should be equal: %d, %d\n", sizeof (Klass),
            sizeof (ClassKlass));
    notice ("Setting up initial Object Memory...\n");

    setup_metaclass ();
    setup_kernel_classes ();

    classes["Object"]       = _objectClass;
    classes["SMI"]          = _smiClass;
    classes["Boolean"]      = _booleanClass;
    classes["True"]         = _trueClass;
    classes["False"]        = _falseClass;
    classes["Method"]       = _methodClass;
    classes["Context"]      = _contextClass;
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

classOop
ObjectMemory::findOrCreateClass (const std::string name,
                                 const std::string superName,
                                 const std::vector<std::string> clsVars,
                                 const std::vector<std::string> nstVars)
{
    classOop super         = classes[superName];
    classOop candidate     = classes[name];
    classOop candidateMeta = candidate ? candidate->isa () : classOop ();

    if (!super && superName != "noSuper")
        fatalError ("No such superclass: %s\n", superName.c_str ());

    if (!candidateMeta)
    {
        notice ("Metaclass for " BLDTEXT ("%s") " not found, creating...\n",
                name.c_str ());
        candidateMeta = lowLevelAllocClass<ClassKlass> ();
        candidateMeta->initMethods ();
    }

    if (!candidate)
    {
        /* Actually, what we really want to do is ask the superclass to
         * create a subclass here. But we will implement this behaviour later.
         */
        notice ("Class for " KBLD "%s" KNRM " not found, creating...\n",
                name.c_str ());
        candidate = lowLevelAllocClass<MemKlass> ();
        candidate->initMethods ();
    }

    candidateMeta->nstVar_at_replace (ClassDesc::EName,
                                      factory.newSymbol (name + " Metaclass"));
    candidateMeta->set_isa (_objectMetaClass);
    candidateMeta->set_superClass (super ? super->isa () : _objectClass);
    candidateMeta->nstVar_at_replace (ClassDesc::ENstVars,
                                      factory.newSymVec (clsVars));

    candidate->nstVar_at_replace (ClassDesc::EName, factory.newSymbol (name));
    candidate->set_isa (candidateMeta);
    candidate->set_superClass (super);
    candidate->nstVar_at_replace (ClassDesc::ENstVars,
                                  factory.newSymVec (nstVars));

    classes[name] = candidate;

    return candidate;
}
