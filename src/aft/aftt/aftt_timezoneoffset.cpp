#include <aftt_timezoneoffset.h>

namespace aftt {

TimezoneOffset::TimezoneOffset()
: m_value(0)
{}

TimezoneOffset::TimezoneOffset(short value)
: m_value(value)
{
}

TimezoneOffset::~TimezoneOffset()
{}

short TimezoneOffset::value() const
{
    return m_value;
}

} // namespace
