#include <actp_thread.h>

namespace actp {

Thread::Thread(Thread::Callback const& callback)
: m_nativeThread(callback)
{}

Thread::Thread(Thread::Callback const& callback, ThreadAttributes const& threadAttributes)
: m_nativeThread(callback, threadAttributes)
{}

Thread::~Thread()
{}

} // namespace
