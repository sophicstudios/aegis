#include <actp_semaphore.h>
#include <afts_win32errorutil.h>
#include <afts_assert.h>
#include <iostream>

namespace aegis {
namespace actp {

#if defined(ACTS_PLATFORM_PTHREADS)

Semaphore::Semaphore(unsigned int maxValue, unsigned int initialValue)
: m_sem(NULL)
{
    int result = sem_init(&m_sem, 0, initialValue);
}
    
Semaphore::~Semaphore()
{
    int result = sem_destroy(&m_sem);
    AFTS_ASSERT_DEBUG(0 == result);
}
    
Semaphore::ResultCode Semaphore::acquire()
{
    int result = sem_wait(&m_sem);
    if (0 != result) {
    }
    
    return ResultCode_OK;
}
    
Semaphore::ResultCode Semaphore::release()
{
    int result = sem_post(&m_sem);
    if (0 != result) {
    }
    
    return ResultCode_OK;
}

Semaphore::ResultCode Semaphore::release(unsigned int count)
{
    return ResultCode_OK;
}

#elif defined(ACTS_PLATFORM_WINTHREADS)

namespace {

Semaphore::ResultCode toSemaphoreResultCode(DWORD errorCode)
{
    switch (errorCode)
    {
    case 0: return Semaphore::ResultCode_OK;
    default: return Semaphore::ResultCode_UNKNOWN;
    }
}

}

Semaphore::Semaphore(unsigned int maxValue, unsigned int initialValue)
{
    m_handle = CreateSemaphore(NULL, static_cast<LONG>(initialValue), static_cast<LONG>(maxValue), NULL);
    if (!m_handle)
    {
        std::string errorString = afts::Win32ErrorUtil::translateSystemError(GetLastError());
        throw std::exception(errorString.c_str());        
    }
}
    
Semaphore::~Semaphore()
{
    BOOL result = CloseHandle(m_handle);
    if (!result)
    {
        std::cerr << "Semaphore CloseHandle() failed! ["
            << " GetLastError(): " << afts::Win32ErrorUtil::translateSystemError(GetLastError())
            << " ]" << std::endl;
    }
}
    
Semaphore::ResultCode Semaphore::acquire()
{
    DWORD result = WaitForSingleObject(m_handle, INFINITE);
    switch (result)
    {
        case WAIT_OBJECT_0:
            return ResultCode_OK;
            break;
        case WAIT_ABANDONED:
            return ResultCode_WAIT_ABANDONED;
            break;
        default:
            return toSemaphoreResultCode(GetLastError());
            break;
    }
}
    
Semaphore::ResultCode Semaphore::release()
{
    BOOL result = ReleaseSemaphore(m_handle, 1, NULL);
    if (!result)
    {
        return toSemaphoreResultCode(GetLastError());
    }
    
    return ResultCode_OK;
}

Semaphore::ResultCode Semaphore::release(unsigned int count)
{
    BOOL result = ReleaseSemaphore(m_handle, static_cast<LONG>(count), NULL);
    if (!result)
    {
        return toSemaphoreResultCode(GetLastError());
    }

    return ResultCode_OK;
}

#endif // ACTS_PLATFORM

} // namespace
} // namespace
