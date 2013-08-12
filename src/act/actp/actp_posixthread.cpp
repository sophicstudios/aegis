#include <actp_posixthread.h>
#include <aftu_exception.h>

#if defined(ACTS_PLATFORM_PTHREADS)

namespace actp {

namespace {

struct ThreadData
{
    ThreadData(ThreadFunction const& func)
    : entryPoint(func)
    {}

    ThreadFunction entryPoint;
};

void* threadEntry(void* data)
{
    ThreadData* threadData = reinterpret_cast<ThreadData*>(data);

    threadData->entryPoint();

    delete threadData;

    return 0;
}

void translateThreadAttributes(
    ThreadAttributes const& threadAttributes,
    pthread_attr_t& pthreadAttr)
{
    switch (threadAttributes.createType)
    {
    case ThreadAttributes::CreateType_DETACHED:
        pthread_attr_setdetachstate(&pthreadAttr, PTHREAD_CREATE_DETACHED);
        break;
    case ThreadAttributes::CreateType_JOINABLE:
        pthread_attr_setdetachstate(&pthreadAttr, PTHREAD_CREATE_JOINABLE);
        break;
    }
}

bool createThread(
    ThreadFunction const& threadFunction,
    ThreadAttributes const& threadAttributes,
    pthread_t* thread,
    bool* joinable)
{
    // Get the attributes of the new thread
    pthread_attr_t pthreadAttr;
    int attrResult = pthread_attr_init(&pthreadAttr);
    if (0 != attrResult) {
        return false;
    }
    
    translateThreadAttributes(threadAttributes, pthreadAttr);

    // Check whether the thread will be joinable or detached
    *joinable = threadAttributes.createType == ThreadAttributes::CreateType_JOINABLE
        ? true : false;

    // Create the thread, passing a structure that holds the actual thread function 
    ThreadData* threadData = new ThreadData(threadFunction);
    int result = pthread_create(thread, &pthreadAttr, threadEntry, threadData);

    // Destroy the attributes object
    pthread_attr_destroy(&pthreadAttr);

    // Check for any error creating the thread
    if (0 != result) {
        delete threadData;
        return false;
    }
    
    return true;
}

} // namespace

PosixThread::PosixThread(ThreadFunction const& threadFunction)
{
    ThreadAttributes threadAttributes;

    if (!createThread(threadFunction, threadAttributes, &m_thread, &m_joinable)) {
        throw aftu::Exception("createThread failed");
    }
}

PosixThread::PosixThread(ThreadFunction const& threadFunction, ThreadAttributes const& threadAttributes)
{
    if (!createThread(threadFunction, threadAttributes, &m_thread, &m_joinable)) {
        throw aftu::Exception("createThread failed");
    }
}

PosixThread::~PosixThread()
{
    // join with the thread if it's joinable.
    join();
    
    pthread_detach(m_thread);
}
    
bool PosixThread::join()
{
    bool result = m_joinable;
    if (m_joinable)
    {
        int pthreadResult = pthread_join(m_thread, NULL);
        if (pthreadResult != 0)
        {
            result = false;
        }

        m_joinable = false;
    }

    return result;
}

} // namespace

#endif // ACTS_PLATFORM
