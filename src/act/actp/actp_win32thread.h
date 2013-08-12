#ifndef INCLUDE_AEGIS_ACTP_WIN32THREAD_H
#define INCLUDE_AEGIS_ACTP_WIN32THREAD_H

#include <acts_platform.h>
#include <actp_threadattributes.h>

#if defined(ACTS_PLATFORM_WINTHREADS)

#include <afts_windows.h>

namespace actp {

class Win32Thread
{
public:
    Win32Thread(ThreadFunction const& threadFunction);

    Win32Thread(ThreadFunction const& threadFunction, ThreadAttributes const& threadAttributes);

    ~Win32Thread();
    
    bool join();

private:
    HANDLE m_thread;
    DWORD m_threadId;
    bool m_joinable;
};

} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE
