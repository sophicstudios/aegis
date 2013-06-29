#ifndef INCLUDE_AEGIS_ACTP_MUTEX_H
#define INCLUDE_AEGIS_ACTP_MUTEX_H

#include <acts_platform.h>

#if defined(ACTS_PLATFORM_PTHREADS)
#include <actp_posixmutex.h>
#elif defined(ACTS_PLATFORM_WINTHREADS)
#include <actp_win32mutex.h>
#endif

#include <iosfwd>

namespace aegis {
namespace actp {

/**
 * A basic mutex class with lock and unlock semantics. Multiple threads
 * may use a Mutex to synchronize access to a shared resource. When multiple
 * threads call the lock() method, only one will proceed while the other
 * threads will block until the thread currently holding the lock calls
 * unlock. At this point, another thread will be released to take hold of the
 * lock, again leaving the remaining threads in a blocked state until the mutex
 * is released.
 *
 * Example code is below:
 *
 * \code
 * // f() may be called my multiple threads simultaneously.
 * void f(Mutex& mutex)
 * {
 *   // lock the mutex to ensure exclusive access to the
 *   // shared resource for one thread at a time.
 *   mutex.lock();
 *   ...
 *   // Use the shared resource
 *   ...
 *   mutex.unlock();
 * }
 * \endcode
 */
class Mutex
{
    friend class Condition;

public:
    /**
     * Creates a new Mutex object in the unlocked state.
     */
    Mutex();

    /**
     * Destroys the underlying mutex object. If the object is
     * in the locked state, the results are undefined.
     */
    ~Mutex();

    /**
     * Locks the mutex. Only one thread at a time may put the
     * mutex into the locked state. All other threads will
     * block on this call until the first thread calls unlock.
     */
    MutexResult lock();

    /**
     * Unlocks the mutex. Any threads that are blocked on a call
     * to lock() will be released so that one of them will next
     * acquire the mutex.
     */
    MutexResult unlock();

private:
    Mutex(Mutex const&);
    Mutex& operator=(Mutex const&);
    
#if defined(ACTS_PLATFORM_PTHREADS)
    typedef PosixMutex NativeMutex;
#elif defined(ACTS_PLATFORM_WINTHREADS)
    typedef Win32Mutex NativeMutex;
#endif

    NativeMutex m_nativeMutex;
};

inline MutexResult Mutex::lock()
{
    return m_nativeMutex.lock();
}

inline MutexResult Mutex::unlock()
{
    return m_nativeMutex.unlock();
}

} // namespace
} // namespace

#endif // INCLUDE
