/* Oopsilon
 * Object descriptors: Object vector
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

#include <type_traits>

#include "VecDesc.h"

template <class T> class ObjVecDesc : public VecDesc<T>
{
    // static_assert (std::is_base_of (Oop, T)::value,
    //               "ObjVecs must contain OOP types");

  public:
};