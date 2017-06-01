/* Oopsilon
 * Quickgen VM generator support methods.
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

#include <cstdint>
#include <cstdlib>
#include <vector>

std::string __nl (std::string txt) { return txt + "\n"; }

/* These methods are for writing and reading arbitrary types from vectors of
 * some smaller type.
 * Obviously the vector's type must be smaller than the type we are trying to
 * read/write.
 * CT is the type of the bytecode (e.g. uint8_t.) T is the type of data to be
 * written to/from the array/vector. */

/* Reads something of type T from the array of CTs pointed to by `array`.
 * Updates `array` to point to the first CT after the data just read. */
template <class CT, class T> T read_type_from_array (CT *& array)
{
    T result;

    memcpy (&result, &array, sizeof (T));
    array += (sizeof (T) / sizeof (CT));

    return result;
}

/* Writes `someThing` of type T to the vector of CTs pointed to by `vec.` */
template <class CT, class T>
void write_type_to_vector (std::vector<CT> vec, T someThing)
{
    const size_t siz    = sizeof (T) / sizeof (CT);
    const CT * accessor = &someThing;

    for (size_t idx = 0; idx != siz; idx++)
        vec.push_back (*accessor++);
}