#include <actp_thread.h>

namespace aegis {
namespace actp {

Thread::Thread(ThreadFunction const& threadFunction)
: m_nativeThread(threadFunction)
{}

Thread::Thread(ThreadFunction const& threadFunction, ThreadAttributes const& threadAttributes)
: m_nativeThread(threadFunction, threadAttributes)
{}

Thread::~Thread()
{}


} // namespace
} // namespace
