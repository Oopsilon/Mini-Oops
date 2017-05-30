/* Oopsilon
 * Bytecode interpreter.
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

class Interpreter
{
    /* The interpreter's sole register. */
    contextOop cp;

  public:
    Interpreter (methodOop aMeth);

    void interpret (contextOop aContext);
};