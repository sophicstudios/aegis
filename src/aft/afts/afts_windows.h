#ifndef INCLUDED_AEGIS_AFTS_WINDOWS_H
#define INCLUDED_AEGIS_AFTS_WINDOWS_H

#include <afts_os.h>

#if defined(AFTS_OS_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#ifndef NOMINMAX
#define NOMINMAX 1
#endif // NOMINMAX

#include <windows.h>

#endif // AFTS_OS

#endif // INCLUDED
