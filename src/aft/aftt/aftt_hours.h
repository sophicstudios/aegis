#ifndef INCLUDED_AEGIS_AFTT_HOURS_H
#define INCLUDED_AEGIS_AFTT_HOURS_H

#include <afts_stdint.h>
#include <ostream>

namespace aftt {

class Days;

class Hours
{
public:
    Hours();
    
    explicit Hours(int64_t hours);
    
    explicit Hours(Days const& days);
    
    ~Hours();
    
    int64_t value() const;
    
private:
    int64_t m_hours;
};

std::ostream& operator<<(std::ostream& os, Hours const& hours);

} // namespace

#endif // INCLUDED
