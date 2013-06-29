#ifndef INCLUDE_ATLNS_SOCKET_H
#define INCLUDE_ATLNS_SOCKET_H

#include <afls_os.h>

namespace aegis {
namespace atlns {

struct Socket
{
#if defined(AFLS_OS_WINDOWS)
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
