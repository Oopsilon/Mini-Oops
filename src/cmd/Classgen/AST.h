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
        EDescInline,
    } methType;

    std::string * _return_type;
    std::string * name;
    std::list<Field> * args;
    std::string * code;

    const Class * cls;

    std::string generate_klass_intf (bool classPrefix = false) const;
    std::string generate_klass_impl () const;

    std::string generate_desc_intf () const;
    std::string generate_desc_impl () const;

    std::string return_type () const;

    void set_class (const Class * aCls) { cls = aCls; }
    bool is_for_klass () const { return methType == EConstructor; }
};

struct Class
{
    std::string * name;
    std::string * superName;
    std::list<Field> * fields;
    std::list<Method> * methods;

    std::string * klass_intf_requires;
    std::string * klass_impl_requires;

    std::string desc_intf_filename () const;
    std::string desc_impl_filename () const;
    std::string klass_intf_filename () const;
    std::string klass_impl_filename () const;

    std::string generate_field_info () const;

    std::string generate_desc_header () const;
    std::string generate_desc_impl () const;
    std::string generate_klass_intf () const;
    std::string generate_klass_impl () const;

    void generate () const;
};