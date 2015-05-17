#ifndef INCLUDE_AEGIS_ACTP_POSIXTHREAD_H
#define INCLUDE_AEGIS_ACTP_POSIXTHREAD_H

#include <acts_platform.h>
#include <actp_threadattributes.h>

#if defined(ACTS_PLATFORM_PTHREADS)

#include <pthread.h>
#include <functional>

namespace actp {

class PosixThread
{
public:
    typedef std::function<void (void)> Callback;

    PosixThread(Callback const& callback);

    PosixThread(Callback const& callback, ThreadAttributes const& threadAttributes);

    ~PosixThread();
    
    bool join();

private:
    PosixThread();
    PosixThread(PosixThread const&);
    PosixThread& operator=(PosixThread const&);
    
    pthread_t m_thread;
    bool m_joinable;
};

} // namespace

#endif // ACTS_PLATFORM

#endif // INCLUDE
