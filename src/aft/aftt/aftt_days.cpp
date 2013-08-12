#include <aftt_days.h>
#include <aftt_weeks.h>
#include <iostream>

namespace aftt {

Days::Days()
: m_days(0)
{}

Days::Days(int64_t days)
: m_days(days)
{}

Days::Days(Weeks const& weeks)
: m_days(weeks.value() * 7)
{}

Days::~Days()
{}

int64_t Days::value() const
{
    return m_days;
}

bool operator==(Days const& lhs, Days const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Days const& lhs, Days const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Days const& lhs, Days const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Days const& lhs, Days const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Days const& lhs, Days const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Days const& lhs, Days const& rhs)
{
    return lhs.value() >= rhs.value();
}

std::ostream& operator<<(std::ostream& os, Days const& days)
{
    return os << days.value();
}

} // namespace
