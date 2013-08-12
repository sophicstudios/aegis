#ifndef INCLUDED_AEGIS_AFTS_OS_H
#define INCLUDED_AEGIS_AFTS_OS_H

#if defined(linux) || defined(__linux) || defined(__linux__)

#define AFTS_OS "linux"
#define AFTS_OS_LINUX
#define AFTS_OS_UNIX
#define AFTS_OS_POSIX

#elif defined(CYGWIN) || defined(__CYGWIN__) || defined(__CYGWIN32__)

#define AFTS_OS "cygwin"
#define AFTS_OS_CYGWIN
#define AFTS_OS_UNIX
#define AFTS_OS_POSIX

#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)

#define AFTS_OS "win32"
#define AFTS_OS_WIN32
#define AFTS_OS_WINDOWS

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

#define AFTS_OS "iphone"
#define AFTS_OS_APPLE
#define AFTS_OS_IPHONE
#define AFTS_OS_POSIX

#elif TARGET_IPHONE_SIMULATOR

#define AFTS_OS "iphone-simulator"
#define AFTS_OS_APPLE
#define AFTS_OS_IPHONE
#define AFTS_OS_POSIX

#elif TARGET_OS_MAC

#define AFTS_OS "macos"
#define AFTS_OS_APPLE
#define AFTS_OS_MACOS
#define AFTS_OS_POSIX

#endif // TARGET_OS

#else

#error "afts_os.h: unsupported operating system"

#endif

#if defined(__LITTLE_ENDIAN__)
#define AFTS_OS_LITTLE_ENDIAN
#elif defined(__BIG_ENDIAN__)
#define AFTS_OS_BIG_ENDIAN
#else
#error "afts_os.h: __LITTLE_ENDIAN__ or __BIG_ENDIAN__ must be defined"
#endif

#endif // INCLUDED
