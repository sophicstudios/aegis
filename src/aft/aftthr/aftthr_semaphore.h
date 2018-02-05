#ifndef INCLUDE_AEGIS_AFTTHR_SEMAPHORE_H
#define INCLUDE_AEGIS_AFTTHR_SEMAPHORE_H

#include <aftthr_platform.h>
#include <iosfwd>

#if defined(AFTTHR_PLATFORM_APPLE)
#include <dispatch/dispatch.h>
#elif defined(AFTTHR_PLATFORM_PTHREADS)
#include <semaphore.h>
#include <pthread.h>
#elif defined(AFTTHR_PLATFORM_WINTHREADS)
#include <afts_windows.h>
#endif

namespace aftthr {

class Semaphore
{
public:
    enum ResultCode {
        ResultCode_OK,
        ResultCode_WAIT_ABANDONED,
        ResultCode_UNKNOWN
    };

    Semaphore(unsigned int initialValue);
    
    ~Semaphore();
    
    ResultCode wait();
    
    ResultCode signal();

private:
    Semaphore();

#if defined(AFTTHR_PLATFORM_APPLE)
    dispatch_semaphore_t m_semaphore;
#elif defined(AFTTHR_PLATFORM_PTHREADS)
    sem_t m_semaphore;
#elif defined(AFTTHR_PLATFORM_WINTHREADS)
    HANDLE m_handle;
#endif // AFTTHR_PLATFORM
};

std::ostream& operator<<(std::ostream& os, Semaphore::ResultCode resultCode);

} // namespace

#endif // INCLUDE
