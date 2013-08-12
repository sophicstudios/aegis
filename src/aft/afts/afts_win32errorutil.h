#ifndef INCLUDED_AEGIS_AFTS_WIN32ERRORUTIL_H
#define INCLUDED_AEGIS_AFTS_WIN32ERRORUTIL_H

#include <afts_os.h>

#if defined(AFTS_OS_WIN32)

#include <string>
#include <afts_windows.h>

namespace afts {

struct Win32ErrorUtil
{
    static std::string translateSystemError(DWORD errorCode);
};

} // namespace

#endif // AFTS_OS

#endif // INCLUDED
