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

#include <string>

class Classgen
{
  public:
    int token;
    std::string * lexResult;

    off_t first_line, first_col, last_line, last_col;

    Classgen () : first_line (0), first_col (0), last_line (0), last_col (0) {}

    void parse (std::string filename);
    void compile ();

    void notice (const char * format, ...);
};

extern Classgen cg;