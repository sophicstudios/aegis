#ifndef INCLUDE_AEGIS_ACTP_POSIXMUTEX_H
#define INCLUDE_AEGIS_ACTP_POSIXMUTEX_H

#include <actp_mutexresult.h>
#include <acts_platform.h>

#if defined(ACTS_PLATFORM_PTHREADS)

#include <pthread.h>

namespace actp {

class PosixMutex
{
    friend class PosixCondition;
    
public:
    PosixMutex();
    
    ~PosixMutex();
    
    MutexResult lock();
    
    MutexResult unlock();
    
private:
    PosixMutex(PosixMutex const&);
    PosixMutex& operator=(PosixMutex const&);
    
    pthread_mutex_t m_mutex;
};

} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE
