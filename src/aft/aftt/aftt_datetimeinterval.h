#ifndef INCLUDED_AEGIS_AFTT_DATETIMEINTERVAL_H
#define INCLUDED_AEGIS_AFTT_DATETIMEINTERVAL_H

#include <aftt_days.h>
#include <aftt_hours.h>
#include <aftt_minutes.h>
#include <aftt_seconds.h>
#include <aftt_milliseconds.h>
#include <aftt_microseconds.h>
#include <aftt_nanoseconds.h>
#include <afts_stdint.h>
#include <iosfwd>

namespace aftt {

class DatetimeInterval
{
    friend class Time;

public:
    DatetimeInterval();
    
    explicit DatetimeInterval(
        Days const& days,
        Hours const& hours = Hours(0),
        Minutes const& minutes = Minutes(0),
        Seconds const& seconds = Seconds(0),
        Nanoseconds const& nanoseconds = Nanoseconds(0));

    explicit DatetimeInterval(Days const& days);
    
    explicit DatetimeInterval(Hours const& hours);
    
    explicit DatetimeInterval(Minutes const& minutes);
    
    explicit DatetimeInterval(Seconds const& seconds);
    
    explicit DatetimeInterval(Milliseconds const& milliseconds);
    
    explicit DatetimeInterval(Microseconds const& microseconds);
    
    explicit DatetimeInterval(Nanoseconds const& nanoseconds);
    
    explicit DatetimeInterval(Seconds const& seconds, Nanoseconds const& nanoseconds);
    
    ~DatetimeInterval();

    DatetimeInterval& operator+=(DatetimeInterval const& rhs);
    
    DatetimeInterval& operator-=(DatetimeInterval const& lhs);
            
    Days days() const;
    
    Hours hours() const;
    
    Minutes minutes() const;
    
    Seconds seconds() const;
    
    Milliseconds milliseconds() const;
    
    Microseconds microseconds() const;
    
    Nanoseconds nanoseconds() const;
    
    double totalSeconds() const;
    
private:
    friend DatetimeInterval operator+(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend DatetimeInterval operator-(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend DatetimeInterval operator-(DatetimeInterval const& value);
    friend bool operator==(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend bool operator!=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend bool operator<(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend bool operator>(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend bool operator<=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    friend bool operator>=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);
    
    int64_t m_seconds;
    int64_t m_nanoseconds;
};

DatetimeInterval operator+(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

DatetimeInterval operator-(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

DatetimeInterval operator-(DatetimeInterval const& value);

bool operator==(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

bool operator!=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

bool operator<(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

bool operator>(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

bool operator<=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

bool operator>=(DatetimeInterval const& lhs, DatetimeInterval const& rhs);

std::ostream& operator<<(std::ostream& os, DatetimeInterval const& rhs);

} // namespace

#endif // INCLUDED
