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

#include "Desc.h"

class VecOopDesc : public OopDesc
{
    std::vector<Oop<OopDesc> > contents;

  public:
};