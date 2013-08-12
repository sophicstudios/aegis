#ifndef INCLUDE_AEGIS_ACTP_SEMAPHORE_H
#define INCLUDE_AEGIS_ACTP_SEMAPHORE_H

#include <acts_platform.h>
#include <iosfwd>

#if defined(ACTS_PLATFORM_PTHREADS)
#include <semaphore.h>
#include <pthread.h>
#elif defined(ACTS_PLATFORM_WINTHREADS)
#include <afts_windows.h>
#endif

namespace actp {

class Semaphore
{
public:
    enum ResultCode {
        ResultCode_OK,
        ResultCode_WAIT_ABANDONED,
        ResultCode_UNKNOWN
    };
    
    Semaphore(unsigned int maxValue, unsigned int initialValue);
    
    ~Semaphore();
    
    ResultCode acquire();
    
    ResultCode release();

    ResultCode release(unsigned int count);
    
private:
    Semaphore();
    
#if defined(ACTS_PLATFORM_PTHREADS)
    sem_t m_sem;
    pthread_mutex_t m_mutex;
#elif defined(ACTS_PLATFORM_WINTHREADS)
    HANDLE m_handle;
#endif // ACTS_PLATFORM
};

std::ostream& operator<<(std::ostream& os, Semaphore::ResultCode resultCode);

} // namespace

#endif // INCLUDE
