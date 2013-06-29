#include <aftt_seconds.h>
#include <aftt_minutes.h>
#include <aftt_hours.h>
#include <aftt_days.h>
#include <iostream>

namespace aegis {
namespace aftt {

Seconds::Seconds()
: m_seconds(0)
{}

Seconds::Seconds(int64_t seconds)
: m_seconds(seconds)
{}

Seconds::Seconds(Minutes const& minutes)
: m_seconds(minutes.value() * 60)
{}

Seconds::Seconds(Hours const& hours)
: m_seconds(hours.value() * 60 * 60)
{}

Seconds::Seconds(Days const& days)
: m_seconds(days.value() * 24 * 60 * 60)
{}

Seconds::~Seconds()
{}

Seconds Seconds::operator++(int)
{
    Seconds result(m_seconds);
    ++m_seconds;
    return result;
}

Seconds& Seconds::operator++()
{
    ++m_seconds;
    return *this;
}

Seconds Seconds::operator--(int)
{
    Seconds result(m_seconds);
    --m_seconds;
    return result;
}

Seconds& Seconds::operator--()
{
    --m_seconds;
    return *this;
}

Seconds& Seconds::operator+=(Seconds const& seconds)
{
    m_seconds += seconds.m_seconds;
    return *this;
}

Seconds& Seconds::operator-=(Seconds const& seconds)
{
    m_seconds -= seconds.m_seconds;
    return *this;
}

int64_t Seconds::value() const
{
    return m_seconds;
}

Seconds operator+(Seconds const& lhs, Seconds const& rhs)
{
    return Seconds(lhs.value() + rhs.value());
}

Seconds operator-(Seconds const& lhs, Seconds const& rhs)
{
    return Seconds(lhs.value() - rhs.value());
}

bool operator==(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator>(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator<=(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>=(Seconds const& lhs, Seconds const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Seconds const& seconds)
{
    return os << seconds.value();
}

} // namespace
} // namespace
