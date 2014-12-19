#include <aftt_date.h>
#include <afts_assert.h>
#include <ostream>
#include <iomanip>

namespace aftt {

namespace {

/**
 * Contains information about each month.
 * longName: the english long name for the month.
 * shortName: the english short name for the month.
 * days: number of day in the month in a non-leap year.
 * leapDays: number of days in the month in a leap year.
 * start: day of week the month would start on (non-leap year)
 * if March started on a Wednesday.
 * leapStart: day of week the month would start on (leap year)
 * if March started on a Wednesday.
 */
struct MonthData
{
    char const* const longName;
    char const* const shortName;
    uint32_t days;
    uint32_t daysBeforeMonth;
    uint32_t daysThroughMonth;
    uint32_t leapDays;
    uint32_t leapDaysBeforeMonth;
    uint32_t leapDaysThroughMonth;
    uint32_t start;
    uint32_t leapStart;
};

const MonthData MONTH_DATA_LIST[] = {
    {NULL,        NULL,   0,   0,   0,  0,   0,   0, 0, 0}, // blank month
    {"January",   "Jan", 31,   0,  31, 31,   0,  31, 0, 6},
    {"February",  "Feb", 28,  31,  59, 29,  31,  60, 3, 2},
    {"March",     "Mar", 31,  59,  90, 31,  60,  91, 3, 3},
    {"April",     "Apr", 30,  90, 120, 30,  91, 121, 6, 6},
    {"May",       "May", 31, 120, 151, 31, 121, 152, 1, 1},
    {"June",      "Jun", 30, 151, 181, 30, 152, 182, 4, 4},
    {"July",      "Jul", 31, 181, 212, 31, 182, 213, 6, 6},
    {"August",    "Aug", 31, 212, 243, 31, 213, 244, 2, 2},
    {"September", "Sep", 30, 243, 273, 30, 244, 274, 5, 5},
    {"October",   "Oct", 31, 273, 304, 31, 274, 305, 0, 0},
    {"November",  "Nov", 30, 304, 334, 30, 305, 335, 3, 3},
    {"December",  "Dec", 31, 334, 365, 31, 335, 366, 5, 5}
};

const uint32_t DAYS_PER_YEAR = 365;
const uint32_t DAYS_PER_4_YEARS = (DAYS_PER_YEAR * 4 )+ 1;
const uint32_t DAYS_PER_CENTURY = (DAYS_PER_YEAR * 100) + 24;
const uint32_t DAYS_PER_4_CENTURY = (DAYS_PER_CENTURY * 4) + 1;

const uint32_t GREGORIAN_START_YEAR = 1752;
const uint32_t GREGORIAN_START_MONTH = 9;
const uint32_t JULIAN_END_DAY = 2;
const uint32_t GREGORIAN_START_DAY = 14;
const uint32_t GREGORIAN_ADJUST = GREGORIAN_START_DAY - JULIAN_END_DAY - 1;

const uint64_t JAN_01_1601 = 584401;
const uint64_t SEP_02_1752 = 639798;
const uint64_t SEP_14_1752 = 639799;
//const uint64_t JAN_01_1753 = 639908;

inline bool isLeapYear(uint32_t year)
{
    // http://en.wikipedia.org/wiki/Leap_year
    // if $year mod 400 is 0 then leap
    // else if $year mod 100 is 0 then no leap
    // else if $year mod 4 is 0 then leap
    // else no leap

    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0) || (year <= 1752));
}

uint64_t yearMonthDayToSerial(uint32_t year, uint32_t month, uint32_t day)
{
    uint64_t serial = 0;
    
    // 1752 is a strange year, in which 11 days are removed, so we have
    // special logic to handle this.
    if (year > GREGORIAN_START_YEAR) {
        // Actual calculation for number of days up to the specified year:
        // 365*(Y-1) + ((Y-1)-1600)/4 - ((Y-1)-1600)/100 + ((Y-1)-1600)/400 + a1 - a2 + a3

        // where 
        // a1 = 400 (number of leap days through year 1600)
        // a2 =  11 (number of days removed from 1752)
        // a3 =   1 (1700 is a pre-adjustment leap year)
        
        // This can be adjusted to:
        // 365*(Y) + (Y-1601)/4 - (Y-1601)/100 + (Y-1601)/400 + 25;
        static const uint32_t LEAP_DAYS = 25;
        
        uint32_t x = year - 1601;
        serial = (DAYS_PER_YEAR * year) + (x/4) - (x/100) + (x/400) + LEAP_DAYS + MONTH_DATA_LIST[month].daysBeforeMonth + day;
        if (month > 2 && (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
            ++serial;
        }
    }
    else {
        uint32_t prevYear = year - 1;
        serial = (DAYS_PER_YEAR * prevYear) + (prevYear/4) + MONTH_DATA_LIST[month].daysBeforeMonth + day;

        if (month > 2 && year % 4 == 0) {
            ++serial;
        }
        
        if (serial > SEP_02_1752) {
            serial -= GREGORIAN_ADJUST;
        }
    }
    
    return serial;
}

void serialToYearMonthDay(uint32_t* year, uint32_t* month, uint32_t* day, uint64_t serial)
{
    if (serial >= SEP_14_1752) {
        serial = serial - JAN_01_1601 + GREGORIAN_ADJUST;

        // Adjust for 400 year rule in leap year computation.
        uint64_t s2 = serial - (serial + 1) / DAYS_PER_4_CENTURY;

        // Adjust for 100 year rule in leap year computation.
        uint64_t s3 = s2 + (s2 + 1) / DAYS_PER_CENTURY - 1;  // 1700 has a leap day

        // Compute year.
        uint32_t y = static_cast<uint32_t>((s3 - ((s3 + 1) / DAYS_PER_4_YEARS)) / DAYS_PER_YEAR);
        *year = y + 1601;

        // Compute julian day.
        uint64_t julianDay = serial -
             ((y * DAYS_PER_YEAR) + (y / 4) - (y / 100) + (y / 400) + 1);  // 1700 has a leap day

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4 && (99 != y % 100 || 399 == y % 400));

        // Compute month.
        uint32_t m = static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057);
        *month = m + 1;

        // Compute day of month.
        *day = static_cast<uint32_t>(julianDay - ((m * 3057 + 50) / 100 - a*(m >= 2)) + 1);
    }
    else {
        // Convert to days since JAN_01_0001.
        serial -= 1;

        // Compute year.
        uint32_t y = static_cast<uint32_t>((serial - (serial+1) / 1461) / 365);
        *year = y + 1;

        // Compute julian day.
        uint64_t julianDay = serial - (y * 365 + y / 4);

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4);

        // Compute month.
        uint32_t m = static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057);
        *month = m + 1;

        // Compute day of month.
        *day = static_cast<uint32_t>(julianDay - ((m * 3057 + 50) / 100 - a*(m >= 2)) + 1);
    }
}

uint32_t serialToYear(uint64_t serial)
{
    if (serial >= SEP_14_1752) {
        serial = serial - JAN_01_1601 + GREGORIAN_ADJUST;

        // Adjust for 400 year rule in leap year computation.
        uint64_t s2 = serial - (serial+1) / DAYS_PER_4_CENTURY;

        // Adjust for 100 year rule in leap year computation.
        uint64_t s3 = s2 + (s2+1) / DAYS_PER_CENTURY - 1;  // 1700 has a leap day

        // Compute year.
        return static_cast<uint32_t>((s3 - (s3+1) / DAYS_PER_4_YEARS) / DAYS_PER_YEAR + 1601);
    }
    else {
        // Convert to days since JAN_01_0001.
        serial -= 1;

        // Compute year.
        return static_cast<uint32_t>((serial - (serial+1) / 1461) / 365 + 1);
    }
}

uint32_t serialToMonth(uint64_t serial)
{
    if (serial >= SEP_14_1752) {
        serial = serial - JAN_01_1601 + GREGORIAN_ADJUST;

        // Adjust for 400 year rule in leap year computation.
        uint64_t s2 = serial - (serial+1) / DAYS_PER_4_CENTURY;

        // Adjust for 100 year rule in leap year computation.
        uint64_t s3 = s2 + (s2+1) / DAYS_PER_CENTURY - 1;  // 1700 has a leap day

        // Compute year.
        uint32_t y = static_cast<uint32_t>((s3 - (s3+1) / DAYS_PER_4_YEARS) / DAYS_PER_YEAR);

        // Compute julian day.
        uint64_t julianDay = serial -
             (y * DAYS_PER_YEAR + y / 4 - y / 100 + y / 400 + 1);  // 1700 has a leap day

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4 && (99 != y % 100 || 399 == y % 400));

        // Compute month.
        return static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057 + 1);
    }
    else {
        // Convert to days since JAN_01_0001.
        serial -= 1;

        // Compute year.
        uint32_t y = static_cast<uint32_t>((serial - (serial+1) / 1461) / 365);

        // Compute julian day.
        uint64_t julianDay = serial - (y * 365 + y / 4);

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4);

        // Compute month.
        return static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057 + 1);
    }
}

uint32_t serialToDay(uint64_t serial)
{
    if (serial >= SEP_14_1752) {
        serial = serial - JAN_01_1601 + GREGORIAN_ADJUST;

        // Adjust for 400 year rule in leap year computation.
        uint64_t s2 = serial - (serial+1) / DAYS_PER_4_CENTURY;

        // Adjust for 100 year rule in leap year computation.
        uint64_t s3 = s2 + (s2+1) / DAYS_PER_CENTURY - 1;  // 1700 has a leap day

        // Compute year.
        uint32_t y = static_cast<uint32_t>((s3 - (s3+1) / DAYS_PER_4_YEARS) / DAYS_PER_YEAR);

        // Compute julian day.
        uint64_t julianDay = serial -
             (y * DAYS_PER_YEAR + y / 4 - y / 100 + y / 400 + 1);  // 1700 has a leap day

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4 && (99 != y % 100 || 399 == y % 400));

        // Compute month.
        uint32_t m = static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057);

        // Compute day of month.
        return static_cast<uint32_t>(julianDay - ((m * 3057 + 50) / 100 - a*(m >= 2)) + 1);
    }
    else {
        // Convert to days since JAN_01_0001.
        serial -= 1;

        // Compute year.
        uint32_t y = static_cast<uint32_t>((serial - (serial+1) / 1461) / 365);

        // Compute julian day.
        uint64_t julianDay = serial - (y * 365 + y / 4);

        // Compute adjustment for February, with and without a leap day.
        uint32_t a = 2 - (3 == y % 4);

        // Compute month.
        uint32_t m = static_cast<uint32_t>(((julianDay + a * (julianDay >= 59)) * 100 + 50) / 3057);

        // Compute day of month.
        return static_cast<uint32_t>(julianDay - ((m * 3057 + 50) / 100 - a*(m >= 2)) + 1);
    }
}

} // namespace

bool Date::isValid(Year const& year, Month const& month, Day const& day)
{
    uint32_t yearValue = year.value();
    uint32_t monthValue = month.value();
    uint32_t dayValue = day.value();

    if (yearValue < 1 || yearValue > 9999 || monthValue < 1 || monthValue > 12) {
        return false;
    }

    bool isLeap = isLeapYear(yearValue);
    
    if (isLeap && yearValue == GREGORIAN_START_YEAR
            && monthValue == GREGORIAN_START_MONTH
            && dayValue > JULIAN_END_DAY
            && dayValue < GREGORIAN_START_DAY)
    {
        return false;
    }

    if (dayValue < 1 || dayValue > (isLeap ? MONTH_DATA_LIST[monthValue].leapDays : MONTH_DATA_LIST[monthValue].days)) {
        return false;
    }

    return true;
}

// Initialize to 0001-01-01
Date::Date()
: m_serial(1)
{}

Date::Date(Year const& year, Month const& month, Day const& day)
: m_serial(yearMonthDayToSerial(year.value(), month.value(), day.value()))
{
    AFTS_ASSERT_DEBUG(isValid(year, month, day));
}

Date::~Date()
{}

Date& Date::operator+=(Days const& days)
{
    m_serial += days.value();
    return *this;
}

Date& Date::operator-=(Days const& days)
{
    m_serial -= days.value();
    return *this;
}

Date& Date::operator++()
{
    ++m_serial;
    return *this;
}

Date Date::operator++(int)
{
    Date temp(*this);
    ++m_serial;
    return temp;
}

Date& Date::operator--()
{
    --m_serial;
    return *this;
}

Date Date::operator--(int)
{
    Date temp(*this);
    --m_serial;
    return temp;
}

bool Date::validateAndSetDate(Year const& year, Month const& month, Day const& day)
{
    if (!isValid(year, month, day))
    {
        return false;
    }

    m_serial = yearMonthDayToSerial(year.value(), month.value(), day.value());

    return true;
}

bool Date::setDate(Year const& year, Month const& month, Day const& day)
{
    m_serial = yearMonthDayToSerial(year.value(), month.value(), day.value());

    return true;
}

void Date::getYearMonthDay(Year& year, Month& month, Day& day) const
{
    uint32_t yearValue = 0;
    uint32_t monthValue = 0;
    uint32_t dayValue = 0;
    
    serialToYearMonthDay(&yearValue, &monthValue, &dayValue, m_serial);
    
    year = Year(yearValue);
    month = Month(monthValue);
    day = Day(dayValue);
}

Year Date::year() const
{
    return Year(serialToYear(m_serial));
}

Month Date::month() const
{
    return Month(serialToMonth(m_serial));
}

Day Date::day() const
{
    return Day(serialToDay(m_serial));
}

std::ostream& Date::print(std::ostream& os) const
{
    uint32_t year, month, day;
    serialToYearMonthDay(&year, &month, &day, m_serial);
    
    os << std::setw(4) << std::setfill('0') << year
        << "-" << std::setw(2) << std::setfill('0') << MONTH_DATA_LIST[month].shortName
        << "-" << std::setw(2) << std::setfill('0') << day;

    return os;
}

Date operator+(Date const& date, Days const& days)
{
    Date result(date);
    result += days;
    return result;
}

Date operator-(Date const& date, Days const& days)
{
    Date result(date);
    result -= days;
    return result;
}

Days operator-(Date const& lhs, Date const& rhs)
{
    return Days(static_cast<int64_t>(lhs.m_serial - rhs.m_serial));
}

bool operator==(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial == rhs.m_serial;
}

bool operator!=(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial != rhs.m_serial;
}

bool operator<(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial < rhs.m_serial;
}

bool operator<=(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial <= rhs.m_serial;
}

bool operator>(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial > rhs.m_serial;
}

bool operator>=(Date const& lhs, Date const& rhs)
{
    return lhs.m_serial >= rhs.m_serial;
}

std::ostream& operator<<(std::ostream& os, Date const& date)
{
    return date.print(os);
}

} // namespace
