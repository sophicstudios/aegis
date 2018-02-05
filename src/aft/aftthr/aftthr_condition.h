#ifndef INCLUDE_AEGIS_AFTTHR_CONDITION_H
#define INCLUDE_AEGIS_AFTTHR_CONDITION_H

#include <aftthr_platform.h>
#include <aftthr_mutex.h>
#include <iosfwd>

#if defined(AFTTHR_PLATFORM_PTHREADS)
#include <pthread.h>
#endif

namespace aftthr {

class Condition
{
    friend class Mutex;

public:
    enum Result {
        Result_OK,
        Result_INVALID_MUTEX,
        Result_UNKNOWN
    };

    Condition();

    ~Condition();

    Result wait(Mutex& mutex);

    Result signalOne();

    Result signalAll();

private:
    Condition(Condition const&);
    Condition& operator=(Condition const&);

    #if defined(AFTTHR_PLATFORM_PTHREADS)
        pthread_cond_t m_condition;
    #elif defined(AFTTHR_PLATFORM_WINTHREADS)
        HANDLE m_condition;
        HANDLE m_mutex;
    #endif
};

std::ostream& operator<<(std::ostream& os, Condition::Result const& result);

} // namespace

#endif // INCLUDE
