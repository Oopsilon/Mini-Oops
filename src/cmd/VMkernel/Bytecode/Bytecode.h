/* Oopsilon
 * Bytecode: Bytecode listing.
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

struct Bytecode
{
    enum Op
    {
        /* A scheme of stack description is used in these comments:
         * beginning with a square bracket, the rightmost variable is to be on
         * the top of the stack, and to the left descends the relative position
         * in the stack. The resulting stack is shown after -- in the same way.
         * If a bytecode expects to be followed by some byte, or some oop, etc,
         * which is used as a parameter, this is noted sequentially within |
         * vertical bars. |
         */

        EPushTrue,
        EPushFalse,
        EPushNil,
        EPushSelf,

        /* These expect only one parameter, an index. | Index | */
        EPushArg,
        EPushLiteral,
        EPushTemp,
        EPushNstVar,

        /* These expect two parameters: an oop to store on the stack and an
           index in the bytecode. | Index | [ Oop -- ] */
        EStoreTemp,
        EStoreNstVar,

        /* Sends a message. | Argcount | [ Receiver Selector Args... -- result ]
         */
        ESend,

        /* Sends a message to self beginning lookup in the superclass. |
           Argcount | [ Selector Args... -- result ] */
        ESuperSend,

        /* Sets the return value. [ ReturnValue ] */
        EStoreRetVal,

        /* Returns. */
        EReturn,
    };

    uint8_t op;
};