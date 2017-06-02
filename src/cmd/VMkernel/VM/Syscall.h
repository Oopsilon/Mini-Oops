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
#include <string>

#include "oops-platform/basic-defs.h"

enum SyscallOp
{
    EIsa,

    /* Puts a character onto the console. */
    EConsPutChar,

    /* I/O functionality */
    EIOFileOpen,
    EIOFileClose,

    EIOFileStatIntoArray,
    EIOFileReadIntoByteArray,
    EIOFileWriteFromByteArray,
    EIOFileSeek,

    /* Locks the Scheduler spinlock. */
    ELockScheduler,
    /* Unlocks the Scheduler spinlock. */
    EUnlockScheduler,

    ECount,
};

static const char * syscallNames[ECount] = {"Isa", "LockScheduler",
                                            "UnlockScheduler"};

struct Syscall
{
    typedef uint8_t type;
    typedef SyscallOp Op;

    static Op op (std::string aName) { return op (aName.c_str ()); }

    static Op op (const char * aName)
    {
        for (int i = 0; i < ECount; i++)
            if (!strcmp (aName, syscallNames[i]))
                return (Op)i;
        fatalError ("Unknown system call name " BLDTEXT ("%s") "\n", aName);
    }
};