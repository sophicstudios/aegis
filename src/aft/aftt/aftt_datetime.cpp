#include <aftt_datetime.h>
#include <ostream>

namespace aftt {

Datetime::Datetime()
{}

Datetime::Datetime(Date const& date, Time const& time)
: m_date(date),
  m_time(time)
{}
    
Datetime::Datetime(
    Year const& year,
    Month const& month,
    Day const& day,
    Hour const& hour,
    Minute const& minute,
    Second const& second,
    Nanosecond const& nanosecond)
: m_date(year, month, day),
  m_time(hour, minute, second, nanosecond)
{}

Date const& Datetime::date() const
{
    return m_date;
}
    
Time const& Datetime::time() const
{
    return m_time;
}

Year Datetime::year() const
{
    return m_date.year();
}

Month Datetime::month() const
{
    return m_date.month();
}

Day Datetime::day() const
{
    return m_date.day();
}

Hour Datetime::hour() const
{
    return m_time.hour();
}

Minute Datetime::minute() const
{
    return m_time.minute();
}

Second Datetime::second() const
{
    return m_time.second();
}

Millisecond Datetime::millisecond() const
{
    return m_time.millisecond();
}

Microsecond Datetime::microsecond() const
{
    return m_time.microsecond();
}

Nanosecond Datetime::nanosecond() const
{
    return m_time.nanosecond();
}

Datetime& Datetime::operator+=(DatetimeInterval const& interval)
{
    m_date += m_time.add(interval);
    return *this;
}
    
Datetime& Datetime::operator-=(DatetimeInterval const& interval)
{
    m_date += m_time.subtract(interval);
    return *this;
}

Datetime operator+(Datetime const& lhs, DatetimeInterval const& rhs)
{
    Datetime result(lhs);
    result += rhs;
    return result;
}

Datetime operator-(Datetime const& lhs, DatetimeInterval const& rhs)
{
    Datetime result(lhs);
    result -= rhs;
    return result;
}

DatetimeInterval operator-(Datetime const& lhs, Datetime const& rhs)
{
    DatetimeInterval timeInterval = lhs.m_time - rhs.m_time;
    return DatetimeInterval(
        Days(Days(lhs.m_date - rhs.m_date).value() + timeInterval.days().value()),
        timeInterval.hours(),
        timeInterval.minutes(),
        timeInterval.seconds(),
        timeInterval.nanoseconds());
}

bool operator==(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.m_date == rhs.m_date && lhs.m_time == rhs.m_time;
}

bool operator!=(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.m_time != rhs.m_time || lhs.m_date != rhs.m_date;
}

bool operator<(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.m_date < rhs.m_date
        || (lhs.m_date == rhs.m_date && lhs.m_time < rhs.m_time);
}

bool operator<=(Datetime const& lhs, Datetime const& rhs)
{
    return lhs.m_date < rhs.m_date
        || (lhs.m_date == rhs.m_date && lhs.m_time <= rhs.m_time);
}

bool operator>(Datetime const& lhs, Datetime const& rhs)
{
    return rhs.m_date < lhs.m_date
        || (rhs.m_date == lhs.m_date && rhs.m_time < lhs.m_time);
}

bool operator>=(Datetime const& lhs, Datetime const& rhs)
{
    return rhs.m_date < lhs.m_date
        || (rhs.m_date == lhs.m_date && rhs.m_time <= lhs.m_time);
}

std::ostream& operator<<(std::ostream& os, Datetime const& dateTime)
{
    return os << dateTime.m_date << " " << dateTime.m_time;
}

} // namespace
