#include "Bcom.h"

void Bcom::notice (const char * format, ...)
{
    va_list args;
    va_start (args, format);

    printf (KMAG "ObjectMemory: " KNRM);
    vprintf (format, args);

    va_end (args);
}