#ifndef INCLUDE_ATLS_SOCKET_H
#define INCLUDE_ATLS_SOCKET_H

#include <aflp_os.h>

namespace aegis {
namespace atls {

struct Socket
{
#if defined(AFLP_OS_WINDOWS)
    typedef SOCKET Handle;
#elif defined(AFLP_OS_UNIX)
    typedef int Handle;
#endif

    enum Error {
        Error_OK,
        Error_WOULDBLOCK
    };
};

} // namespace
} // namespace

#endif // INCLUDE
