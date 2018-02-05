#ifndef INCLUDE_AEGIS_AFTTHR_THREAD_H
#define INCLUDE_AEGIS_AFTTHR_THREAD_H

#include <aftthr_platform.h>
#include <aftthr_threadattributes.h>

#if defined(AFTTHR_PLATFORM_PTHREADS)
#include <pthread.h>
#elif defined(AFTTHR_PLATFORM_WINTHREADS)
#include <afts_windows.h>
#endif

#include <functional>

namespace aftthr {

class Thread
{
public:
    typedef std::function<void (void)> Callback;

    Thread(Callback const& callback);

    Thread(Callback const& threadFunction, ThreadAttributes const& threadAttributes);

    ~Thread();
    
    bool join();

private:
    Thread();
    Thread(Thread const&);
    Thread& operator=(Thread const&);

    bool m_joinable;

    #if defined(AFTTHR_PLATFORM_PTHREADS)
        pthread_t m_thread;
    #elif defined(AFTTHR_PLATFORM_WINTHREADS)
        HANDLE m_thread;
        DWORD m_threadId;
    #endif
};

} // namespace

#endif // INCLUDE
