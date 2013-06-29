#ifndef INCLUDE_AEGIS_ACTP_WIN32MUTEX_H
#define INCLUDE_AEGIS_ACTP_WIN32MUTEX_H

#include <acts_platform.h>

#if defined(ACTS_PLATFORM_WINTHREAD)

#include <afts_windows.h>

namespace aegis {
namespace actp {

class Win32Mutex
{
    friend class Win32Condition;
    
public:
    Win32Mutex();
    
    ~Win32Mutex();
    
    MutexResult lock();
    
    MutexResult unlock();
    
private:
    Win32Mutex(Win32Mutex const&);
    Win32Mutex& operator=(Win32Mutex const&);
    
    HANDLE m_handle;
};

} // namespace
} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE

