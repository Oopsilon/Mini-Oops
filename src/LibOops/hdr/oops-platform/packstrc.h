#include "compats.hhh"

#if defined(_MSC_VER)
#pragma pack(push, packing)
#pragma pack(1)
#define PACKSTRUCT
#elif defined(__GNUC__) || defined(__clang)
#define PACKSTRUCT __attribute__ ((packed))
#elif defined(WATCOM)
#pragma pack(push, 1)
#define PACKSTRUCT
#else
#error Unknown compiler
#endif
