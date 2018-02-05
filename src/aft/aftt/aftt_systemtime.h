#ifndef INCLUDED_AEGIS_AFTT_SYSTEMTIME_H
#define INCLUDED_AEGIS_AFTT_SYSTEMTIME_H

#include <aftt_datetimetz.h>
#include <aftt_datetimeinterval.h>

namespace aftt {

struct SystemTime
{
    ///
    /// Returns a datetime interval representing the amount of elapsed time
    /// since Unix epoch (1970-01-01T00:00:00.000+00:00)
    ///
    static DatetimeInterval now();

    ///
    /// Returns a DateTimeTz object representing now in UTC
    ///
    static DatetimeTz nowAsDatetimeUTC();
    
    ///
    /// Returns a DateTimeTz object representing now in the machine's local timezone
    ///
    static DatetimeTz nowAsDatetimeLocal();
    
    ///
    /// Returns a DateTimeTz object representing the Unix epoch
    ///
    static DatetimeTz epochAsDatetimeUTC();
};

} // namespace

#endif // INCLUDED
