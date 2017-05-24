/* Oopsilon
 * Object descriptors: C++ Vector object
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

#include <vector>

#include "Desc.h"

template <typename T> class VecOopDesc : public OopDesc
{
    std::vector<T> _contents;

  public:
    std::vector<T> contents () { return _contents; }
    void set_contents (std::vector<T> newContents) { _contents = newContents; }
};

typedef VecOopDesc<char> ByteVecOopDesc;