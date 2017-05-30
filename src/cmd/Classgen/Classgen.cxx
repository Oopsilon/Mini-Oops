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

#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <string>
#include <utility>

#include "oops-platform/misc.h"

#include "Classgen.h"

#include "gram.tab.h"
#include "scan.yy.h"

Classgen cg;

void ParseTrace (FILE *, char *);
void * ParseAlloc (void * (*allocProc) (size_t));
extern "C" void * Parse (void *, int, std::string *);
extern "C" void * ParseFree (void *, void (*freeProc) (void *));

void Classgen::notice (const char * format, ...)
{
    va_list args;
    va_start (args, format);

    printf (KGRN "Classgen: " KNRM);
    vprintf (format, args);

    va_end (args);
}

void Classgen::parse (std::string filename)
{
    std::FILE * f = std::fopen (filename.c_str (), "rb");
    std::string toParse;
    /* Lex requires this scanner structure in order to operate. */
    yyscan_t scanner;
    /* It also requires a suitable buffer-state structure. */
    YY_BUFFER_STATE yybuffer;
    /* Lemon requires this parser structure. */
    void * parser;

    if (!f)
        fatalError ("Could not open %s\n", filename.c_str ());

    notice ("Analysing file %s...\n", filename.c_str ());

    std::fseek (f, 0, SEEK_END);
    toParse.resize (std::ftell (f));
    std::rewind (f);
    std::fread (&toParse[0], 1, toParse.size (), f);
    std::fclose (f);

    parser = ParseAlloc (malloc);

    yylex_init_extra (this, &scanner);
    /* Now we need to scan our string into the buffer. */
    yybuffer = yy_scan_string (toParse.c_str (), scanner);

    /* Perform the lexing. */
    while ((token = yylex (scanner)))
    {
        Parse (parser, token, lexResult);
    }

    /* Submit an EOF to trigger reduction of the file. */
    Parse (parser, TK_EOF, 0);

    /* Free the parser. */
    ParseFree (parser, free);
    /* Now we can clean up the buffer. */
    yy_delete_buffer (yybuffer, scanner);
    /* And, finally, destroy this scanner. */
    yylex_destroy (scanner);
}

int main (int argc, char * argv[])
{
    if (argc < 3)
        fatalError ("Usage: %s path/to/Oopsilon/Package.oop\n", argv[0]);

    {
        std::ofstream out;

        // ParseTrace (stdout, KCYN "[Analyser::Lemon] " KNRM);

        return 0;
    }
}