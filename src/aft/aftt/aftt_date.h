#ifndef INCLUDED_AEGIS_AFTT_DATE_H
#define INCLUDED_AEGIS_AFTT_DATE_H

#include <aftt_year.h>
#include <aftt_month.h>
#include <aftt_day.h>
#include <aftt_days.h>

#include <iosfwd>

namespace aftt {

/**
 * The Date class represents a single day in time. The year is
 * any valid integer. The month and day are constrained to the
 * months of the year and the days of the given month, both starting
 * from 1. ([1-12] months and [1-(28, 29, 30 or 31)] days.
 */
class Date
{
public:
    static bool isValid(Year const& year, Month const& month, Day const& day);

    Date();

    Date(Year const& year, Month const& month, Day const& day);

    ~Date();

    Date& operator+=(Days const& days);

    Date& operator-=(Days const& days);
    
    Date& operator++();

    Date operator++(int);

    Date& operator--();

    Date operator--(int);

    bool validateAndSetDate(Year const& year, Month const& month, Day const& day);

    bool setDate(Year const& year, Month const& month, Day const& day);

    void getYearMonthDay(Year& year, Month& month, Day& day) const;
    
    Year year() const;

    Month month() const;

    Day day() const;

    std::ostream& print(std::ostream& os) const;

private:
    friend Days operator-(Date const& lhs, Date const& rhs);
    friend bool operator==(Date const& lhs, Date const& rhs);
    friend bool operator!=(Date const& lhs, Date const& rhs);
    friend bool operator<(Date const& lhs, Date const& rhs);
    friend bool operator<=(Date const& lhs, Date const& rhs);
    friend bool operator>(Date const& lhs, Date const& rhs);
    friend bool operator>=(Date const& lhs, Date const& rhs);
    friend std::ostream& operator<<(std::ostream& os, Date const& date);
    
    uint64_t m_serial;
};

Date operator+(Date const& date, Days const& days);

Date operator-(Date const& date, Days const& days);

Days operator-(Date const& lhs, Date const& rhs);

bool operator==(Date const& lhs, Date const& rhs);

bool operator!=(Date const& lhs, Date const& rhs);

bool operator<(Date const& lhs, Date const& rhs);

bool operator<=(Date const& lhs, Date const& rhs);

bool operator>(Date const& lhs, Date const& rhs);

bool operator>=(Date const& lhs, Date const& rhs);

std::ostream& operator<<(std::ostream& os, Date const& date);

} // namespace\

#endif // INCLUDED
