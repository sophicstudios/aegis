#include <aftt_datetimetz.h>
#include <iomanip>
#include <cstdlib>

namespace aftt {

DatetimeTz::DatetimeTz()
: m_offset(0)
{}

DatetimeTz::DatetimeTz(Datetime const& datetime, TimezoneOffset const& offset)
: Datetime(datetime),
  m_offset(offset)
{}

DatetimeTz::DatetimeTz(Date const& date, Time const& time, TimezoneOffset const& offset)
: Datetime(date, time),
  m_offset(offset)
{}

DatetimeTz::DatetimeTz(
    Year const& year,
    Month const& month,
    Day const& day,
    TimezoneOffset const& offset)
: Datetime(year, month, day),
  m_offset(offset)
{}

DatetimeTz::DatetimeTz(
    Year const& year,
    Month const& month,
    Day const& day,
    Hour const& hour,
    Minute const& minute,
    Second const& second,
    TimezoneOffset const& offset)
: Datetime(year, month, day, hour, minute, second),
  m_offset(offset)
{}

DatetimeTz::DatetimeTz(
    Year const& year,
    Month const& month,
    Day const& day,
    Hour const& hour,
    Minute const& minute,
    Second const& second,
    Millisecond const& millisecond,
    TimezoneOffset const& offset)
: Datetime(year, month, day, hour, minute, second, millisecond),
  m_offset(offset)
{}

DatetimeTz::DatetimeTz(
    Year const& year,
    Month const& month,
    Day const& day,
    Hour const& hour,
    Minute const& minute,
    Second const& second,
    Nanosecond const& nanosecond,
    TimezoneOffset const& offset)
: Datetime(year, month, day, hour, minute, second, nanosecond),
  m_offset(offset)
{}

DatetimeTz::~DatetimeTz()
{}

TimezoneOffset DatetimeTz::offset() const
{
    return m_offset;
}

DatetimeTz operator+(DatetimeTz const& lhs, DatetimeInterval const& rhs)
{
    DatetimeTz result(lhs);
    result += rhs;
    return result;
}

DatetimeTz operator-(DatetimeTz const& lhs, DatetimeInterval const& rhs)
{
    DatetimeTz result(lhs);
    result -= rhs;
    return result;
}

std::ostream& operator<<(std::ostream& os, DatetimeTz const& datetime)
{
    short offset = datetime.offset().value();
    short hours = std::abs(offset) / 60;
    short minutes = std::abs(offset) % 60;
    return os << datetime.date() << "T" << datetime.time()
        << (offset < 0 ? '-' : '+')
        << std::setw(2) << std::setfill('0') << hours
        << std::setw(2) << std::setfill('0') << minutes;
}

} // namespace
