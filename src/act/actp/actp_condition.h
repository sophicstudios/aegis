#ifndef INCLUDE_AEGIS_ACTP_CONDITION_H
#define INCLUDE_AEGIS_ACTP_CONDITION_H

#include <acts_platform.h>
#include <actp_mutex.h>
#include <iosfwd>

#if defined(ACTS_PLATFORM_PTHREADS)
#include <pthread.h>
#elif defined(ACTS_PLATFORM_WINTHREADS)
#include <actp_win32condition.h>
#endif

namespace actp {

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

    #if defined(ACTS_PLATFORM_PTHREADS)
        pthread_cond_t m_condition;
    #elif defined(ACTS_PLATFORM_WINTHREADS)
        HANDLE m_condition;
        HANDLE m_mutex;
    #endif
};

std::ostream& operator<<(std::ostream& os, Condition::Result const& result);

} // namespace

#endif // INCLUDE
