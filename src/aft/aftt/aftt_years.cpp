#include <aftt_years.h>

namespace aftt {

Years::Years()
: m_years(0)
{}

Years::Years(int32_t years)
: m_years(years)
{}

Years::~Years()
{}

int32_t Years::value() const
{
    return m_years;
}

} // namespace
