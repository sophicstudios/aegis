#include <actp_posixmutex.h>
#include <aftu_exception.h>

#if defined(ACTS_PLATFORM_PTHREADS)

namespace aegis {
namespace actp {

namespace {

MutexResult convertResult(int result)
{
    switch (result)
    {
        case 0: return MutexResult_OK;
        default: return MutexResult_UNKNOWN;
    }
}

} // namespace

PosixMutex::PosixMutex()
{
    int result = pthread_mutex_init(&m_mutex, NULL);
    if (result != 0)
    {
        throw aftu::Exception("pthread_mutex_init failed");
    }
}

PosixMutex::~PosixMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

MutexResult PosixMutex::lock()
{
    int result = pthread_mutex_lock(&m_mutex);
    return convertResult(result);
}

MutexResult PosixMutex::unlock()
{
    int result = pthread_mutex_unlock(&m_mutex);
    return convertResult(result);
}

} // namespace
} // namespace

#endif // ACTS_PLATFORM
