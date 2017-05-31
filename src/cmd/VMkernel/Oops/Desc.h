/* Oopsilon
 * Object-oriented pointers - basic descriptor.
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

#pragma once

#include "ObjectMemory/Oop.h"

#include "Hierarchy.h"

/* An oop is the root type of any object in the Mini-Oops system.
 * It may be a MemOop (which is an allocated object) or an SmiOop (which is an
 * integer stored inline.
 *
 * The OopDesc is the actual structure. It is accessed via an Oop<someOopDesc>
 * object - the Oop acts as a handle. Note that only a MemOop is a real object.
 * SmiOops are phoneys which work by manipulating their own this-pointer. For
 * that reason they are immutable objects. */
class Desc
{
  protected:
    classOop _isa;

    void errIfSmi ()
    {
        if (is_smi ())
            fatalError ("Illegal operation on Smi\n");
    }

  public:
    classOop isa ()
    {
        return is_smi () ? /* we should return SMI class here, actually */ _isa
                         : _isa;
    }

    void set_isa (classOop newIsa)
    {
        errIfSmi ();
        _isa = newIsa;
    }

    /* Tests on type */
    bool is_smi () const { return (oop (this)).isSmiOop (); }

    /* VM use */
    /* Looks up the selector for the named method on this object. */
    methodOop lookup (std::string meth);

    /* Enquiry - despatched to Klass */
    std::string describe ();
};