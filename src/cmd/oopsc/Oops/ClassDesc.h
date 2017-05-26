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
class ClassDesc : public MemDesc
{
  public:
    static std::vector<std::string> & nstVarNames ()
    {
        const char * varnames[] = {"_klass_CXX", "name", "superClass",
                                   "nstVarVec", "methods"};
        static std::vector<std::string> varnamesVec = std::vector<std::string> (
            std::begin (varnames), std::end (varnames));
        return varnamesVec;
    }

    enum
    {
        EKlass = 1,
        EName,
        ESuper,
        ENstVars,
        EMethods,
    } Layout;

    /* These is a non-standard setter because it doesn't involve an Oops.
     * A Klass' lifetime is the lifetime of the ClassDesc it belongs to. */
    inline Klass * getKlass () { return nstVar_at<Klass *> (EKlass); }
    inline void setKlass (Klass * newKlass)
    {
        nstVar_at_put<Klass *> (EKlass, newKlass);
    }

    classOop superClass () { return nstVar_at<classOop> (ESuper); }
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

    inline objVecOop<methodOop>::type methods ()
    {
        return nstVar_at<objVecOop<methodOop>::type> (EMethods);
    }
    inline void set_methods (objVecOop<methodOop>::type val)
    {
        nstVar_at_put (EMethods, val);
    }

    /* Proxy functions forwarding to Klass */
    inline void init () { getKlass ()->init (this); }
    inline void initNstVars () { getKlass ()->initNstVars (this); }
    inline void initMethods () { getKlass ()->initMethods (this); }

    inline size_t instanceSize () { return getKlass ()->instanceSize (this); }
    inline size_t indexableNstVarsSize ()
    {
        return getKlass ()->indexableNstVarsSize (this);
    }
};