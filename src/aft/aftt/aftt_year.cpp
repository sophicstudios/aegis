#include <aftt_year.h>

namespace aftt {

Year::Year()
: m_year(0)
{}

Year::Year(unsigned int year)
: m_year(year)
{}

Year::~Year()
{}

unsigned int Year::value() const
{
    return m_year;
}

bool operator==(Year const& lhs, Year const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Year const& lhs, Year const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Year const& lhs, Year const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Year const& lhs, Year const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Year const& lhs, Year const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Year const& lhs, Year const& rhs)
{
    return lhs.value() >= rhs.value();
}

} // namespace
