#ifndef INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H
#define INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H

#include <boost/function.hpp>
#include <cstdlib>

namespace aegis {
namespace actp {

typedef boost::function<void (void)> ThreadFunction;

struct ThreadAttributes
{
    enum CreateType {
        CreateType_DETACHED,
        CreateType_JOINABLE
    };

    ThreadAttributes(
        CreateType ct = CreateType_JOINABLE,
        size_t ss = 0);
    
    CreateType createType;
    size_t stackSize;
};

ThreadAttributes::ThreadAttributes(CreateType ct, size_t ss)
: createType(ct), stackSize(ss)
{}

} // namespace
} // namespace

#endif // INCLUDE
