#include <aftt_nanoseconds.h>
#include <aftt_microseconds.h>
#include <aftt_milliseconds.h>
#include <aftt_seconds.h>
#include <aftt_minutes.h>
#include <aftt_hours.h>
#include <aftt_days.h>
#include <iostream>

namespace aftt {

Nanoseconds::Nanoseconds()
: m_nanoseconds(0)
{}

Nanoseconds::Nanoseconds(int64_t nanoseconds)
: m_nanoseconds(nanoseconds)
{}

Nanoseconds::Nanoseconds(Microseconds const& microseconds)
: m_nanoseconds(microseconds.value() * 1000)
{}

Nanoseconds::Nanoseconds(Milliseconds const& milliseconds)
: m_nanoseconds(milliseconds.value() * 1000 * 1000)
{}

Nanoseconds::Nanoseconds(Seconds const& seconds)
: m_nanoseconds(seconds.value() * 1000 * 1000 * 1000)
{}

Nanoseconds::Nanoseconds(Minutes const& minutes)
: m_nanoseconds(minutes.value() * 60 * 1000 * 1000 * 1000)
{}

Nanoseconds::Nanoseconds(Hours const& hours)
: m_nanoseconds(hours.value() * 60 * 60 * 1000 * 1000 * 1000)
{}

Nanoseconds::Nanoseconds(Days const& days)
: m_nanoseconds(days.value() * 24 * 60 * 60 * 1000 * 1000 * 1000)
{}

Nanoseconds::~Nanoseconds()
{}

Nanoseconds Nanoseconds::operator++(int)
{
    Nanoseconds result(m_nanoseconds);
    ++m_nanoseconds;
    return result;
}

Nanoseconds& Nanoseconds::operator++()
{
    ++m_nanoseconds;
    return *this;
}

Nanoseconds Nanoseconds::operator--(int)
{
    Nanoseconds result(m_nanoseconds);
    --m_nanoseconds;
    return result;
}

Nanoseconds& Nanoseconds::operator--()
{
    --m_nanoseconds;
    return *this;
}

Nanoseconds& Nanoseconds::operator+=(Nanoseconds const& nanoseconds)
{
    m_nanoseconds += nanoseconds.m_nanoseconds;
    return *this;
}

Nanoseconds& Nanoseconds::operator-=(Nanoseconds const& nanoseconds)
{
    m_nanoseconds -= nanoseconds.m_nanoseconds;
    return *this;
}

int64_t Nanoseconds::value() const
{
    return m_nanoseconds;
}

Nanoseconds operator+(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return Nanoseconds(lhs.value() + rhs.value());
}

Nanoseconds operator-(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return Nanoseconds(lhs.value() - rhs.value());
}

bool operator==(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator>(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator<=(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>=(Nanoseconds const& lhs, Nanoseconds const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Nanoseconds const& nanoseconds)
{
    return os << nanoseconds.value();
}

} // namespace
