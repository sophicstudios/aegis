#include <aftt_datetime.h>
#include <aunit.h>

namespace aegis {
namespace aftt {

class TestDatetime : public aunit::TestFixture
{
public:
    TestDatetime() {}
    
    virtual ~TestDatetime() {}
    
protected:
    virtual void runTest();
    
private:
    void testConstruction();
    void testAssignment();
    void testAddition();
    void testSubtraction();
};

AUNIT_REGISTERTEST(TestDatetime);

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

void TestDatetime::runTest()
{
    testConstruction();
    testAssignment();
    testAddition();
    testSubtraction();
}

void TestDatetime::testConstruction()
{
    Datetime dt1(2010, 10, 31);
    AUNIT_ASSERT(verify(dt1, 2010, 10, 31, 0, 0, 0, 0));
    
    Datetime dt2(2010, 10, 31, 5);
    
    Datetime dt3(2010, 10, 31, 5, 31);
    
    Datetime dt4(2010, 10, 31, 5, 31, 55);
    
    Datetime dt5(2010, 10, 31, 5, 31, 55, 999);
}

void TestDatetime::testAssignment()
{
}

void TestDatetime::testAddition()
{
}

void TestDatetime::testSubtraction()
{
}

} // namespace
} // namespace


