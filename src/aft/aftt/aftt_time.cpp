#include <aftt_time.h>
#include <aftt_datetimeinterval.h>
#include <aftu_exception.h>
#include <afts_assert.h>
#include <ostream>
#include <iomanip>
#include <cassert>

namespace aftt {

namespace {

const uint64_t HOURS_PER_DAY = 24;

const uint64_t MINUTES_PER_HOUR = 60;

const uint64_t SECONDS_PER_MINUTE = 60;
const uint64_t SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;
const uint64_t SECONDS_PER_DAY = SECONDS_PER_HOUR * HOURS_PER_DAY;

const uint64_t MILLISECONDS_PER_SECOND = 1000;

const uint64_t MICROSECONDS_PER_MILLISECOND = 1000;

const uint64_t NANOSECONDS_PER_MICROSECOND = 1000;
const uint64_t NANOSECONDS_PER_MILLISECOND = NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MILLISECOND;
const uint64_t NANOSECONDS_PER_SECOND = NANOSECONDS_PER_MILLISECOND * MILLISECONDS_PER_SECOND;
const uint64_t NANOSECONDS_PER_MINUTE = NANOSECONDS_PER_SECOND * SECONDS_PER_MINUTE;
const uint64_t NANOSECONDS_PER_HOUR = NANOSECONDS_PER_MINUTE * MINUTES_PER_HOUR;
const uint64_t NANOSECONDS_PER_DAY = NANOSECONDS_PER_HOUR * HOURS_PER_DAY;

inline uint64_t fromComponents(
    Hour const& hour,
    Minute const& minute,
    Second const& second,
    Nanosecond const& nanosecond)
{
    return hour.value() * NANOSECONDS_PER_HOUR
        + minute.value() * NANOSECONDS_PER_MINUTE
        + second.value() * NANOSECONDS_PER_SECOND
        + nanosecond.value();
}

inline unsigned int getHour(uint64_t nanoseconds)
{
    return static_cast<unsigned int>(nanoseconds / NANOSECONDS_PER_HOUR);
}

inline unsigned int getMinute(uint64_t nanoseconds)
{
    return static_cast<unsigned int>((nanoseconds % NANOSECONDS_PER_HOUR) / NANOSECONDS_PER_MINUTE);
}

inline unsigned int getSecond(uint64_t nanoseconds)
{
    return static_cast<unsigned int>((nanoseconds % NANOSECONDS_PER_MINUTE) / NANOSECONDS_PER_SECOND);
}

inline unsigned int getNanosecond(uint64_t nanoseconds)
{
    return static_cast<unsigned int>(nanoseconds % NANOSECONDS_PER_SECOND);
}

} // namespace

Hour::Hour(unsigned int value)
: m_value(value)
{
    AFTS_ASSERT(m_value <= 24);
}

Hour::Hour(unsigned int value, Hour::Split split)
: m_value(split == Split_AM ? (value == 12 ? 0 : value) : (value == 12 ? 12 : value + 12))
{
    AFTS_ASSERT(m_value <= 24);
}

Hour::~Hour()
{}

unsigned int Hour::value() const
{
    return m_value;
}

bool operator==(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Hour const& lhs, Hour const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Hour const& hour)
{
    os << hour.value();
    return os;
}

Minute::Minute(unsigned int value)
: m_value(value)
{
    if (m_value > 59) {
        throw aftu::Exception() << "Invalid Minute";
    }
}

Minute::~Minute()
{}

unsigned int Minute::value() const
{
    return m_value;
}

bool operator==(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Minute const& lhs, Minute const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Minute const& minute)
{
    os << minute.value();
    return os;
}

Second::Second(unsigned int value)
: m_value(value)
{
    if (m_value > 59) {
        throw aftu::Exception() << "Invalid Second";
    }
}

Second::~Second()
{}

unsigned int Second::value() const
{
    return m_value;
}

bool operator==(Second const& lhs, Second const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Second const& lhs, Second const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Second const& lhs, Second const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Second const& lhs, Second const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Second const& lhs, Second const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Second const& lhs, Second const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Second const& second)
{
    os << second.value();
    return os;
}

Millisecond::Millisecond(unsigned int value)
: m_value(value)
{
    if (m_value > 999) {
        throw aftu::Exception() << "Invalid Millisecond";
    }
}

Millisecond::~Millisecond()
{}

unsigned int Millisecond::value() const
{
    return m_value;
}

bool operator==(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Millisecond const& lhs, Millisecond const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Millisecond const& millisecond)
{
    os << millisecond.value();
    return os;
}

Microsecond::Microsecond(unsigned int value)
: m_value(value)
{
    if (m_value > 999999) {
        throw aftu::Exception() << "Invalid Microsecond";
    }
}

Microsecond::~Microsecond()
{}

unsigned int Microsecond::value() const
{
    return m_value;
}

bool operator==(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Microsecond const& lhs, Microsecond const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Microsecond const& microsecond)
{
    os << microsecond.value();
    return os;
}

Nanosecond::Nanosecond(unsigned int value)
: m_value(value)
{
    if (m_value > 999999999) {
        throw aftu::Exception() << "Invalid Nanosecond";
    }
}

Nanosecond::~Nanosecond()
{}

unsigned int Nanosecond::value() const
{
    return m_value;
}

bool operator==(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Nanosecond const& lhs, Nanosecond const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Nanosecond const& nanosecond)
{
    os << nanosecond.value();
    return os;
}

Time::Time()
: m_nanoseconds(NANOSECONDS_PER_DAY)
{}

Time::Time(Hour const& hour,
    Minute const& minute,
    Second const& second,
    Nanosecond const& nanosecond)
: m_nanoseconds(fromComponents(hour, minute, second, nanosecond))
{}

Time::Time(Time const& time)
: m_nanoseconds(time.m_nanoseconds)
{}

Time::~Time()
{}

Time& Time::operator=(Time const& time)
{
    m_nanoseconds = time.m_nanoseconds;
    return *this;
}

void Time::setHour(Hour const& hour)
{
    m_nanoseconds -= getHour(m_nanoseconds) * NANOSECONDS_PER_HOUR;
    m_nanoseconds += hour.value() * NANOSECONDS_PER_HOUR;
}

void Time::setMinute(Minute const& minute)
{
    m_nanoseconds -= getMinute(m_nanoseconds) * NANOSECONDS_PER_MINUTE;
    m_nanoseconds += minute.value() * NANOSECONDS_PER_MINUTE;
}

void Time::setSecond(Second const& second)
{
    m_nanoseconds -= getSecond(m_nanoseconds) * NANOSECONDS_PER_SECOND;
    m_nanoseconds += second.value() * NANOSECONDS_PER_SECOND;
}

void Time::setNanosecond(Nanosecond const& nanosecond)
{
    m_nanoseconds -= getNanosecond(m_nanoseconds);
    m_nanoseconds += nanosecond.value();
}

Time& Time::operator+=(DatetimeInterval const& interval)
{
    add(interval);
    return *this;
}

Time& Time::operator-=(DatetimeInterval const& interval)
{
    subtract(interval);
    return *this;
}

Days Time::add(DatetimeInterval const& interval)
{
    int64_t totalIntervalSeconds = interval.m_seconds;
    int32_t normalizedSeconds = static_cast<int32_t>(totalIntervalSeconds % SECONDS_PER_DAY);
    int64_t days = totalIntervalSeconds / SECONDS_PER_DAY;
    int64_t normalizedNanoseconds = (normalizedSeconds * NANOSECONDS_PER_SECOND) + interval.nanoseconds().value();
    
    if (normalizedNanoseconds < 0) {
        m_nanoseconds += (NANOSECONDS_PER_DAY + normalizedNanoseconds);
        days += ((m_nanoseconds / NANOSECONDS_PER_DAY) - 1);
    }
    else {   
        m_nanoseconds += normalizedNanoseconds;
        days += m_nanoseconds / NANOSECONDS_PER_DAY;
    }
    
    m_nanoseconds %= NANOSECONDS_PER_DAY;
    
    return Days(days);
}

Days Time::subtract(DatetimeInterval const& interval)
{
    int64_t totalIntervalSeconds = interval.m_seconds;
    int32_t normalizedSeconds = static_cast<int32_t>(totalIntervalSeconds % SECONDS_PER_DAY);
    int64_t days = totalIntervalSeconds / SECONDS_PER_DAY;
    int64_t normalizedNanoseconds = (normalizedSeconds * NANOSECONDS_PER_SECOND) + interval.nanoseconds().value();
    
    if (normalizedNanoseconds < 0) {
        m_nanoseconds -= normalizedNanoseconds;
        days -= (m_nanoseconds / NANOSECONDS_PER_DAY);
    }
    else {
        m_nanoseconds += (NANOSECONDS_PER_DAY - normalizedNanoseconds);
        days -= ((m_nanoseconds / NANOSECONDS_PER_DAY) - 1);
    }
    
    m_nanoseconds %= NANOSECONDS_PER_DAY;
    
    return Days(days);
}

Hour Time::hour() const
{
    return Hour(static_cast<unsigned int>(m_nanoseconds / NANOSECONDS_PER_HOUR));
}

Minute Time::minute() const
{
    return Minute(static_cast<unsigned int>((m_nanoseconds % NANOSECONDS_PER_HOUR) / NANOSECONDS_PER_MINUTE));
}

Second Time::second() const
{
    return Second(static_cast<unsigned int>((m_nanoseconds % NANOSECONDS_PER_MINUTE) / NANOSECONDS_PER_SECOND));
}

Millisecond Time::millisecond() const
{
    return Millisecond(static_cast<unsigned int>((m_nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_MILLISECOND));
}

Microsecond Time::microsecond() const
{
    return Microsecond(static_cast<unsigned int>((m_nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_MICROSECOND));
}

Nanosecond Time::nanosecond() const
{
    return Nanosecond(static_cast<unsigned int>(m_nanoseconds % NANOSECONDS_PER_SECOND));
}

std::ostream& Time::print(std::ostream& os) const
{
    os << std::setw(2) << std::setfill('0') << hour() << ":"
        << std::setw(2) << std::setfill('0') << minute() << ":"
        << std::setw(2) << std::setfill('0') << second() << "."
        << std::setw(3) << std::setfill('0') << static_cast<int>(nanosecond().value() / 1000000.0);

    return os;
}

Time operator+(Time const& lhs, DatetimeInterval const& rhs)
{
    Time result(lhs);
    result += rhs;
    return result;
}

Time operator-(Time const& lhs, DatetimeInterval const& rhs)
{
    Time result(lhs);
    result -= rhs;
    return result;
}

DatetimeInterval operator-(Time const& lhs, Time const& rhs)
{
    return DatetimeInterval(Days(0), Hours(0), Minutes(0), Seconds(0), Nanoseconds(lhs.m_nanoseconds - rhs.m_nanoseconds));
}

bool operator==(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds == rhs.m_nanoseconds;
}

bool operator!=(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds != rhs.m_nanoseconds;
}

bool operator<(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds < rhs.m_nanoseconds;
}

bool operator<=(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds <= rhs.m_nanoseconds;
}

bool operator>(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds > rhs.m_nanoseconds;
}

bool operator>=(Time const& lhs, Time const& rhs)
{
    return lhs.m_nanoseconds >= rhs.m_nanoseconds;
}

std::ostream& operator<<(std::ostream& os, Time const& time)
{
    return time.print(os);
}

} // namespace
