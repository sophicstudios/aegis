#include <aftt_systemtime.h>
#include <aftu_exception.h>
#include <afts_assert.h>
#include <afts_os.h>

#if defined(AFTS_OS_WIN32)

#include <afts_windows.h>

#elif defined(AFTS_OS_APPLE)

#include <mach/clock.h>
#include <mach/mach.h>
#include <mach/clock_types.h>
#include <time.h>

#else // POSIX

#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#endif // AFTS_OS

namespace aftt {

namespace {
    static Datetime s_epoch(Year(1970), Month(1), Day(1), Hour(0), Minute(0), Second(0), Nanosecond(0));
}

#if defined(AFTS_OS_WIN32)

DatetimeInterval SystemTime::now()
{
    return DatetimeInterval();
}

DatetimeTz SystemTime::nowAsDatetimeUTC()
{
    SYSTEMTIME time;
    GetSystemTime(&time);

    return DatetimeTz(
        Year(time.wYear),
        Month(time.wMonth),
        Day(time.wDay),
        Hour(time.wHour),
        Minute(time.wMinute),
        Second(time.wSecond),
        Millisecond(time.wMilliseconds),
        TimezoneOffset(0));
}

DatetimeTz SystemTime::nowAsDatetimeLocal()
{
    SYSTEMTIME time;
    GetLocalTime(&time);
    
    return DatetimeTz(
        Year(time.wYear),
        Month(time.wMonth),
        Day(time.wDay),
        Hour(time.wHour),
        Minute(time.wMinute),
        Second(time.wSecond),
        Millisecond(time.wMilliseconds),
        TimezoneOffset(0));
}

#elif defined(AFTS_OS_APPLE)

DatetimeInterval SystemTime::now()
{
    clock_serv_t cclock;
    mach_timespec_t mts;
    
    memset(&mts, 0, sizeof(mach_timespec_t));
    
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    
    /*
    std::cout << "SystemTime::now ["
        << " cclock:" << cclock
        << " tv_sec: " << mts.tv_sec
        << " tv_nsec: " << mts.tv_nsec
        << " ]" << std::endl;
    */
    
    DatetimeInterval result(
        Days(0),
        Hours(0),
        Minutes(0),
        Seconds(mts.tv_sec),
        Nanoseconds(mts.tv_nsec));
    
    return result;
}

DatetimeTz SystemTime::nowAsDatetimeUTC()
{
    Datetime d(s_epoch + now());
    return DatetimeTz(d, TimezoneOffset(0));
}

DatetimeTz SystemTime::nowAsDatetimeLocal()
{
    clock_serv_t cclock;
    mach_timespec_t mts;
    
    memset(&mts, 0, sizeof(mach_timespec_t));
    
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    
    tm localTm;
    memset(&localTm, 0, sizeof(tm));
    
    time_t sec = static_cast<time_t>(mts.tv_sec);
    localtime_r(&sec, &localTm);
    
    return DatetimeTz(
        Year(localTm.tm_year + 1900),
        Month(localTm.tm_mon + 1),
        Day(localTm.tm_mday),
        Hour(localTm.tm_hour),
        Minute(localTm.tm_min),
        Second(localTm.tm_sec),
        Nanosecond(mts.tv_nsec),
        TimezoneOffset(localTm.tm_gmtoff / 60));
}

#elif defined(_POSIX_TIMERS) // POSIX

DatetimeInterval SystemTime::now()
{
    timespec ts;
    memset(&ts, 0, sizeof(timespec));
    
    int result = clock_gettime(CLOCK_REALTIME, &ts);
    if (0 != result)
    {
        throw aftu::Exception() << "clock_gettime failed [ error: " << afts::ErrorUtil::translateErrno(errno) << " ]";
    }

    return DatetimeInterval(
        Days(0),
        Hours(0),
        Minutes(0),
        Seconds(ts.tv_sec),
        Nanoseconds(ts.tv_nsec));
}

DatetimeTz SystemTime::nowAsDatetimeUTC()
{
    Datetime d(s_epoch + now());
    return DatetimeTz(d, TimezoneOffset(0));
}
    
DatetimeTz SystemTime::nowAsDatetimeLocal()
{
    timespec ts;
    memset(&ts, 0, sizeof(timespec));
    
    int result = clock_gettime(CLOCK_REALTIME, &ts);
    if (0 != result)
    {
        throw aftu::Exception() << "clock_gettime failed [ error: " << afts::ErrorUtil::translateErrno(errno) << " ]";
    }
    
    tm localTm;
    memset(&localTm, 0, sizeof(tm));
    
    localtime_r(&(ts.tv_sec), &localTm);
    
    return DatetimeTz(
        Year(localTm.tm_year + 1900),
        Month(localTm.tm_mon + 1),
        Day(localTm.tm_mday),
        Hour(localTm.tm_hour),
        Minute(localTm.tm_min),
        Second(localTm.tm_sec),
        Nanosecond(ts.tv_nsec),
        TimezoneOffset(0));
}

#endif // AFTS_OS

DatetimeTz SystemTime::epochAsDatetimeUTC()
{
    return DatetimeTz(s_epoch, TimezoneOffset(0));
}

} // namespace
