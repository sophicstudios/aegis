#ifndef INCLUDE_AEGIS_ACTP_THREAD_H
#define INCLUDE_AEGIS_ACTP_THREAD_H

#include <actp_threadattributes.h>
#include <acts_platform.h>

#if defined(ACTS_PLATFORM_PTHREADS)
#include <actp_posixthread.h>
#endif

#include <functional>

namespace actp {

#if defined(ACTS_PLATFORM_PTHREADS)
typedef PosixThread NativeThread;
#endif

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

    NativeThread m_nativeThread;
};

inline bool Thread::join()
{
    return m_nativeThread.join();
}

} // namespace

#endif // INCLUDE
