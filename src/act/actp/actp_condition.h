#ifndef INCLUDE_AEGIS_ACTP_CONDITION_H
#define INCLUDE_AEGIS_ACTP_CONDITION_H

#include <acts_platform.h>
#include <actp_mutex.h>
#include <iosfwd>

#if defined(ACTS_PLATFORM_PTHREADS)
#include <actp_posixcondition.h>
#elif defined(ACTS_PLATFORM_WINTHREADS)
#include <actp_win32condition.h>
#endif

namespace aegis {
namespace actp {

#if defined(ACTS_PLATFORM_PTHREADS)
typedef PosixCondition NativeCondition;
#elif defined(ACTS_PLATFORM_WINTHREADS)
typedef Win32Condition NativeCondition;
#endif

class Condition
{
    friend class Mutex;

public:
    Condition();

    ~Condition();

    ConditionResult wait(Mutex& mutex);

    ConditionResult signalOne();

    ConditionResult signalAll();

private:
    Condition(Condition const&);
    Condition& operator=(Condition const&);

    NativeCondition m_nativeCondition;
};

inline ConditionResult Condition::wait(Mutex& mutex)
{
    return m_nativeCondition.wait(mutex.m_nativeMutex);
}

inline ConditionResult Condition::signalOne()
{
    return m_nativeCondition.signalOne();
}

inline ConditionResult Condition::signalAll()
{
    return m_nativeCondition.signalAll();
}

} // namespace
} // namespace

#endif // INCLUDE
