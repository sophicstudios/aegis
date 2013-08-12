#include <actp_win32mutex.h>
#include <aftu_exception.h>

#if defined(ACTS_PLATFORM_WINTHREADS)

#include <afts_win32errorutil.h>

namespace actp {

namespace {

MutexResult toMutexResultCode(DWORD errorCode)
{
    switch (errorCode)
    {
        case 0: return MutexResult_OK;
        case WAIT_ABANDONED: return MutexResult_WAIT_ABANDONED;
        default: return MutexResult_UNKNOWN;
    }
}

} // namespace

Mutex::Mutex()
{
    m_handle = CreateMutex(NULL, FALSE, NULL);
    if (m_handle == NULL)
    {
        std::string errorString = afts::Win32ErrorUtil::translateSystemError(GetLastError());
        throw std::exception(errorString.c_str());
    }
}

Mutex::~Mutex()
{
    BOOL result = CloseHandle(m_handle);
    if (!result)
    {
        std::cerr << "Mutex CloseHandle() failed! ["
            << " GetLastError(): " << afts::Win32ErrorUtil::translateSystemError(GetLastError())
            << " ]" << std::endl;
    }
}

Mutex::ResultCode Mutex::lock()
{
    DWORD result = WaitForSingleObject(m_handle, INFINITE);
    switch (result)
    {
    case WAIT_OBJECT_0:
        return ResultCode_OK;
        break;
    default:
        return toMutexResultCode(result);
        break;
    }
}

Mutex::ResultCode Mutex::unlock()
{
    BOOL result = ReleaseMutex(m_handle);
    if (result != TRUE)
    {
        return toMutexResultCode(GetLastError());
    }

    return Mutex::ResultCode_OK;
}

} // namespace

#endif // ACTS_PLATFORM
