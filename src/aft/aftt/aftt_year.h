#ifndef INCLUDED_AEGIS_AFTT_YEAR_H
#define INCLUDED_AEGIS_AFTT_YEAR_H

namespace aftt {

class Year
{
public:
    Year();
    
    Year(unsigned int year);
    
    ~Year();
    
    unsigned int value() const;

private:
    unsigned int m_year;
};

bool operator==(Year const& lhs, Year const& rhs);
bool operator!=(Year const& lhs, Year const& rhs);
bool operator<(Year const& lhs, Year const& rhs);
bool operator<=(Year const& lhs, Year const& rhs);
bool operator>(Year const& lhs, Year const& rhs);
bool operator>=(Year const& lhs, Year const& rhs);

} // namespace

#endif // INCLUDED
