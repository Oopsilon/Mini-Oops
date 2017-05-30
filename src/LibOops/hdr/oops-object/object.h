/* Oopsilon
 * Base definitions
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

typedef const char * STR;
typedef const char * SEL;
typedef struct OopsBaseObject * oop;
typedef struct OopsBaseClass * CLS;
/* Method implementation. argBox holds the return value followed by the
 * arguments, in sequence. */
typedef void (*IMP) (oop selfRef, SEL sel, void * argBox);
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

inline void oops_send (oop rcvr, SEL selector, void * args)
{
    IMP imp;
    CLS cls = rcvr->isa;
    VtblEntry * start;

    for (start = cls->vt; start != 0; start++)
        if (!strcmp (start->sel, selector))
        {
            imp = start->imp;
            break;
        }

    imp (rcvr, selector, args);
}