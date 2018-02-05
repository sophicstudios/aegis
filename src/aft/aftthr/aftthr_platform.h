#ifndef INCLUDE_AEGIS_AFTTHR_PLATFORM_H
#define INCLUDE_AEGIS_AFTTHR_PLATFORM_H

#include <afts_platform.h>

#if defined(AFTS_OS_POSIX)

#if defined(AFTS_OS_APPLE)

#define AFTTHR_PLATFORM_APPLE

#endif // AFTS_OS_APPLE

#define AFTTHR_PLATFORM_PTHREADS

#elif defined(AFTS_OS_WIN32)

#define AFTTHR_PLATFORM_WINTHREADS

#endif // AFTS_OS

#endif // INCLUDE
