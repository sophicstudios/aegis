#include <aftt_time.h>
#include <aftt_datetimeinterval.h>
#include <aunit.h>
#include <iostream>

namespace aegis {
namespace aftt {

class TestTime : public aunit::TestFixture
{
public:
    TestTime() {}
    virtual ~TestTime() {}
    
protected:
    virtual void runTest();

private:
    void testConstruction();
    void testAssignment();
    void testAddition();
    void testSubtraction();
};

AUNIT_REGISTERTEST(TestTime);

namespace {

bool verify(Time const& t, unsigned int hour, unsigned int minute, unsigned int second, unsigned int millisecond)
{
    return t.hour() == hour
        && t.minute() == minute
        && t.second() == second
        && t.millisecond() == millisecond;
}

} // namespace

void TestTime::runTest()
{
    testConstruction();
    testAssignment();
    testAddition();
    testSubtraction();
}

void TestTime::testConstruction()
{
    Time t1;
    AUNIT_ASSERT(verify(t1, 24, 0, 0, 0));

    Time t2(1, 23);
    AUNIT_ASSERT(verify(t2, 1, 23, 0, 0));

    Time t3(1, 23, 0, 0);
    AUNIT_ASSERT(verify(t3, 1, 23, 0, 0));

    Days count = t3.add(DatetimeInterval(Seconds(60), Nanoseconds(0))); // 60 seconds
    AUNIT_ASSERT(verify(t3, 1, 24, 0, 0));
    AUNIT_ASSERT(count == 0);

    count = t3.add(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1 hour, 10 minutes
    AUNIT_ASSERT(verify(t3, 2, 34, 0, 0));
    AUNIT_ASSERT(count == 2);

    count = t3.add(DatetimeInterval(Days(1), Hours(1))); // 1 day, 1 hour
    AUNIT_ASSERT(verify(t3, 3, 34, 0, 0));
    AUNIT_ASSERT(count == 1);
}

void TestTime::testAssignment()
{
    Time t1;
    AUNIT_ASSERT(verify(t1, 24, 0, 0, 0));

    t1.setHour(6);
    AUNIT_ASSERT(verify(t1, 6, 0, 0, 0));

    t1.setMinute(23);
    AUNIT_ASSERT(verify(t1, 6, 23, 0, 0));
    
    t1.setSecond(59);
    AUNIT_ASSERT(verify(t1, 6, 23, 59, 0));

    t1.setNanosecond(981000000);
    AUNIT_ASSERT(verify(t1, 6, 23, 59, 981));
}

void TestTime::testAddition()
{
    Time t1(1, 23, 0, 0);
    AUNIT_ASSERT(verify(t1, 1, 23, 0, 0));

    Days count = t1.add(DatetimeInterval(Days(0), Hours(0), Minutes(1)));
    AUNIT_ASSERT(verify(t1, 1, 24, 0, 0));
    AUNIT_ASSERT(count == 0);

    count = t1.add(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1, hour, 10 minutes
    AUNIT_ASSERT(verify(t1, 2, 34, 0, 0));
    AUNIT_ASSERT(count == 2);

    count = t1.add(DatetimeInterval(Days(0), Hours(25))); // 1 day, 1 hour
    AUNIT_ASSERT(verify(t1, 3, 34, 0, 0));
    AUNIT_ASSERT(count == 1);
}

void TestTime::testSubtraction()
{
    Time t1(1, 23, 0 ,0);
    AUNIT_ASSERT(verify(t1, 1, 23, 0, 0));
    
    Days count = t1.subtract(DatetimeInterval(Days(0), Hours(0), Minutes(1)));
    AUNIT_ASSERT(verify(t1, 1, 22, 0, 0));
    AUNIT_ASSERT(count == 0);
    
    count = t1.subtract(DatetimeInterval(Days(2), Hours(1), Minutes(10))); // 2 days, 1 hour, 10 minutes
    AUNIT_ASSERT(verify(t1, 0, 12, 0, 0));
    AUNIT_ASSERT(count == 2);
    
    count = t1.subtract(DatetimeInterval(Days(2), Hours(1))); // 2 days, 1 hour
    AUNIT_ASSERT(verify(t1, 23, 12, 0, 0));
    AUNIT_ASSERT(count == 3);
}

} // namespace
} // namespace
