#include <actp_win32thread.h>

#if defined(ACTS_PLATFORM_WINTHREADS)

namespace actp {

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

Win32Thread::Win32Thread(ThreadFunction const& threadFunction)
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

Win32Thread::Win32Thread(ThreadFunction const& threadFunction, ThreadAttributes const& threadAttributes)
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

Win32Thread::~Win32Thread()
{
    join();
}

bool Win32Thread::join()
{
    if (m_joinable) {
        DWORD result = WaitForSingleObject(m_thread, INFINITE);
        CloseHandle(m_thread);
        m_joinable = false;
        return result == WAIT_OBJECT_0;
    }

    return false;
}

} // namespace

#endif // ACTS_PLATFORM
