#include <actp_semaphore.h>
#include <afts_win32errorutil.h>
#include <afts_assert.h>
#include <iostream>

namespace actp {

#if defined(ACTS_PLATFORM_APPLE)

Semaphore::Semaphore(unsigned int initialValue)
{
    m_semaphore = dispatch_semaphore_create(initialValue);
    if (m_semaphore == nullptr)
    {
        std::cerr << "dispatch_semaphore_create failed ["
            << " ]" << std::endl;
    }
}
    
Semaphore::~Semaphore()
{
    dispatch_release(m_semaphore);
}
    
Semaphore::ResultCode Semaphore::wait()
{
    long result = dispatch_semaphore_wait(m_semaphore, DISPATCH_TIME_FOREVER);
    if (result != 0)
    {
        return ResultCode_UNKNOWN;
    }
    return ResultCode_OK;
}
    
Semaphore::ResultCode Semaphore::signal()
{
    dispatch_semaphore_signal(m_semaphore);
    return ResultCode_OK;
}

#elif defined(ACTS_PLATFORM_PTHREADS)

Semaphore::Semaphore(unsigned int initialValue)
{
    int result = sem_init(&m_semaphore, 0, initialValue);
    if (result != 0)
    {
         std::cerr << "sem_init failed ["
            << " ]" << std::endl;
    }
}
    
Semaphore::~Semaphore()
{
    int result = sem_destroy(&m_semaphore);
    AFTS_ASSERT(0 == result);
}
    
Semaphore::ResultCode Semaphore::wait()
{
    int result = sem_wait(&m_semaphore);
    if (0 != result) {
        return ResultCode_UNKNOWN;
    }
    
    return ResultCode_OK;
}
    
Semaphore::ResultCode Semaphore::signal()
{
    int result = sem_post(&m_semaphore);
    if (0 != result) {
        return ResultCode_UNKNOWN;
    }
    
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
    
Semaphore::ResultCode Semaphore::wait()
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
    
Semaphore::ResultCode Semaphore::signal()
{
    BOOL result = ReleaseSemaphore(m_handle, 1, NULL);
    if (!result)
    {
        return toSemaphoreResultCode(GetLastError());
    }
    
    return ResultCode_OK;
}

#endif // ACTS_PLATFORM

} // namespace
