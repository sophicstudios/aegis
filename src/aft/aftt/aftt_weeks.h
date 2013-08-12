#ifndef INCLUDED_AEGIS_AFTT_WEEKS_H
#define INCLUDED_AEGIS_AFTT_WEEKS_H

#include <afts_stdint.h>

namespace aftt {

class Weeks
{
public:
    Weeks();
    
    Weeks(int32_t weeks);
    
    ~Weeks();
    
    int32_t value() const;
    
private:
    int32_t m_weeks;
};

} // namespace

#endif // INCLUDED
