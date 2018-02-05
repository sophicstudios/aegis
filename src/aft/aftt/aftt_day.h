#ifndef INCLUDED_AEGIS_AFTT_DAY_H
#define INCLUDED_AEGIS_AFTT_DAY_H

namespace aftt {

class Day
{
public:
    Day();
    
    explicit Day(unsigned int day);
    
    ~Day();
    
    unsigned int value() const;

private:
    unsigned int m_day;
};

bool operator==(Day const& lhs, Day const& rhs);
bool operator!=(Day const& lhs, Day const& rhs);
bool operator<(Day const& lhs, Day const& rhs);
bool operator<=(Day const& lhs, Day const& rhs);
bool operator>(Day const& lhs, Day const& rhs);
bool operator>=(Day const& lhs, Day const& rhs);

} // namespace

#endif // INCLUDED
