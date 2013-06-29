#include <aftt_month.h>
#include <aftu_exception.h>

namespace aegis {
namespace aftt {

namespace {

unsigned int monthNameToValue(Month::Name name)
{
    switch (name) {
    case Month::Name_JANUARY: return 1; break;
    case Month::Name_FEBRUARY: return 2; break;
    case Month::Name_MARCH: return 3; break;
    case Month::Name_APRIL: return 4; break;
    case Month::Name_MAY: return 5; break;
    case Month::Name_JUNE: return 6; break;
    case Month::Name_JULY: return 7; break;
    case Month::Name_AUGUST: return 8; break;
    case Month::Name_SEPTEMBER: return 9; break;
    case Month::Name_OCTOBER: return 10; break;
    case Month::Name_NOVEMBER: return 11; break;
    case Month::Name_DECEMBER: return 12; break;
    default: throw aftu::Exception() << "Unknown Month Name [ name: " << name << " ]";
    }
}

Month::Name monthValueToName(unsigned int value)
{
    switch (value) {
    case 1: return Month::Name_JANUARY; break;
    case 2: return Month::Name_FEBRUARY; break;
    case 3: return Month::Name_MARCH; break;
    case 4: return Month::Name_APRIL; break;
    case 5: return Month::Name_MAY; break;
    case 6: return Month::Name_JUNE; break;
    case 7: return Month::Name_JULY; break;
    case 8: return Month::Name_AUGUST; break;
    case 9: return Month::Name_SEPTEMBER; break;
    case 10: return Month::Name_OCTOBER; break;
    case 11: return Month::Name_NOVEMBER; break;
    case 12: return Month::Name_DECEMBER; break;
    default: throw aftu::Exception() << "Invalid month [ value: " << value << " ]";
    }
}

} // namespace

Month::Month()
: m_value(1)
{}

Month::Month(Month::Name name)
: m_value(monthNameToValue(name))
{}

Month::Month(unsigned int month)
: m_value(month)
{
    if (m_value < 1 || m_value > 12) {
        throw aftu::Exception() << "Invalid Month";
    }
}

Month::~Month()
{}

Month::Name Month::name() const
{
    return monthValueToName(m_value);
}

unsigned int Month::value() const
{
    return m_value;
}

bool operator==(Month const& lhs, Month const& rhs)
{
    return lhs.value() == rhs.value();
}

bool operator!=(Month const& lhs, Month const& rhs)
{
    return lhs.value() != rhs.value();
}

bool operator<(Month const& lhs, Month const& rhs)
{
    return lhs.value() < rhs.value();
}

bool operator<=(Month const& lhs, Month const& rhs)
{
    return lhs.value() <= rhs.value();
}

bool operator>(Month const& lhs, Month const& rhs)
{
    return lhs.value() > rhs.value();
}

bool operator>=(Month const& lhs, Month const& rhs)
{
    return lhs.value() >= rhs.value();
}

} // namespace
} // namespace
