#include <aftt_datetimeinterval.h>
#include <aftt_days.h>
#include <aftt_hours.h>
#include <aftt_minutes.h>
#include <aftt_seconds.h>
#include <aftt_milliseconds.h>
#include <aftt_microseconds.h>
#include <aftt_nanoseconds.h>
#include <afts_stdint.h>
#include <ostream>
#include <iomanip>

namespace aegis {
namespace aftt {

namespace {

int64_t NANOSECONDS_PER_MICROSECOND = 1000;
int64_t NANOSECONDS_PER_MILLISECOND = NANOSECONDS_PER_MICROSECOND * 1000;
int64_t NANOSECONDS_PER_SECOND = NANOSECONDS_PER_MILLISECOND * 1000;
int64_t NANOSECONDS_PER_MINUTE = NANOSECONDS_PER_SECOND * 60;
int64_t NANOSECONDS_PER_HOUR = NANOSECONDS_PER_MINUTE * 60;
int64_t NANOSECONDS_PER_DAY = NANOSECONDS_PER_HOUR * 24;

int64_t MICROSECONDS_PER_MILLISECOND = 1000;
int64_t MICROSECONDS_PER_SECOND = MICROSECONDS_PER_MILLISECOND * 1000;
int64_t MICROSECONDS_PER_MINUTE = MICROSECONDS_PER_SECOND * 60;
int64_t MICROSECONDS_PER_HOUR = MICROSECONDS_PER_MINUTE * 60;
int64_t MICROSECONDS_PER_DAY = MICROSECONDS_PER_HOUR * 24;

int64_t MILLISECONDS_PER_SECOND = 1000;
int64_t MILLISECONDS_PER_MINUTE = MILLISECONDS_PER_SECOND * 60;
int64_t MILLISECONDS_PER_HOUR = MILLISECONDS_PER_MINUTE * 60;
int64_t MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * 24;

int64_t SECONDS_PER_MINUTE = 60;
int64_t SECONDS_PER_HOUR = SECONDS_PER_MINUTE * 60;
int64_t SECONDS_PER_DAY = SECONDS_PER_HOUR * 24;

} // namespace

DatetimeInterval::DatetimeInterval()
: m_seconds(0),
  m_nanoseconds(0)
{}

DatetimeInterval::DatetimeInterval(
    Seconds const& seconds,
    Nanoseconds const& nanoseconds)
: m_seconds(seconds.value()),
  m_nanoseconds(nanoseconds.value())
{}

DatetimeInterval::DatetimeInterval(
    Days const& days,
    Hours const& hours,
    Minutes const& minutes,
    Seconds const& seconds,
    Nanoseconds const& nanoseconds)
: m_seconds(seconds.value()
    + (minutes.value() * SECONDS_PER_MINUTE)
    + (hours.value() * SECONDS_PER_HOUR)
    + (days.value() * SECONDS_PER_DAY))
{
    if (nanoseconds.value() <= -NANOSECONDS_PER_SECOND || nanoseconds.value() >= NANOSECONDS_PER_SECOND) {
        m_seconds += nanoseconds.value() / NANOSECONDS_PER_SECOND;
        m_nanoseconds %= NANOSECONDS_PER_SECOND;
    }
    else {
        m_nanoseconds = nanoseconds.value();
    }
    
    if (m_seconds < 0 && m_nanoseconds > 0) {
        ++m_seconds;
        m_nanoseconds -= NANOSECONDS_PER_SECOND;
    }
    else if (m_seconds > 0 && m_nanoseconds < 0) {
        --m_seconds;
        m_nanoseconds += NANOSECONDS_PER_SECOND;
    }
}

DatetimeInterval::DatetimeInterval(Days const& days)
: m_seconds(days.value() * SECONDS_PER_DAY),
  m_nanoseconds(0)
{}

DatetimeInterval::DatetimeInterval(Hours const& hours)
: m_seconds(hours.value() * SECONDS_PER_HOUR),
  m_nanoseconds(0)
{}

DatetimeInterval::DatetimeInterval(Minutes const& minutes)
: m_seconds(minutes.value() * SECONDS_PER_MINUTE),
  m_nanoseconds(0)
{}

DatetimeInterval::DatetimeInterval(Seconds const& seconds)
: m_seconds(seconds.value()),
  m_nanoseconds(0)
{}

DatetimeInterval::DatetimeInterval(Milliseconds const& milliseconds)
: m_seconds(milliseconds.value() / MILLISECONDS_PER_SECOND),
  m_nanoseconds((milliseconds.value() % MILLISECONDS_PER_SECOND) * NANOSECONDS_PER_MILLISECOND)
{}

DatetimeInterval::DatetimeInterval(Microseconds const& microseconds)
: m_seconds(microseconds.value() / MICROSECONDS_PER_SECOND),
  m_nanoseconds((microseconds.value() % MICROSECONDS_PER_SECOND) * NANOSECONDS_PER_MICROSECOND)
{}

DatetimeInterval::DatetimeInterval(Nanoseconds const& nanoseconds)
: m_seconds(nanoseconds.value() / NANOSECONDS_PER_SECOND),
  m_nanoseconds(nanoseconds.value() % NANOSECONDS_PER_SECOND)
{}

DatetimeInterval::~DatetimeInterval()
{}

DatetimeInterval& DatetimeInterval::operator+=(DatetimeInterval const& rhs)
{
    m_nanoseconds += rhs.m_nanoseconds;
    m_seconds += (rhs.m_seconds + (m_nanoseconds / NANOSECONDS_PER_SECOND));
    m_nanoseconds %= NANOSECONDS_PER_SECOND;
    return *this;
}

DatetimeInterval& DatetimeInterval::operator-=(DatetimeInterval const& rhs)
{
    m_nanoseconds -= rhs.m_nanoseconds;
    m_seconds -= (rhs.m_seconds - (m_nanoseconds / NANOSECONDS_PER_SECOND));
    m_nanoseconds %= NANOSECONDS_PER_SECOND;
    return *this;
}

Days DatetimeInterval::days() const
{
    return Days(m_seconds / SECONDS_PER_DAY);
}

Hours DatetimeInterval::hours() const
{
    return Hours((m_seconds % SECONDS_PER_DAY) / SECONDS_PER_HOUR);
}

Minutes DatetimeInterval::minutes() const
{
    return Minutes((m_seconds % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE);
}

Seconds DatetimeInterval::seconds() const
{
    return Seconds(m_seconds % SECONDS_PER_MINUTE);
}

Milliseconds DatetimeInterval::milliseconds() const
{
    return Milliseconds((m_nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_MILLISECOND);
}

Microseconds DatetimeInterval::microseconds() const
{
    return Microseconds((m_nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_MICROSECOND);
}

Nanoseconds DatetimeInterval::nanoseconds() const
{
    return Nanoseconds(m_nanoseconds % NANOSECONDS_PER_SECOND);
}

double DatetimeInterval::totalSeconds() const
{
    return static_cast<double>(m_seconds) + static_cast<double>(m_nanoseconds) / NANOSECONDS_PER_SECOND;
}

DatetimeInterval operator+(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    int64_t nanoseconds = lhs.m_nanoseconds + rhs.m_nanoseconds;
    int64_t seconds = lhs.m_seconds + (rhs.m_seconds + (nanoseconds / NANOSECONDS_PER_SECOND));
    nanoseconds %= NANOSECONDS_PER_SECOND;
    return DatetimeInterval(Seconds(seconds), Nanoseconds(nanoseconds));
}

DatetimeInterval operator-(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    int64_t nanoseconds = lhs.m_nanoseconds - rhs.m_nanoseconds;
    int64_t seconds = lhs.m_seconds - (rhs.m_seconds - (nanoseconds / NANOSECONDS_PER_SECOND));
    nanoseconds %= NANOSECONDS_PER_SECOND;
    return DatetimeInterval(Seconds(seconds), Nanoseconds(nanoseconds));
}

DatetimeInterval operator-(DatetimeInterval const& value)
{
    return DatetimeInterval(Seconds(-value.m_seconds), Nanoseconds(-value.m_nanoseconds));
}

bool operator==(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return lhs.m_seconds == rhs.m_seconds && lhs.m_nanoseconds == rhs.m_nanoseconds;
}

bool operator!=(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return lhs.m_seconds != rhs.m_seconds || lhs.m_nanoseconds != rhs.m_nanoseconds;
}

bool operator<(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return lhs.m_seconds < rhs.m_seconds
        || (lhs.m_seconds == rhs.m_seconds && lhs.m_nanoseconds < rhs.m_nanoseconds);
}

bool operator<=(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return !(rhs < lhs);
}

bool operator>(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return lhs.m_seconds > rhs.m_seconds
        || (lhs.m_seconds == rhs.m_seconds && lhs.m_nanoseconds > rhs.m_nanoseconds);
}

bool operator>=(DatetimeInterval const& lhs, DatetimeInterval const& rhs)
{
    return !(rhs < lhs);
}

std::ostream& operator<<(std::ostream& os, DatetimeInterval const& rhs)
{
    return os << rhs.days() << "(d) "
        << std::setw(2) << std::setfill('0') << rhs.hours() << ":"
        << std::setw(2) << std::setfill('0') << rhs.minutes() << ":"
        << std::setw(2) << std::setfill('0') << rhs.seconds() << "."
        << std::setw(9) << std::setfill('0') << rhs.nanoseconds();
}

} // namespace
} // namespace
