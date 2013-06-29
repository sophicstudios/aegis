#include <aftt_minutes.h>
#include <aftt_hours.h>
#include <aftt_days.h>
#include <iostream>

namespace aegis {
namespace aftt {

Minutes::Minutes()
: m_minutes(0)
{}

Minutes::Minutes(int64_t minutes)
: m_minutes(minutes)
{}

Minutes::Minutes(Hours const& hours)
: m_minutes(hours.value() * 60)
{}

Minutes::Minutes(Days const& days)
: m_minutes(days.value() * 24 * 60)
{}

Minutes::~Minutes()
{}

int64_t Minutes::value() const
{
    return m_minutes;
}

std::ostream& operator<<(std::ostream& os, Minutes const& minutes)
{
    return os << minutes.value();
}

} // namespace
} // namespace
