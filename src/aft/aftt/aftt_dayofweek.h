#ifndef INCLUDED_AEGIS_AFTT_DAYOFWEEK
#define INCLUDED_AEGIS_AFTT_DAYOFWEEK

namespace aegis {
namespace aftt {

class Date;

struct DayOfWeek
{
    enum Day {
        Day_SUNDAY = 0,
        Day_MONDAY,
        Day_TUESDAY,
        Day_WEDNESDAY,
        Day_THURSDAY,
        Day_FRIDAY,
        Day_SATURDAY
    };

    Day getDay(Date const& date);
};

} // namespace
} // namespace

#endif // INCLUDED
