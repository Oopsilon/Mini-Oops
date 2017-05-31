/* Oopsilon
 * Classgen: Oops class generator.
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

#include <list>
#include <string>

struct Class;

struct Field
{
    std::string * type;
    std::string * name;

    std::string generate () const;
};

struct Method
{
    enum MethType
    {
        EConstructor,
    } methType;

    std::string * _return_type;
    std::string * name;
    std::list<Field> * args;
    std::string * code;

    Class * cls;

    std::string generate_klass_interface () const;

    std::string return_type () const;

    void set_class (Class * aCls) { cls = aCls; }
    bool is_for_klass () const { return methType == EConstructor; }
};

struct Class
{
    std::string * name;
    std::string * superName;
    std::list<Field> * fields;
    std::list<Method> * methods;

    std::string generate_field_info () const;

    void generate ();
};