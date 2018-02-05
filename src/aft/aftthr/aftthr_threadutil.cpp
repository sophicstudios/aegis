#include <aftthr_threadutil.h>
#include <aftthr_platform.h>

namespace aftthr {

#if defined(AFTTHR_PLATFORM_PTHREADS)

ThreadUtil::ResultCode ThreadUtil::sleep(aftt::DatetimeInterval const& interval)
{
    struct timespec request;
    request.tv_sec = static_cast<time_t>(interval.hours().value() * 3600
        + interval.minutes().value() * 60
        + interval.seconds().value());
    request.tv_nsec = static_cast<long>(interval.nanoseconds().value());

    struct timespec remaining;

    int result = nanosleep(&request, &remaining);
    if (result != 0) {
    }
    
    return ResultCode_OK;
}

ThreadUtil::ResultCode ThreadUtil::sleep(
    aftt::DatetimeInterval const& interval,
    aftt::DatetimeInterval* remainingInterval)
{
    struct timespec request;
    request.tv_sec = static_cast<time_t>(interval.hours().value() * 3600
        + interval.minutes().value() * 60
        + interval.seconds().value());
    request.tv_nsec = static_cast<long>(interval.nanoseconds().value());

    struct timespec remaining;

    int result = nanosleep(&request, &remaining);
    if (result != 0) {
    }

    if (remainingInterval) {
        *remainingInterval = aftt::DatetimeInterval(
            aftt::Days(0),
            aftt::Hours(0),
            aftt::Minutes(0),
            aftt::Seconds(remaining.tv_sec),
            aftt::Nanoseconds(remaining.tv_nsec));
    }
    
    return ResultCode_OK;
}

#elif defined(AFTTHR_PLATFORM_WINTHREADS)

void ThreadUtil::sleep(aftt::DatetimeInterval const& interval)
{
    ::Sleep(static_cast<DWORD>(interval.totalSeconds() * 1000));
}

#endif // AFTTHR_PLATFORM

} // namespace
