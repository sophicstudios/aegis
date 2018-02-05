#ifndef INCLUDED_AEGIS_AFTT_MONTH_H
#define INCLUDED_AEGIS_AFTT_MONTH_H

namespace aftt {

class Month
{
public:
    enum Name {
        Name_JANUARY = 1,
        Name_FEBRUARY = 2,
        Name_MARCH = 3,
        Name_APRIL = 4,
        Name_MAY = 5,
        Name_JUNE = 6,
        Name_JULY = 7,
        Name_AUGUST = 8,
        Name_SEPTEMBER = 9,
        Name_OCTOBER = 10,
        Name_NOVEMBER = 11,
        Name_DECEMBER = 12,
    };

    Month();
    
    explicit Month(Name name);
    
    explicit Month(unsigned int month);
    
    ~Month();
    
    Name name() const;
    
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Month const& lhs, Month const& rhs);
bool operator!=(Month const& lhs, Month const& rhs);
bool operator<(Month const& lhs, Month const& rhs);
bool operator<=(Month const& lhs, Month const& rhs);
bool operator>(Month const& lhs, Month const& rhs);
bool operator>=(Month const& lhs, Month const& rhs);

} // namespace

#endif // INCLUDED
