/* Oopsilon
 * oopsc Oopsilon Compiler: Parser state.
 * Copyright (c) 2017 D. Mackay. All rights reserved. */

#pragma once

#include "oops-platform/misc.h"

namespace AST
{
struct AST;
struct Directive;
struct Symbol;
struct Program;
};

class Oopsc;

struct LineInfo
{
    int line = 0, col = 0;
    LineInfo () {}
    LineInfo (int L, int C) : line (L), col (C) {}
};

class ParserState
{
    friend class Oopsc;
    std::string filename;
    int token;
    AST::Symbol * lexResult;

  public:
    Oopsc & oc;
    /* Is this file simply being imported, or is it a source file for full
     * generation? */
    bool isImported;
    int first_line, first_col, last_line, last_col;
    int brace_depth;

    ParserState (Oopsc & anImgParser, std::string aFilename, bool imported)
        : oc (anImgParser), token (0), filename (aFilename), lexResult (NULL),
          isImported (imported)
    {
    }

    /* Parser (Lemon) interface */
    void addDirective (AST::Directive * aDir);

    LineInfo lineInfo () { return LineInfo (first_line, first_col); }

    /* Lexer (Flex) interface */
    void setResult (AST::Symbol * anAST) { lexResult = anAST; }
    AST::Symbol * result () { return lexResult; }
};