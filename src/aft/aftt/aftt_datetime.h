#ifndef INCLUDED_AEGIS_AFTT_DATETIME_H
#define INCLUDED_AEGIS_AFTT_DATETIME_H

#include <aftt_date.h>
#include <aftt_time.h>
#include <aftt_datetimeinterval.h>

namespace aftt {

class Datetime
{
public:
    Datetime();
    
    Datetime(Date const& date, Time const& time);

    Datetime(
        Year const& year,
        Month const& month,
        Day const& day);

    Datetime(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second);

    Datetime(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second,
        Millisecond const& millisecond);

    Datetime(
        Year const& year,
        Month const& month,
        Day const& day,
        Hour const& hour,
        Minute const& minute,
        Second const& second,
        Nanosecond const& nanosecond);

    Date const& date() const;
    
    Time const& time() const;
    
    Year year() const;
    
    Month month() const;
    
    Day day() const;
    
    Hour hour() const;
    
    Minute minute() const;
    
    Second second() const;
    
    Millisecond millisecond() const;
    
    Microsecond microsecond() const;
    
    Nanosecond nanosecond() const;
    
    Datetime& operator+=(DatetimeInterval const& interval);
    
    Datetime& operator-=(DatetimeInterval const& interval);
    
private:
    friend Datetime operator+(Datetime const& lhs, DatetimeInterval const& rhs);
    friend Datetime operator-(Datetime const& lhs, DatetimeInterval const& rhs);
    friend DatetimeInterval operator-(Datetime const& lhs, Datetime const& rhs);
    friend bool operator==(Datetime const& lhs, Datetime const& rhs);
    friend bool operator!=(Datetime const& lhs, Datetime const& rhs);
    friend bool operator<(Datetime const& lhs, Datetime const& rhs);
    friend bool operator<=(Datetime const& lhs, Datetime const& rhs);
    friend bool operator>(Datetime const& lhs, Datetime const& rhs);
    friend bool operator>=(Datetime const& lhs, Datetime const& rhs);
    friend std::ostream& operator<<(std::ostream& os, Datetime const& datetime);

    Date m_date;
    Time m_time;
};

Datetime operator+(Datetime const& lhs, DatetimeInterval const& rhs);

Datetime operator-(Datetime const& lhs, DatetimeInterval const& rhs);

DatetimeInterval operator-(Datetime const& lhs, Datetime const& rhs);

bool operator==(Datetime const& lhs, Datetime const& rhs);

bool operator!=(Datetime const& lhs, Datetime const& rhs);

bool operator<(Datetime const& lhs, Datetime const& rhs);

bool operator<=(Datetime const& lhs, Datetime const& rhs);

bool operator>(Datetime const& lhs, Datetime const& rhs);

bool operator>=(Datetime const& lhs, Datetime const& rhs);

std::ostream& operator<<(std::ostream& os, Datetime const& datetime);

} // namespace

#endif // INCLUDED
