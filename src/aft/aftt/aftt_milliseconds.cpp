#include <aftt_milliseconds.h>
#include <aftt_seconds.h>
#include <aftt_minutes.h>
#include <aftt_hours.h>
#include <aftt_days.h>

namespace aftt {

Milliseconds::Milliseconds()
: m_milliseconds(0)
{}

Milliseconds::Milliseconds(int64_t milliseconds)
: m_milliseconds(milliseconds)
{}

Milliseconds::Milliseconds(Seconds const& seconds)
: m_milliseconds(seconds.value() * 1000)
{}

Milliseconds::Milliseconds(Minutes const& minutes)
: m_milliseconds(minutes.value() * 60 * 1000)
{}

Milliseconds::Milliseconds(Hours const& hours)
: m_milliseconds(hours.value() * 60 * 60 * 1000)
{}

Milliseconds::Milliseconds(Days const& days)
: m_milliseconds(days.value() * 24 * 60 * 60 * 1000)
{}

Milliseconds::~Milliseconds()
{}

int64_t Milliseconds::value() const
{
    return m_milliseconds;
}

std::ostream& operator<<(std::ostream& os, Milliseconds const& milliseconds)
{
    return os << milliseconds.value();
}

} // namespace
