#ifndef INCLUDED_AEGIS_AFTT_WEEKS_H
#define INCLUDED_AEGIS_AFTT_WEEKS_H

#include <afts_stdint.h>

namespace aegis {
namespace aftt {

class Weeks
{
public:
    Weeks();
    
    Weeks(int64_t weeks);
    
    ~Weeks();
    
    int64_t value() const;
    
private:
    int64_t m_weeks;
};

} // namespace
} // namespace

#endif // INCLUDED
