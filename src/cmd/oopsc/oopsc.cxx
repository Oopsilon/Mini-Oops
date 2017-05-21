/* Oopsilon
 * Entry point
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

#include <cstdio>
#include <fstream>
#include <string>
#include <utility>

#include "oopsc.h"

#include "gram.tab.h"
#include "scan.yy.h"

#include "Oops/ClassOop.h"
#include "Oops/SmiOop.h"
#include "VM/vm.h"

#include "AST/Program.h"
#include "AST/Symbol.h"

VM theVM;
VM & vm = theVM;

#define OOPSC_COMPNAME KBLD KMAG "Oopsilon Dynamic Compiler" KNRM "\n"

#if defined(_MSC_VER)
#include <conio.h>
#define WAIT                                                                   \
    printf ("DONE\n");                                                         \
    _getch ();
#else
#define WAIT
#endif

void ParseTrace (FILE *, char *);
void * ParseAlloc (void * (*allocProc) (size_t));
extern "C" void * Parse (void *, int, AST::AST *, ParserState *);
extern "C" void * ParseFree (void *, void (*freeProc) (void *));

Oopsc::Oopsc (std::string RootDir)
    : rootDir (RootDir), program (*new AST::Program)
{
}

void Oopsc::parse (std::string filename, bool isImported)
{
    std::FILE * f = std::fopen ((rootDir + "/" + filename).c_str (), "rb");
    std::string toParse;
    std::pair<int, AST::AST *> result;
    /* Lex requires this scanner structure in order to operate. */
    yyscan_t scanner;
    /* It also requires a suitable buffer-state structure. */
    YY_BUFFER_STATE yybuffer;
    /* Lemon requires this parser structure. */
    void * parser;

    if (!f)
        fatalError ("Could not open Package.oop in directory %s\n",
                    rootDir.c_str ());

    oopsMsg ("Compiling %s...\n", filename.c_str ());

    std::fseek (f, 0, SEEK_END);
    toParse.resize (std::ftell (f));
    std::rewind (f);
    std::fread (&toParse[0], 1, toParse.size (), f);
    std::fclose (f);

    parser = ParseAlloc (malloc);

    pStateStack.push (ParserState (*this, filename, isImported));

    yylex_init_extra (&pState (), &scanner);
    /* Now we need to scan our string into the buffer. */
    yybuffer = yy_scan_string (toParse.c_str (), scanner);

    /* Perform the lexing. */
    while ((pState ().token = yylex (scanner)))
    {
        if (pState ().token == TK_INCLUDE)
            parse (pState ().lexResult->c_str ());
        else
            Parse (parser, pState ().token, pState ().lexResult, &pState ());
    }

    /* Submit an EOF to trigger reduction of the file. */
    Parse (parser, TK_EOF, 0, &pState ());

    /* Free the parser. */
    ParseFree (parser, free);
    /* Now we can clean up the buffer. */
    yy_delete_buffer (yybuffer, scanner);
    /* And, finally, destroy this scanner. */
    yylex_destroy (scanner);
}

string Oopsc::generate () { return ""; }

int main (int argc, char * argv[])
{
    printf (OOPS_BANNER);
    printf (OOPSC_COMPNAME);
    printf (KBLU "[" COMPILER_INFO " on " SYSTEM_INFO ", " __DATE__
                 ", at " __TIME__ "]\n" KNRM);

    if (argc < 2)
        fatalError ("Usage: %s path/to/Oopsilon/Package.oop\n", argv[0]);

    {
        std::ofstream gvOut;
        Oopsc oc (argv[1]);

        // ParseTrace (stdout, KCYN "[Analyser::Lemon] " KNRM);

        oc.parse ("Package.oop");

        WAIT;
        return 0;
    }
}
