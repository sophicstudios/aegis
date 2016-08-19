#include <aftt_time.h>
#include <aftt_datetimeinterval.h>
#include <aunit.h>
#include <iostream>

namespace {

using namespace aunit;
using namespace aftt;

namespace {

bool verify(Time const& t, unsigned int hour, unsigned int minute, unsigned int second, unsigned int millisecond)
{
    return t.hour() == hour
        && t.minute() == minute
        && t.second() == second
        && t.millisecond() == millisecond;
}

} // namespace

Describe d("aftt_time", []
{
    it("Construction", [&]
    {
        Time t1;

        expect(verify(t1, 24, 0, 0, 0)).toBeTrue();

        Time t2(1, 23);

        expect(verify(t2, 1, 23, 0, 0)).toBeTrue();

        Time t3(1, 23, 0, 0);

        expect(verify(t3, 1, 23, 0, 0)).toBeTrue();

        Days count = t3.add(DatetimeInterval(Seconds(60), Nanoseconds(0))); // 60 seconds

        expect(verify(t3, 1, 24, 0, 0)).toBeTrue();
        expect(count).toEqual(0);

        count = t3.add(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1 hour, 10 minutes

        expect(verify(t3, 2, 34, 0, 0)).toBeTrue();
        expect(count).toEqual(2);

        count = t3.add(DatetimeInterval(Days(1), Hours(1))); // 1 day, 1 hour

        expect(verify(t3, 3, 34, 0, 0)).toBeTrue();
        expect(count).toEqual(1);
    });

    it("Assignment", [&]
    {
        Time t1;

        expect(verify(t1, 24, 0, 0, 0)).toBeTrue();

        t1.setHour(6);

        expect(verify(t1, 6, 0, 0, 0)).toBeTrue();

        t1.setMinute(23);

        expect(verify(t1, 6, 23, 0, 0)).toBeTrue();
        
        t1.setSecond(59);

        expect(verify(t1, 6, 23, 59, 0)).toBeTrue();

        t1.setNanosecond(981000000);

        expect(verify(t1, 6, 23, 59, 981)).toBeTrue();
    });

    it("Addition", [&]
    {
        Time t1(1, 23, 0, 0);

        expect(verify(t1, 1, 23, 0, 0)).toBeTrue();

        Days count = t1.add(DatetimeInterval(Days(0), Hours(0), Minutes(1)));

        expect(verify(t1, 1, 24, 0, 0)).toBeTrue();
        expect(count).toEqual(0);

        count = t1.add(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1, hour, 10 minutes

        expect(verify(t1, 2, 34, 0, 0)).toBeTrue();
        expect(count).toEqual(2);

        count = t1.add(DatetimeInterval(Days(0), Hours(25))); // 1 day, 1 hour

        expect(verify(t1, 3, 34, 0, 0)).toBeTrue();
        expect(count).toEqual(1);
    });

    it("Subtraction", [&]
    {
        Time t1(1, 23, 0 ,0);

        expect(verify(t1, 1, 23, 0, 0)).toBeTrue();
        
        Days count = t1.subtract(DatetimeInterval(Days(0), Hours(0), Minutes(1)));

        expect(verify(t1, 1, 22, 0, 0)).toBeTrue();
        expect(count).toEqual(0);
        
        count = t1.subtract(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1 hour, 10 minutes

        expect(verify(t1, 0, 12, 0, 0)).toBeTrue();
        expect(count).toEqual(2);
        
        count = t1.subtract(DatetimeInterval(Days(2), Hours(1))); // 2 days, 1 hour

        expect(verify(t1, 23, 12, 0, 0)).toBeTrue();
        expect(count).toEqual(3);
    });
});

} // namespace
