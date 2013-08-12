#ifndef INCLUDED_AEGIS_AFTT_SECONDS_H
#define INCLUDED_AEGIS_AFTT_SECONDS_H

#include <afts_stdint.h>
#include <iosfwd>

namespace aftt {

class Minutes;
class Hours;
class Days;

class Seconds
{
public:
    Seconds();
    
    Seconds(int64_t seconds);

    explicit Seconds(Minutes const& minutes);

    explicit Seconds(Hours const& hours);
    
    explicit Seconds(Days const& days);
    
    ~Seconds();

    // postfix ++ operator
    Seconds operator++(int);
    
    // prefix ++ operator
    Seconds& operator++();
    
    // postfix -- operator
    Seconds operator--(int);
    
    // prefix -- operator
    Seconds& operator--();
    
    Seconds& operator+=(Seconds const& rhs);
    
    Seconds& operator-=(Seconds const& rhs);
    
    int64_t value() const;
    
private:
    int64_t m_seconds;
};

Seconds operator+(Seconds const& lhs, Seconds const& rhs);

Seconds operator-(Seconds const& lhs, Seconds const& rhs);

bool operator==(Seconds const& lhs, Seconds const& rhs);

bool operator!=(Seconds const& lhs, Seconds const& rhs);

bool operator<(Seconds const& lhs, Seconds const& rhs);

bool operator>(Seconds const& lhs, Seconds const& rhs);

bool operator<=(Seconds const& lhs, Seconds const& rhs);

bool operator>=(Seconds const& lhs, Seconds const& rhs);

std::ostream& operator<<(std::ostream& os, Seconds const& seconds);

} // namespace

#endif // INCLUDED
