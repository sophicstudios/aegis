#include <aftt_datetime.h>
#include <aunit.h>

namespace aftt {

using namespace aunit;

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
    
    return year == y
        && month == m
        && day == d
        && hour == h
        && minute == mi
        && second == s
        && millisecond == ms;
}

} // namespace

describe("aftt_datetime", []
{
    it("Construction", [&]
    {
        Datetime dt1(2010, 10, 31);

        expect(verify(dt1, 2010, 10, 31, 0, 0, 0, 0)).toBeTrue();
        
        Datetime dt2(2010, 10, 31, 5);
        
        Datetime dt3(2010, 10, 31, 5, 31);
        
        Datetime dt4(2010, 10, 31, 5, 31, 55);
        
        Datetime dt5(2010, 10, 31, 5, 31, 55, 999);
    });
});

} // namespace


