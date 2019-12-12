/* Oopsilon
 * Base definitions
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

typedef const char * STR;
typedef const char * SEL;
typedef struct OopsBaseObject * oop;
typedef struct OopsBaseClass * CLS;
typedef oop (*IMP) (oop selfRef, SEL sel, ...);
typedef struct VtblEntry * vtbl;

struct VtblEntry
{
    SEL sel;
    IMP imp;
};

struct OopsBaseObject
{
    CLS isa;
    size_t refcnt;
};

struct OopsBaseClass
{
    CLS isa;
    size_t refcnt;
    CLS super;
    long instanceSize;
    vtbl vt;
};

inline IMP oops_bind (oop rcvr, SEL selector)
{
    CLS cls = rcvr->isa;
    VtblEntry * it;

    for (it = cls->vt; start != 0; it++)
        if (!strcmp (start->sel, selector))
            return it->imp;

    if (super)
        return super->oops_bind (rcvr, selector);

    abort (99);
}