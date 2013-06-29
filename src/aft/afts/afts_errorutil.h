#ifndef INCLUDED_AEGIS_AFTS_ERRORUTIL_H
#define INCLUDED_AEGIS_AFTS_ERRORUTIL_H

#include <afts_os.h>
#include <string>

namespace aegis {
namespace afts {

struct ErrorUtil
{
    static std::string translateErrno(int errnum);
};

} // namespace
} // namespace

#endif // INCLUDED
