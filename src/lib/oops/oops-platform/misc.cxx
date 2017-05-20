#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "oops-platform/misc.h"

void fnName (const char * funcname) { printf (KMAG "[%s] " KNRM, funcname); }

#define PRINTFUNC fnName (funcName)

extern "C" void dbg2 (const char * funcName, const char * fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    PRINTFUNC;
    vprintf (fmt, args);
    va_end (args);
}

extern "C" void fatalError2 (const char * funcName, const char * fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    PRINTFUNC;
    printf (KRED "ERROR: " KNRM);
    vprintf (fmt, args);
    va_end (args);
    exit (EXIT_FAILURE);
}

extern "C" void oopsMsg2 (const char * fmt, ...)
{
    std::string newFmt = KBLU + string (fmt) + KNRM;
    va_list args;
    va_start (args, fmt);
    vprintf (newFmt.c_str (), args);
    va_end (args);
}
