/* Oopsilon
 * LibOops: CXX support (Root object - provides basic reflective features)
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include <cassert>
#include <typeinfo>

struct Object
{
    /* A virtual function is necessary to make RTTI work. */
    virtual void unused (){};

    template <typename T> inline bool isA ()
    {
        return typeid (T).hash_code () == typeid (*this).hash_code ();
    }

    template <typename T> inline bool isKindOf ()
    {
        return (dynamic_cast<T *> (this)) ? true : false;
    }

    template <typename T> inline T * asAPtr ()
    {
        T * result = dynamic_cast<T *> (this);
        // assert (result);
        return result;
    }

    template <typename T> inline T & asARef ()
    {
        T * result = dynamic_cast<T *> (this);
        assert (result);
        return *result;
    }
};
