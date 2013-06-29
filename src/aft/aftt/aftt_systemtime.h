#ifndef INCLUDED_AEGIS_AFTT_SYSTEMTIME_H
#define INCLUDED_AEGIS_AFTT_SYSTEMTIME_H

#include <aftt_datetime.h>
#include <aftt_datetimeinterval.h>

namespace aegis {
namespace aftt {

struct SystemTime
{
    ///
    /// Returns a datetime interval representing the amount of elapsed time
    /// since Unix epoch (1970-01-01T00:00:00.000+00:00)
    ///
    static DatetimeInterval now();

    ///
    /// Returns a DateTime object representing now in UTC
    ///
    static Datetime nowAsDatetimeUTC();
    
    ///
    /// Returns a DateTime object representing now in the machine's local timezone
    ///
    static Datetime nowAsDatetimeLocal();
    
    ///
    /// Returns a DateTime object representing the Unix epoch
    ///
    static Datetime epochAsDatetimeUTC();
};

} // namespace
} // namespace

#endif // INCLUDED
