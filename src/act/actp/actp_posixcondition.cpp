#include <actp_posixcondition.h>
#include <actp_posixmutex.h>
#include <aftu_exception.h>
#include <afts_errorutil.h>
#include <afts_assert.h>

#if defined(ACTS_PLATFORM_PTHREADS)

namespace aegis {
namespace actp {

PosixCondition::PosixCondition()
{
    int result = pthread_cond_init(&m_cond, NULL);
    if (result != 0)
    {
        throw aftu::Exception("pthread_cond_init failed!") << " ["
            << " error: " << afts::ErrorUtil::translateErrno(result)
            << " ]";
    }
}

PosixCondition::~PosixCondition()
{
    int result = pthread_cond_destroy(&m_cond);
    AFTS_ASSERT_DEBUG(result == 0);
}

ConditionResult PosixCondition::wait(PosixMutex& mutex)
{
    int result = pthread_cond_wait(&m_cond, &mutex.m_mutex);
    if (result != 0)
    {
        return ConditionResult_UNKNOWN;
    }
    
    return ConditionResult_OK;
}

ConditionResult PosixCondition::signalOne()
{
    int result = pthread_cond_signal(&m_cond);
    if (result != 0)
    {
        return ConditionResult_UNKNOWN;
    }
    
    return ConditionResult_OK;
}

ConditionResult PosixCondition::signalAll()
{
    int result = pthread_cond_broadcast(&m_cond);
    if (result != 0)
    {
        return ConditionResult_UNKNOWN;
    }
    
    return ConditionResult_OK;
}

} // namespace
} // namespace

#endif // ACTS_PLATFORM
