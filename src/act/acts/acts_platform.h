#ifndef INCLUDE_AEGIS_ACTS_PLATFORM_H
#define INCLUDE_AEGIS_ACTS_PLATFORM_H

#include <afts_platform.h>

#if defined(AFTS_OS_POSIX)

#define ACTS_PLATFORM_PTHREADS

#elif defined(AFTS_OS_WIN32)

#define ACTS_PLATFORM_WINTHREADS

#endif // AFTS_OS

#endif // INCLUDE
