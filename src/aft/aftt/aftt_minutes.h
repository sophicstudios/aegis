#ifndef INCLUDED_AEGIS_AFTT_MINUTES_H
#define INCLUDED_AEGIS_AFTT_MINUTES_H

#include <afts_stdint.h>
#include <iosfwd>

namespace aegis {
namespace aftt {

class Hours;
class Days;

class Minutes
{
public:
    Minutes();
    
    Minutes(int64_t minutes);

    explicit Minutes(Hours const& hours);

    explicit Minutes(Days const& days);

    ~Minutes();
    
    int64_t value() const;
    
private:
    int64_t m_minutes;
};

std::ostream& operator<<(std::ostream& os, Minutes const& minutes);

} // namespace
} // namespace

#endif // INCLUDED
