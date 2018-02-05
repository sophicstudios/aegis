#include <aftthr_thread.h>
#include <aftu_exception.h>

namespace aftthr {

#if defined(AFTTHR_PLATFORM_PTHREADS)

namespace {

struct ThreadData
{
    Thread::Callback callback;
};

void* threadEntry(void* data)
{
    ThreadData* threadData = reinterpret_cast<ThreadData*>(data);

    threadData->callback();

    delete threadData;

    return 0;
}

void translateThreadAttributes(
    ThreadAttributes const& threadAttributes,
    pthread_attr_t& pthreadAttr)
{
    switch (threadAttributes.createType())
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
    Thread::Callback const& callback,
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
    *joinable = threadAttributes.createType() == ThreadAttributes::CreateType_JOINABLE
        ? true : false;

    // Create the thread, passing a structure that holds the actual thread function 
    ThreadData* threadData = new ThreadData();
    threadData->callback = callback;
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

Thread::Thread(Thread::Callback const& callback)
{
    ThreadAttributes threadAttributes;
    threadAttributes.createType(ThreadAttributes::CreateType_JOINABLE);

    if (!createThread(callback, threadAttributes, &m_thread, &m_joinable)) {
        throw aftu::Exception("createThread failed");
    }
}

Thread::Thread(Callback const& callback, ThreadAttributes const& threadAttributes)
{
    if (!createThread(callback, threadAttributes, &m_thread, &m_joinable)) {
        throw aftu::Exception("createThread failed");
    }
}

Thread::~Thread()
{
    // join with the thread if it's joinable.
    join();
    
    pthread_detach(m_thread);
}
    
bool Thread::join()
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

#elif defined(AFTTHR_PLATFORM_WINTHREADS)

namespace {

struct ThreadData
{
    ThreadFunction threadFunction;
};

unsigned int __stdcall threadFunc(void* data)
{
    ThreadData* threadData = reinterpret_cast<ThreadData*>(data);
    threadData->threadFunction();
    delete threadData;
    return 0;
}

} // namespace

Thread::Thread(ThreadFunction const& threadFunction)
{
    ThreadData* threadData = new ThreadData();
    threadData->threadFunction = threadFunction;

    m_thread = reinterpret_cast<HANDLE>(
            _beginthreadex(
                NULL,
                0,
                threadFunc,
                threadData,
                0,
                reinterpret_cast<unsigned int*>(&m_threadId)));
}

Thread::Thread(ThreadFunction const& threadFunction, ThreadAttributes const& threadAttributes)
{
    ThreadData* threadData = new ThreadData();
    threadData->threadFunction = threadFunction;

    m_thread = reinterpret_cast<HANDLE>(
        _beginthreadex(
            NULL,
            threadAttributes.stackSize,
            threadFunc,
            threadData,
            0,
            reinterpret_cast<unsigned int*>(&m_threadId)));

    if (threadAttributes.createType == ThreadAttributes::CreateType_DETACHED) {
        m_joinable = false;
        CloseHandle(m_thread);
    }
}

Thread::~Thread()
{
    join();
}

bool Thread::join()
{
    if (m_joinable) {
        DWORD result = WaitForSingleObject(m_thread, INFINITE);
        CloseHandle(m_thread);
        m_joinable = false;
        return result == WAIT_OBJECT_0;
    }

    return false;
}

#endif // AFTTHR_PLATFORM

} // namespace
