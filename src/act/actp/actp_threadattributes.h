#ifndef INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H
#define INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H

#include <cstdlib>

namespace actp {

enum CreateType {
    CreateType_DETACHED,
    CreateType_JOINABLE
};

struct ThreadAttributes
{
    ThreadAttributes(
        CreateType ct = CreateType_JOINABLE,
        size_t ss = 0);
    
    CreateType createType;
    size_t stackSize;
};

} // namespace

#endif // INCLUDE
