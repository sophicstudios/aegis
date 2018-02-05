#include <aftthr_condition.h>
#include <aftu_exception.h>
#include <afts_assert.h>
#include <afts_errorutil.h>

namespace aftthr {

#if defined(AFTTHR_PLATFORM_PTHREADS)

Condition::Condition()
{
    int result = pthread_cond_init(&m_condition, NULL);
    if (result != 0)
    {
        throw aftu::Exception("pthread_cond_init failed!") << " ["
            << " error: " << afts::ErrorUtil::translateErrno(result)
            << " ]";
    }
}

Condition::~Condition()
{
    int result = pthread_cond_destroy(&m_condition);
    AFTS_ASSERT(result == 0);
}

Condition::Result Condition::wait(Mutex& mutex)
{
    int result = pthread_cond_wait(&m_condition, &mutex.m_mutex);
    if (result != 0)
    {
        return Condition::Result_UNKNOWN;
    }
    
    return Condition::Result_OK;
}

Condition::Result Condition::signalOne()
{
    int result = pthread_cond_signal(&m_condition);
    if (result != 0)
    {
        return Condition::Result_UNKNOWN;
    }
    
    return Condition::Result_OK;
}

Condition::Result Condition::signalAll()
{
    int result = pthread_cond_broadcast(&m_condition);
    if (result != 0)
    {
        return Condition::Result_UNKNOWN;
    }
    
    return Condition::Result_OK;
}

#elif defined(AFTTHR_PLATFORM_WINTHREADS)

// TODO: Finish and test this implementation
Condition::Condition()
: m_waiting(0)
{
    m_condition = CreateSemaphore(NULL, 0, std::numeric_limits<long>::max(), NULL);
    m_mutex = CreateMutex(NULL, FALSE, NULL);
}
    
Condition::Condition()
{
    CloseHandle(m_mutex);
    CloseHandle(m_condition);
}

Condition::Result Condition::wait(Mutex& mutex)
{
    WaitForSingleObject(m_mutex, INFINITE);
    ++m_waiting;
    ReleaseMutex(m_mutex);
    
    mutex.unlock();
 
    WaitForSingleObject(m_condition, INFINITE);
       
    mutex.lock();

    --m_waiting;
    
    return Condition::Result_UNKNOWN;
}

Condition::Result Condition::signalOne()
{
    WaitForSingleObject(m_mutex, INFINITE);
    
    ReleaseMutex(m_mutex);

    ReleaseSemaphore(m_condition, 1, NULL);
    
    return Condition::Result_UNKNOWN;
}

Condition::Result Condition::signalAll()
{
    return Condition::Result_UNKNOWN;
}

#endif // AFTTHR_PLATFORM

std::ostream& operator<<(std::ostream& os, Condition::Result const& result)
{
    switch (result) {
        case Condition::Result_OK:
            os << "Condition::Result_OK";
            break;
        case Condition::Result_INVALID_MUTEX:
            os << "Condition::Result_INVALID_MUTEX";
            break;
        case Condition::Result_UNKNOWN:
        default:
            os << "Condition::Result_UNKNOWN";
            break;
    }
    
    return os;
}

} // namespace
