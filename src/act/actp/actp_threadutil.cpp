#include <actp_threadutil.h>
#include <acts_platform.h>

namespace aegis {
namespace actp {

#if defined(ACTS_PLATFORM_PTHREADS)

ThreadUtil::ResultCode ThreadUtil::sleep(aftt::TimeInterval const& interval)
{
    struct timespec request;
    request.tv_sec = interval.hours() * 3600 + interval.minutes() * 60 + interval.seconds();
    request.tv_nsec = interval.nanoseconds();

    struct timespec remaining;

    int result = nanosleep(&request, &remaining);
    if (result != 0) {
    }
    
    return ResultCode_OK;
}

ThreadUtil::ResultCode ThreadUtil::sleep(
    aftt::TimeInterval const& interval,
    aftt::TimeInterval* remainingInterval)
{
    struct timespec request;
    request.tv_sec = interval.hours() * 3600 + interval.minutes() * 60 + interval.seconds();
    request.tv_nsec = interval.nanoseconds();

    struct timespec remaining;

    int result = nanosleep(&request, &remaining);
    if (result != 0) {
    }

    if (remainingInterval) {
        *remainingInterval = aftt::TimeInterval(0, 0, remaining.tv_sec, 0, 0, remaining.tv_nsec);
    }
    
    return ResultCode_OK;
}

#elif defined(ACTS_PLATFORM_WINTHREADS)

void ThreadUtil::sleep(aftt::TimeInterval const& interval)
{
    ::Sleep(static_cast<DWORD>(interval.totalSeconds() * 1000));
}

#endif // ACTS_PLATFORM

} // namespace
} // namespace
