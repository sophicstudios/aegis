#ifndef INCLUDE_AEGIS_ACTP_POSIXCONDITION_H
#define INCLUDE_AEGIS_ACTP_POSIXCONDITION_H

#include <acts_platform.h>
#include <actp_conditionresult.h>

#if defined(ACTS_PLATFORM_PTHREADS)

#include <pthread.h>

namespace actp {

class PosixMutex;

class PosixCondition
{
public:
    /**
     *
     */
    PosixCondition();
    
    /**
     *
     */
    ~PosixCondition();

    /**
     *
     */
    ConditionResult wait(PosixMutex& mutex);
    
    /**
     *
     */
    ConditionResult signalOne();
    
    /**
     *
     */
    ConditionResult signalAll();
    
private:
    PosixCondition(PosixCondition const&);
    PosixCondition& operator=(PosixCondition const&);
    
    pthread_cond_t m_cond;
};

} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE
