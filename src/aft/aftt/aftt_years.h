#ifndef INCLUDED_AEGIS_AFTT_YEARS_H
#define INCLUDED_AEGIS_AFTT_YEARS_H

#include <afts_stdint.h>

namespace aegis {
namespace aftt {

class Years
{
public:
    Years();
    
    Years(int64_t years);

    ~Years();
    
    int64_t value() const;
    
private:
    int64_t m_years;
};

} // namespace
} // namespace

#endif // INCLUDED
