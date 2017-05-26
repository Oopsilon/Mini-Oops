/* Oopsilon
 * Object descriptors: Context object
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

#include "Hierarchy.h"
#include "MemDesc.h"

class Context : public MemOopDesc
{
    enum
    {
        EMethod = 1,

        EArgs,
        ETemps,
        EStack,

        EPC,
        EPFP,
    } Layout;

  public:
    static std::vector<std::string> & nstVarNames ()
    {
        const char * varnames[] = {
            /* <methodOop>: Current method being executed. */
            "method",

            /* <std::vector<oop> *>: Arguments, temporaries, and stack. */
            "args", "temps", "stack",

            /* <smiOop>: Program counter. */
            "pc",
            /* <contextOop>: Previous frame pointer. */
            "pfp",
        };

        static std::vector<std::string> varnamesVec = std::vector<std::string> (
            std::begin (varnames), std::end (varnames));
        return varnamesVec;
    }

    methodOop method () { return nstVar_at<methodOop> (EMethod); }
    void set_method (methodOop val) { return nstVar_at_put (EMethod, val); }

    std::vector<oop> * args () { return nstVar_at<std::vector<oop> *> (EArgs); }
    void set_args (std::vector<oop> * val)
    {
        return nstVar_at_put (EArgs, val);
    }

    std::vector<oop> * temps ()
    {
        return nstVar_at<std::vector<oop> *> (ETemps);
    }
    void set_temps (std::vector<oop> * val)
    {
        return nstVar_at_put (EStack, val);
    }

    std::vector<oop> * stack ()
    {
        return nstVar_at<std::vector<oop> *> (EStack);
    }
    void set_stack (std::vector<oop> * val)
    {
        return nstVar_at_put (EStack, val);
    }

    smiOop pc () { return nstVar_at<smiOop> (EPC); }
    void set_pc (smiOop val) { return nstVar_at_put (EPC, val); }

    contextOop pfp () { return nstVar_at<contextOop> (EPFP); }
    void set_pfp (contextOop val) { return nstVar_at_put (EPFP, val); }
};