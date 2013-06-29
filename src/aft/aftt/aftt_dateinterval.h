#ifndef INCLUDED_AEGIS_AFTT_DATEINTERVAL_H
#define INCLUDED_AEGIS_AFTT_DATEINTERVAL_H

namespace aegis {
namespace aftt {

class DateInterval
{
public:
    DateInterval();
    
    DateInterval(int years, int months = 0, int days = 0);
    
    ~DateInterval();
    
    
};

class YearInterval : public DateInterval
{
public:
    YearInterval(int years);
};

class MonthInterval : public DateInterval
{
public: 
    MonthInterval(int months);
};

class WeekInterval : public DateInterval
{
public:
    WeekInterval(int weeks);
};

class DayInterval : public DateInterval
{
public:
    DayInterval(int days);
};

} // namespace
} // namespace

#endif // INCLUDED
