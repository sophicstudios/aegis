#ifndef INCLUDED_AEGIS_AFTT_MICROSECONDS_H
#define INCLUDED_AEGIS_AFTT_MICROSECONDS_H

#include <afts_stdint.h>
#include <iosfwd>

namespace aftt {

class Days;
class Hours;
class Minutes;
class Seconds;
class Milliseconds;

class Microseconds
{
public:
    Microseconds();
    
    Microseconds(int64_t microseconds);
    
    explicit Microseconds(Milliseconds const& milliseconds);
    
    explicit Microseconds(Seconds const& seconds);
    
    explicit Microseconds(Minutes const& minutes);
    
    explicit Microseconds(Hours const& hours);
    
    explicit Microseconds(Days const& days);
    
    ~Microseconds();
    
    int64_t value() const;
    
private:
    int64_t m_microseconds;
};

std::ostream& operator<<(std::ostream& os, Microseconds const& microseconds);

} // namespae

#endif // INCLUDED
