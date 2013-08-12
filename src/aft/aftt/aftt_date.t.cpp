#include <aftt_date.h>
#include <aunit.h>

namespace aftt {

class TestDate : public aunit::TestFixture
{
public:
    TestDate() {}
    virtual ~TestDate() {}

protected:
    virtual void runTest();

private:
    void testConstruction();
    void testAssignment();
    void testAddition();
    void testSubtraction();
};

AUNIT_REGISTERTEST(TestDate);

namespace {

int START_YEAR = 1;
int END_YEAR = 2100;

struct MonthInfo
{
    int days;
    int leapDays;
};

const MonthInfo MONTH_INFO[] = {
    {31, 31}, // Jan
    {28, 29}, // Feb
    {31, 31}, // Mar
    {30, 30}, // Apr
    {31, 31}, // May
    {30, 30}, // Jun
    {31, 31}, // Jul
    {31, 31}, // Aug
    {30, 30}, // Sep
    {31, 31}, // Oct
    {30, 30}, // Nov
    {31, 31}  // Dec
};

bool equalDates(Date const& date, int year, int month, int day)
{
    return date.year() == year
        && date.month() == month
        && date.day() == day;
}

} // namespace

void TestDate::runTest()
{
    testConstruction();
    testAssignment();
    testAddition();
    testSubtraction();
}

void TestDate::testConstruction()
{
    bool allConstructionSucceeded = true;
    for (int y = START_YEAR; y < END_YEAR; ++y) {
        for (int m = 1; m <= 12; ++m) {
            for (int d = 1; d < MONTH_INFO[m-1].days + 1; ++d) {
                if (y == 1752 && m == 9 && d > 2 && d < 14) {
                    continue;
                }

                Date date(y, m, d);
                allConstructionSucceeded &= equalDates(date, y, m, d);
            }
        }
    }

    AUNIT_ASSERT(allConstructionSucceeded);
}

void TestDate::testAssignment()
{
    const int year = 1975;
    const int month = 2;
    const int day = 16;
    
    Date d1(year, month, day);
    AUNIT_ASSERT(equalDates(d1, year, month, day));
    
    Date d2;
    AUNIT_ASSERT(equalDates(d2, 1, 1, 1));
    
    d2 = d1;
    AUNIT_ASSERT(equalDates(d2, year, month, day));
}

void TestDate::testAddition()
{
    Date d1(1975, 2, 16);
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 16));
    
    d1 += Days(1);
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 17));
    
    d1++;
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 18));
    
    ++d1;
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 19));
    
    d1 += Days(2);
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 21));
    
    Date d2(1752, 9, 2);

    ++d2;
    AUNIT_ASSERT(equalDates(d2, 1752, 9, 14));
}

void TestDate::testSubtraction()
{
    Date d1(1975, 2, 16);
    
    d1 -= Days(1);
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 15));
    
    d1--;
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 14));
    
    --d1;
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 13));
    
    d1 -= Days(2);
    AUNIT_ASSERT(equalDates(d1, 1975, 2, 11));
    
    Date d2(1752, 9, 14);
    
    --d2;
    AUNIT_ASSERT(equalDates(d2, 1752, 9, 2));
}

} // namespace
