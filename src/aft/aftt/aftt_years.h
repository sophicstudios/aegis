#ifndef INCLUDED_AEGIS_AFTT_YEARS_H
#define INCLUDED_AEGIS_AFTT_YEARS_H

#include <afts_stdint.h>

namespace aftt {

class Years
{
public:
    Years();
    
    explicit Years(int32_t years);

    ~Years();
    
    int32_t value() const;
    
private:
    int32_t m_years;
};

} // namespace

#endif // INCLUDED
