/* Oopsilon
 * Object descriptors: Class object
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

#include "Klass/Klass.h"
#include "MemDesc.h"

/* Memory layout:
 * X -> oop isa
 * 1 -> Klass * klass
 * 2 -> symbolOop name
 * 3 -> classOop super
 * 4 -> objVecOop<symbolOop> nstVars
 * 5 -> objVecOop<methOop> methods
 */
class ClassOopDesc : public MemOopDesc
{
    enum
    {
        EKlass = 1,
        EName,
        ESuper,
        ENstVars,
        EMethods,
    } Layout;

  public:
    /* These is a non-standard setter because it doesn't involve an Oops.
     * A Klass' lifetime is the lifetime of the ClassDesc it belongs to. */
    inline Klass * getKlass () { return nstVar_at<Klass *> (EKlass); }
    inline void setKlass (Klass * newKlass)
    {
        nstVar_at_put<Klass *> (EKlass, newKlass);
    }

    inline void init () { getKlass ()->init (this); }

    classOop superClass (oop anObj) { return nstVar_at<classOop> (ESuper); }
    void set_superClass (classOop newSuper)
    {
        nstVar_at_put<classOop> (ESuper, newSuper);
    }

    inline objVecOop<symbolOop>::type nstVars ()
    {
        return nstVar_at<objVecOop<symbolOop>::type> (ENstVars);
    }
    inline void set_nstVars (objVecOop<symbolOop>::type newNstVars)
    {
        nstVar_at_put (ENstVars, newNstVars);
    }

    inline size_t instanceSize () { return getKlass ()->instanceSize (this); }
};