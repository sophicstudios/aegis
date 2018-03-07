#include <aftt_datetime.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace aftt;

namespace {

bool verify(Datetime const& dt,
    int year, int month, int day,
    int hour, int minute, int second, int millisecond)
{
    Year y = dt.year();
    Month m = dt.month();
    Day d = dt.day();

    Hour h = dt.hour();
    Minute mi = dt.minute();
    Second s = dt.second();
    Millisecond ms = dt.millisecond();
    
    return Year(year) == y
        && Month(month) == m
        && Day(day) == d
        && Hour(hour) == h
        && Minute(minute) == mi
        && Second(second) == s
        && Millisecond(millisecond) == ms;
}

} // namespace

Describe d("aftt_datetime", []
{
    it("Construction", [&]
    {
        Datetime dt1(Year(2010), Month(10), Day(31));

        expect(verify(dt1, 2010, 10, 31, 0, 0, 0, 0)).toBeTrue();
        
        Datetime dt2(Year(2010), Month(10), Day(31), Hour(5), Minute(0), Second(0));
        
        Datetime dt3(Year(2010), Month(10), Day(31), Hour(5), Minute(31), Second(0));
        
        Datetime dt4(Year(2010), Month(10), Day(31), Hour(5), Minute(31), Second(55));
        
        Datetime dt5(Year(2010), Month(10), Day(31), Hour(5), Minute(31), Second(55), Millisecond(999));
    });
});

} // namespace


