#ifndef INCLUDED_AEGIS_AFTT_DAYS_H
#define INCLUDED_AEGIS_AFTT_DAYS_H

#include <afts_stdint.h>
#include <ostream>

namespace aftt {

class Weeks;

class Days
{
public:
    Days();
    
    explicit Days(int64_t days);
    
    Days(Weeks const& weeks);
    
    ~Days();
    
    int64_t value() const;
    
private:
    int64_t m_days;
};

bool operator==(Days const& lhs, Days const& rhs);
bool operator!=(Days const& lhs, Days const& rhs);
bool operator<(Days const& lhs, Days const& rhs);
bool operator<=(Days const& lhs, Days const& rhs);
bool operator>(Days const& lhs, Days const& rhs);
bool operator>=(Days const& lhs, Days const& rhs);
std::ostream& operator<<(std::ostream& os, Days const& days);

} // namespace

#endif // INCLUDED
