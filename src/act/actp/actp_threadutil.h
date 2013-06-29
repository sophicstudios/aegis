#ifndef INCLUDE_AEGIS_ACTP_THREADUTIL_H
#define INCLUDE_AEGIS_ACTP_THREADUTIL_H

#include <actp_thread.h>
#include <aftt_timeinterval.h>

namespace aegis {
namespace actp {

struct ThreadUtil
{
    enum ResultCode {
        ResultCode_OK,
        ResultCode_SLEEP_INTERRUPTED
    };
    
    /**
     * Suspends the current thread for the specified time intervale.
     * The granularity of the interval is limited by the capabilities
     * of the system and could be up to nanosecond resolution.
     *
     * @param interval The time interval
     */
    static ResultCode sleep(aftt::TimeInterval const& interval);
    
    /**
     * Suspends the current thread for the specified time intervale.
     * The granularity of the interval is limited by the capabilities
     * of the system and could be up to nanosecond resolution. If the
     * sleep is interrupted for any reason, the TimeIntervale pointed
     * to by 'remaining' will contain the sleep time left after
     * the interruption.
     *
     * @param interval The time interval
     * @param remaining The time remaining after the sleep ends
     */
    static ResultCode sleep(
        aftt::TimeInterval const& interval,
        aftt::TimeInterval* remainingInterval);
};

} // namespace
} // namespace

#endif // INCLUDE
