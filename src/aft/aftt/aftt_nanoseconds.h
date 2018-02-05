#ifndef INCLUDED_AEGIS_AFTT_NANOSECONDS_H
#define INCLUDED_AEGIS_AFTT_NANOSECONDS_H

#include <afts_stdint.h>
#include <ostream>

namespace aftt {

class Days;
class Hours;
class Minutes;
class Seconds;
class Milliseconds;
class Microseconds;
class Nanoseconds;

class Nanoseconds
{
public:
    Nanoseconds();
    
    explicit Nanoseconds(int64_t nanoseconds);
    
    explicit Nanoseconds(Microseconds const& microseconds);
    
    explicit Nanoseconds(Milliseconds const& milliseconds);
    
    explicit Nanoseconds(Seconds const& seconds);
    
    explicit Nanoseconds(Minutes const& minutes);
    
    explicit Nanoseconds(Hours const& hours);
    
    explicit Nanoseconds(Days const& days);

    ~Nanoseconds();
    
    // postfix ++ operator
    Nanoseconds operator++(int);
    
    // prefix ++ operator
    Nanoseconds& operator++();
    
    // postfix -- operator
    Nanoseconds operator--(int);
    
    // prefix -- operator
    Nanoseconds& operator--();
    
    Nanoseconds& operator+=(Nanoseconds const& rhs);

    Nanoseconds& operator-=(Nanoseconds const& rhs);

    int64_t value() const;
    
private:
    int64_t m_nanoseconds;
};

Nanoseconds operator+(Nanoseconds const& lhs, Nanoseconds const& rhs);

Nanoseconds operator-(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator==(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator!=(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator<(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator>(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator<=(Nanoseconds const& lhs, Nanoseconds const& rhs);

bool operator>=(Nanoseconds const& lhs, Nanoseconds const& rhs);

std::ostream& operator<<(std::ostream& os, Nanoseconds const& nanoseconds);

} // namespace

#endif // INCLUDED
