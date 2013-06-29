#include <aftt_day.h>
#include <aftu_exception.h>

namespace aegis {
namespace aftt {

namespace {

unsigned int validateDay(unsigned int day)
{
    if (day > 0 && day < 32) {
        return day;
    }
    else {
        throw aftu::Exception() << "Not a valid day";
    }
}

} // namespace

Day::Day()
: m_day(1)
{}

Day::Day(unsigned int day)
: m_day(validateDay(day))
{}

Day::~Day()
{}

unsigned int Day::value() const
{
    return m_day;
}

bool operator==(Day const& lhs, Day const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Day const& lhs, Day const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Day const& lhs, Day const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Day const& lhs, Day const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Day const& lhs, Day const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Day const& lhs, Day const& rhs)
{
    return lhs.value() >= rhs.value();
}

} // namespace
} // namespace
