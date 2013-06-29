#include <aftt_years.h>

namespace aegis {
namespace aftt {

Years::Years()
: m_years(0)
{}

Years::Years(int64_t years)
: m_years(years)
{}

Years::~Years()
{}

int64_t Years::value() const
{
    return m_years;
}

} // namespace
} // namespace
