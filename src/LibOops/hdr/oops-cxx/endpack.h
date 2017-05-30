#include "oops-platform/compats.h"

#undef PACKSTRUCT

#if defined(_MSC_VER)
#pragma pack(pop)
#elif defined(WATCOM)
#pragma pack(pop)
#endif
