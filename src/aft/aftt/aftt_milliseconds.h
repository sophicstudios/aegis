#ifndef INCLUDED_AEGIS_AFTT_MILLISECONDS_H
#define INCLUDED_AEGIS_AFTT_MILLISECONDS_H

#include <afts_stdint.h>
#include <iosfwd>

namespace aftt {

class Days;
class Hours;
class Minutes;
class Seconds;

class Milliseconds
{
public:
    Milliseconds();
    
    Milliseconds(int64_t milliseconds);

    explicit Milliseconds(Seconds const& seconds);
    
    explicit Milliseconds(Minutes const& minutes);

    explicit Milliseconds(Hours const& hours);
    
    explicit Milliseconds(Days const& days);
    
    ~Milliseconds();
    
    int64_t value() const;
    
private:
    int64_t m_milliseconds;
};

std::ostream& operator<<(std::ostream& os, Milliseconds const& milliseconds);

} // namespace

#endif // INCLUDED
