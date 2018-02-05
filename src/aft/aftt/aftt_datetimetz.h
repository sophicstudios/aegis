#ifndef INCLUDED_AEGIS_AFTT_DATETIMETZ_H
#define INCLUDED_AEGIS_AFTT_DATETIMETZ_H

#include <aftt_datetime.h>
#include <aftt_timezoneoffset.h>

namespace aftt {

class DatetimeTz : public Datetime
{
public:
    DatetimeTz();

    DatetimeTz(Datetime const& datetime, TimezoneOffset const& offset);

    DatetimeTz(Date const& date, Time const& time, TimezoneOffset const& offset);

    DatetimeTz(
        Year const& year,
        Month const& month,
        Day const& day,
        TimezoneOffset const& offset);

    DatetimeTz(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second,
        TimezoneOffset const& offset);

    DatetimeTz(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second,
        Millisecond const& millisecond,
        TimezoneOffset const& offset);

    DatetimeTz(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second,
        Nanosecond const& nanosecond,
        TimezoneOffset const& offset);

    virtual ~DatetimeTz();

    TimezoneOffset offset() const;

private:
    friend DatetimeTz operator+(DatetimeTz const& lhs, DatetimeInterval const& rhs);
    friend DatetimeTz operator-(DatetimeTz const& lhs, DatetimeInterval const& rhs);
    friend std::ostream& operator<<(std::ostream& os, DatetimeTz const& datetime);

    TimezoneOffset m_offset;
};

DatetimeTz operator+(DatetimeTz const& lhs, DatetimeInterval const& rhs);

DatetimeTz operator-(DatetimeTz const& lhs, DatetimeInterval const& rhs);

std::ostream& operator<<(std::ostream& os, DatetimeTz const& datetime);

} // namespace

#endif // INCLUDED
