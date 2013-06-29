#include <aftt_microseconds.h>
#include <aftt_milliseconds.h>
#include <aftt_seconds.h>
#include <aftt_minutes.h>
#include <aftt_hours.h>
#include <aftt_days.h>
#include <iostream>

namespace aegis {
namespace aftt {

Microseconds::Microseconds()
: m_microseconds(0)
{}

Microseconds::Microseconds(int64_t microseconds)
: m_microseconds(microseconds)
{}

Microseconds::Microseconds(Milliseconds const& milliseconds)
: m_microseconds(milliseconds.value() * 1000)
{}

Microseconds::Microseconds(Seconds const& seconds)
: m_microseconds(seconds.value() * 1000 * 1000)
{}

Microseconds::Microseconds(Minutes const& minutes)
: m_microseconds(minutes.value() * 60 * 1000 * 1000)
{}

Microseconds::Microseconds(Hours const& hours)
: m_microseconds(hours.value() * 60 * 60 * 1000 * 1000)
{}

Microseconds::Microseconds(Days const& days)
: m_microseconds(days.value() * 24 * 60 * 60 * 1000 * 1000)
{}

int64_t Microseconds::value() const
{
    return m_microseconds;
}

std::ostream& operator<<(std::ostream& os, Microseconds const& microseconds)
{
    return os << microseconds.value();
}

} // namespace
} // namespace
