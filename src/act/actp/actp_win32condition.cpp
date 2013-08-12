#include <actp_win32condition.h>
#include <actp_win32mutex.h>
#include <aftu_exception.h>
#include <afts_win32errorutil.h>
#include <afts_assert.h>

#if defined(ACTS_PLATFORM_WINTHREADS)

namespace actp {

Win32Condition::Win32Condition()
: m_waiting(0)
{
    m_queue = CreateSemaphore(NULL, 0, std::numeric_limits<long>::max(), NULL);
    m_mutex = CreateMutex(NULL, FALSE, NULL);
}
    
Win32Condition::~Win32Condition()
{
    CloseHandle(m_mutex);
    CloseHandle(m_queue);
}

ConditionResult Win32Condition::wait(Win32Mutex& mutex)
{
    WaitForSingleObject(m_mutex, INFINITE);
    ++m_waiting;
    ReleaseMutex(m_mutex);
    
    mutex.unlock();
 
    WaitForSingleObject(m_queue, INFINITE);
       
    mutex.lock();

    --m_waiting;
    
    return ConditionResult_UNKNOWN;
}

ConditionResult Win32Condition::signalOne()
{
    WaitForSingleObject(m_mutex, INFINITE);
    
    ReleaseMutex(m_mutex);

    ReleaseSemaphore(m_queue, 1, NULL);
    
    return ConditionResult_UNKNOWN;
}

ConditionResult Win32Condition::signalAll()
{
    return ConditionResult_UNKNOWN;
}

} // namespace

#endif // ACTS_PLATFORM
