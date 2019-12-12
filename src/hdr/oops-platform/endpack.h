#include "compats.hhh"

#undef PACKSTRUCT

#if defined(_MSC_VER)
#pragma pack(pop)
#elif defined(WATCOM)
#pragma pack(pop)
#endif
