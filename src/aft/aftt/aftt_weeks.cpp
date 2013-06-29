#include <aftt_weeks.h>

namespace aegis {
namespace aftt {

Weeks::Weeks()
: m_weeks(0)
{}

Weeks::Weeks(int64_t weeks)
: m_weeks(weeks)
{}

Weeks::~Weeks()
{}

int64_t Weeks::value() const
{
    return m_weeks;
}

} // namespace
} // namespace
