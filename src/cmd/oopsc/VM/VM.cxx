/* Oopsilon
 * VM class.
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

#include <cstdarg>

#include "VM.h"

#define OOPSC_COMPNAME KBLD KMAG "Oopsilon Dynamic Compiler" KNRM "\n"

VM VM::globalVM;
VM & vm = VM::globalVM;

VM::VM ()
{
    printf (OOPS_BANNER);
    notice (OOPSC_COMPNAME);
    notice (KBLU "[" COMPILER_INFO " on " SYSTEM_INFO ", " __DATE__
                 ", at " __TIME__ "]\n" KNRM);
    notice ("Initialising ObjectMemory...\n");
    mem.preboot ();
}

void VM::notice (const char * format, ...)
{
    va_list args;
    va_start (args, format);

    printf (KBLU "VMkernel: " KNRM);
    vprintf (format, args);

    va_end (args);
}