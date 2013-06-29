#ifndef INCLUDED_AEGIS_AFTU_WIN32ERROR_H
#define INCLUDED_AEGIS_AFTU_WIN32ERROR_H

#include <afts_os.h>

#if defined(AFTS_OS_WIN32)

#include <string>
#include <windows.h>

namespace aegis {
namespace aftu {

struct Win32Error
{
    static std::string systemErrorString(DWORD errorCode);
};

} // namespace
} // namespace

#endif // AFTS_OS

#endif // INCLUDED
