#include <aftthr_mutex.h>
#include <aftu_exception.h>

#if defined(AFTTHR_PLATFORM_WINTHREADS)
#include <afts_win32errorutil.h>
#endif

namespace aftthr {

#if defined(AFTTHR_PLATFORM_PTHREADS)

namespace {

Mutex::Result toMutexResult(int result)
{
    switch (result)
    {
        case 0: return Mutex::Result_OK;
        default: return Mutex::Result_UNKNOWN;
    }
}

} // namespace

Mutex::Mutex()
{
    int result = pthread_mutex_init(&m_mutex, NULL);
    if (result != 0)
    {
        throw aftu::Exception("pthread_mutex_init failed");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

Mutex::Result Mutex::lock()
{
    int result = pthread_mutex_lock(&m_mutex);
    return toMutexResult(result);
}

Mutex::Result Mutex::unlock()
{
    int result = pthread_mutex_unlock(&m_mutex);
    return toMutexResult(result);
}

#elif defined(AFTTHR_PLATFORM_WINTHREADS)

namespace {

Mutex::Result toMutexResult(DWORD errorCode)
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
    m_mutex = CreateMutex(NULL, FALSE, NULL);
    if (m_handle == NULL)
    {
        std::string errorString = afts::Win32ErrorUtil::translateSystemError(GetLastError());
        throw std::exception(errorString.c_str());
    }
}

Mutex::~Mutex()
{
    BOOL result = CloseHandle(m_mutex);
    if (!result)
    {
        std::cerr << "Mutex CloseHandle() failed! ["
            << " GetLastError(): " << afts::Win32ErrorUtil::translateSystemError(GetLastError())
            << " ]" << std::endl;
    }
}

Mutex::Result Mutex::lock()
{
    DWORD result = WaitForSingleObject(m_mutex, INFINITE);
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

Mutex::Result Mutex::unlock()
{
    BOOL result = ReleaseMutex(m_mutex);
    if (result != TRUE)
    {
        return toMutexResultCode(GetLastError());
    }

    return Mutex::ResultCode_OK;
}

#endif // AFTTHR_PLATFORM

std::ostream& operator<<(std::ostream& os, Mutex::Result const& result)
{
    switch (result) {
        case Mutex::Result_OK:
            os << "Mutex::Result_OK";
            break;
        case Mutex::Result_NOT_LOCK_OWNER:
            os << "Mutex::Result_NOT_LOCK_OWNER";
            break;
        case Mutex::Result_WAIT_ABANDONED:
            os << "Mutex::Result_WAIT_ABANDONED";
            break;
        case Mutex::Result_UNKNOWN:
        default:
            os << "Mutex::Result_UNKNOWN";
            break;
    }
    
    return os;
}

} // namespace
