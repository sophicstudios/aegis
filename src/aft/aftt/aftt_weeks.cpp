#include <aftt_weeks.h>

namespace aftt {

Weeks::Weeks()
: m_weeks(0)
{}

Weeks::Weeks(int32_t weeks)
: m_weeks(weeks)
{}

Weeks::~Weeks()
{}

int32_t Weeks::value() const
{
    return m_weeks;
}

} // namespace
