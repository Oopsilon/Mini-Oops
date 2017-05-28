/* Oopsilon
 * Bytecode: System calls.
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

#include <cstring>

struct Syscall
{
    enum Op
    {
        EIsa,
        EEmpty,
        ECount,
    };

    static constexpr const char * names[ECount]{
        "Isa", NULL,
    };

    typedef uint8_t type;

    static Op op (std::string aName) { return op (aName.c_str ()); }

    static Op op (const char * aName)
    {
        for (int i = 0; i < ECount; i++)
            if (!strcmp (aName, names[i]))
                return (Op)i;
        fatalError ("Unknown system call name " BLDTEXT ("%s") "\n", aName);
    }
};