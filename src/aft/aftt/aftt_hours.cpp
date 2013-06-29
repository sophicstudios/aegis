#include <aftt_hours.h>
#include <aftt_days.h>
#include <iostream>

namespace aegis {
namespace aftt {

Hours::Hours()
: m_hours(0)
{}

Hours::Hours(int64_t hours)
: m_hours(hours)
{}

Hours::Hours(Days const& days)
: m_hours(days.value() * 24)
{}

Hours::~Hours()
{}

int64_t Hours::value() const
{
    return m_hours;
}

std::ostream& operator<<(std::ostream& os, Hours const& hours)
{
    return os << hours.value();
}

} // namespace
} // namespace
