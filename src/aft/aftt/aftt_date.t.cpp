#include <aftt_date.h>
#include <aunit.h>

namespace {

using namespace aunit;
using namespace aftt;

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
    return date.year() == Year(year)
        && date.month() == Month(month)
        && date.day() == Day(day);
}

} // namespace

Describe d("aftt_date", []
{
    it("Construction", [&]
    {
        bool allConstructionSucceeded = true;
        for (int y = START_YEAR; y < END_YEAR; ++y) {
            for (int m = 1; m <= 12; ++m) {
                for (int d = 1; d < MONTH_INFO[m-1].days + 1; ++d) {
                    if (y == 1752 && m == 9 && d > 2 && d < 14) {
                        continue;
                    }

                    Date date((Year(y)), Month(m), Day(d));
                    allConstructionSucceeded &= equalDates(date, y, m, d);
                }
            }
        }

        expect(allConstructionSucceeded).toBeTrue();
    });

    it("Assignment", [&]
    {
        const int year = 1975;
        const int month = 2;
        const int day = 16;
        
        Date d1((Year(year)), Month(month), Day(day));
        expect(equalDates(d1, year, month, day)).toBeTrue();
        
        Date d2;
        expect(equalDates(d2, 1, 1, 1)).toBeTrue();
        
        d2 = d1;
        expect(equalDates(d2, year, month, day)).toBeTrue();
    });

    it("Addition", [&]
    {
        Date d1(Year(1975), Month(2), Day(16));
        expect(equalDates(d1, 1975, 2, 16)).toBeTrue();
        
        d1 += Days(1);
        expect(equalDates(d1, 1975, 2, 17)).toBeTrue();
        
        d1++;
        expect(equalDates(d1, 1975, 2, 18)).toBeTrue();
        
        ++d1;
        expect(equalDates(d1, 1975, 2, 19)).toBeTrue();
        
        d1 += Days(2);
        expect(equalDates(d1, 1975, 2, 21)).toBeTrue();
        
        Date d2(Year(1752), Month(9), Day(2));

        ++d2;
        expect(equalDates(d2, 1752, 9, 14)).toBeTrue();
    });

    it("Subtraction", [&]
    {
        Date d1(Year(1975), Month(2), Day(16));
        
        d1 -= Days(1);
        expect(equalDates(d1, 1975, 2, 15)).toBeTrue();
        
        d1--;
        expect(equalDates(d1, 1975, 2, 14)).toBeTrue();
        
        --d1;
        expect(equalDates(d1, 1975, 2, 13)).toBeTrue();
        
        d1 -= Days(2);
        expect(equalDates(d1, 1975, 2, 11)).toBeTrue();
        
        Date d2(Year(1752), Month(9), Day(14));
        
        --d2;
        expect(equalDates(d2, 1752, 9, 2)).toBeTrue();
    });
});

} // namespace
