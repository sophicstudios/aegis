#ifndef INCLUDED_AEGIS_AFTS_COMPILER_H
#define INCLUDED_AEGIS_AFTS_COMPILER_H

#include <afts_os.h>

/** This component defines macros identifying the current compiler.
 * The following are defined:
 * AFTS_COMPILER
 * AFTS_COMPILER_MAJOR_VERSION
 * AFTS_COMPILER_MINOR_VERSION
 * AFTS_COMPILER_*
 *
 * This header also defines macros useful when compiling dynamic libraries, to
 * ease in automatically exporting/importing symbols from the library and into
 * clients of the library
 */

/**
 * Definitions standard across all compilers
 */
#if defined(__SSE__)
#define AFTS_COMPILER_SSE
#endif

#if defined(__SSE2__)
#define AFTS_COMPILER_SSE2
#endif

#if defined(__SSE3__)
#define AFTS_COMPILER_SSE3
#endif

#if !defined(NDEBUG)
#define AFTS_DEBUG
#endif

/*****************************************
 * GNU Compiler Collection
 *****************************************/
#if defined(__GNUC__)

#define AFTS_COMPILER "gnuc"
#define AFTS_COMPILER_GNUC
#define AFTS_COMPILER_MAJOR_VERSION __GNUC__
#define AFTS_COMPILER_MINOR_VERSION __GNUC_MINOR__
#define AFTS_COMPILER_PATCH_VERSION __GNUC_PATCHLEVEL__

#if defined(AFTS_OS_WIN32)

#define AFTS_DLLIMPORT __declspec(dllimport)
#define AFTS_DLLEXPORT __declspec(dllexport)
#define AFTS_DLLLOCAL

#else // non-win32

#if defined(GCC_HASCLASSVISIBILITY)

// If this is defined, any classes and functions marked as AEGIS_AFTS_DLLLOCAL
// will not be exported from dynamic libraries.

#define AFTS_DLLIMPORT __attribute__ ((visibility("default")))
#define AFTS_DLLEXPORT __attribute__ ((visibility("default")))
#define AFTS_DLLLOCAL __attribute__ ((visibility("hidden")))

#else // no class visibility

#define AFTS_DLLIMPORT
#define AFTS_DLLEXPORT
#define AFTS_DLLLOCAL

#endif // GCC_HASCLASSVISIBILITY

#endif // AFTS_OS_WIN32

/*****************************************
 * Microsoft Visual C++
 *****************************************/
#elif defined(_MSC_VER)

#define AFTS_COMPILER "msvc"
#define AFTS_COMPILER_MSVC
#define AFTS_COMPILER_MAJOR_VERSION _MSC_VER
#define AFTS_COMPILER_MINOR_VERSION
#define AFTS_COMPILER_PATCH_VERSION

#define AFTS_DLLIMPORT __declspec(dllimport)
#define AFTS_DLLEXPORT __declspec(dllexport)
#define AFTS_DLLLOCAL

#ifndef NDEBUG
#define AFTS_DEBUG
#endif // NDEBUG

// C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#pragma warning(disable : 4290)

// LNK4221: This object file does not define any previously undefined public symbols,
// so it will not be used by any link operation that consumes this library
#pragma warning(disable : 4221)

#else

#error "afts_compiler.h: unsupported compiler"

#endif

#endif // INCLUDED
