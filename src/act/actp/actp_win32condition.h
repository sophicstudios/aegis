#ifndef INCLUDE_AEGIS_ACTP_WIN32CONDITION_H
#define INCLUDE_AEGIS_ACTP_WIN32CONDITION_H

#include <acts_platform.h>
#include <actp_conditionresult.h>

#if defined(ACTS_PLATFORM_WINTHREADS)

#include <afts_windows.h>

namespace aegis {
namespace actp {

class Win32Mutex;

class Win32Condition
{
public:
    Win32Condition();
    
    ~Win32Condition();
    
    ConditionResult wait(Win32Mutex& mutex);
    
    ConditionResult signalOne();
    
    ConditionResult signalAll();
    
private:
    Win32Condition(Win32Condition const&);
    Win32Condition& operator=(Win32Condition const&);
    
    HANDLE m_queue;
    HANDLE m_mutex;
};

} // namespace
} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE
