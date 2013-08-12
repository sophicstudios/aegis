#ifndef INCLUDED_AEGIS_AFTT_TIME_H
#define INCLUDED_AEGIS_AFTT_TIME_H

#include <aftt_days.h>
#include <afts_stdint.h>
#include <iosfwd>

// @Description This component represents a point in time, with the individual components
// of that time, including hour, minute, second and millisecond, available as
// properties of the object.
//
// @Author Lyell Haynes

namespace aftt {

class DatetimeInterval;

// Represents an hour of the day, in the range [0,23]
class Hour
{
public:
    enum Split {
        Split_AM,
        Split_PM
    };
    
    // specify the hour using a 24 hour clock, in the range [0,23]. If value
    // is not within the expected range, an exeption is thrown.
    Hour(unsigned int value);
    
    // specify the hour using a 12 hour clock, in the range [1,12] [AM/PM],
    // where 12 AM == 0 in the 24-hour clock and 12 PM == 12 in the 24-hour
    // clock. For example, a time value of 12:43:56 AM == 00:43:56 and a time of
    // 12:43:56 PM == 12:43:56
    Hour(unsigned int value, Split split);
    
    ~Hour();

    // returns an integer representing the hour in a 24-hour clock.
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Hour const& lhs, Hour const& rhs);
bool operator!=(Hour const& lhs, Hour const& rhs);
bool operator<(Hour const& lhs, Hour const& rhs);
bool operator<=(Hour const& lhs, Hour const& rhs);
bool operator>(Hour const& lhs, Hour const& rhs);
bool operator>=(Hour const& lhs, Hour const& rhs);
std::ostream& operator<<(std::ostream& os, Hour const& hour);

class Minute
{
public:
    Minute(unsigned int value);
    
    ~Minute();
    
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Minute const& lhs, Minute const& rhs);
bool operator!=(Minute const& lhs, Minute const& rhs);
bool operator<(Minute const& lhs, Minute const& rhs);
bool operator<=(Minute const& lhs, Minute const& rhs);
bool operator>(Minute const& lhs, Minute const& rhs);
bool operator>=(Minute const& lhs, Minute const& rhs);
std::ostream& operator<<(std::ostream& os, Minute const& minute);

class Second
{
public:
    Second(unsigned int second);
    
    ~Second();
    
    unsigned int value() const;

private:
    unsigned int m_value;
};

bool operator==(Second const& lhs, Second const& rhs);
bool operator!=(Second const& lhs, Second const& rhs);
bool operator<(Second const& lhs, Second const& rhs);
bool operator<=(Second const& lhs, Second const& rhs);
bool operator>(Second const& lhs, Second const& rhs);
bool operator>=(Second const& lhs, Second const& rhs);
std::ostream& operator<<(std::ostream& os, Second const& second);

class Millisecond
{
public:
    Millisecond(unsigned int millisecond);
    
    ~Millisecond();
    
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Millisecond const& lhs, Millisecond const& rhs);
bool operator!=(Millisecond const& lhs, Millisecond const& rhs);
bool operator<(Millisecond const& lhs, Millisecond const& rhs);
bool operator<=(Millisecond const& lhs, Millisecond const& rhs);
bool operator>(Millisecond const& lhs, Millisecond const& rhs);
bool operator>=(Millisecond const& lhs, Millisecond const& rhs);
std::ostream& operator<<(std::ostream& os, Millisecond const& millisecond);

class Microsecond
{
public:
    Microsecond(unsigned int microsecond);
    
    Microsecond(Millisecond const& millisecond);
    
    ~Microsecond();
    
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Microsecond const& lhs, Microsecond const& rhs);
bool operator!=(Microsecond const& lhs, Microsecond const& rhs);
bool operator<(Microsecond const& lhs, Microsecond const& rhs);
bool operator<=(Microsecond const& lhs, Microsecond const& rhs);
bool operator>(Microsecond const& lhs, Microsecond const& rhs);
bool operator>=(Microsecond const& lhs, Microsecond const& rhs);
std::ostream& operator<<(std::ostream& os, Microsecond const& microsecond);

class Nanosecond
{
public:
    Nanosecond(unsigned int nanosecond);

    Nanosecond(Millisecond const& millisecond);
    
    Nanosecond(Microsecond const& microsecond);
    
    ~Nanosecond();
    
    unsigned int value() const;
    
private:
    unsigned int m_value;
};

bool operator==(Nanosecond const& lhs, Nanosecond const& rhs);
bool operator!=(Nanosecond const& lhs, Nanosecond const& rhs);
bool operator<(Nanosecond const& lhs, Nanosecond const& rhs);
bool operator<=(Nanosecond const& lhs, Nanosecond const& rhs);
bool operator>(Nanosecond const& lhs, Nanosecond const& rhs);
bool operator>=(Nanosecond const& lhs, Nanosecond const& rhs);
std::ostream& operator<<(std::ostream& os, Nanosecond const& nanosecond);

class Time
{
public:
    // Constructs a Time object with the initial value of 24:00:00.000. This is a special
    // value that only makes sense in this case. It cannot be created from any other
    // operation on the Time object. In a logical sense, it is equivalent to the
    // time of 00:00:00.000 and any operations done on this default constructed
    // Time object will be the same as if done on an object with the time
    // of 00:00:00.000.
    Time();

    Time(Time const& time);
    
    // Constructs a Time object with the given hour, minute, second and nanosecond.
    Time(
        Hour const& hour,
        Minute const& minute = Minute(0),
        Second const& second = Second(0),
        Nanosecond const& nanosecond = Nanosecond(0));

    // Destructor
    ~Time();

    Time& operator=(Time const& time);
    
    // Sets the hour component.
    void setHour(Hour const& hour);

    // Sets the minute value of the time.
    void setMinute(Minute const& minute);

    // Sets the second value of the time.
    void setSecond(Second const& second);

    // Sets the nanosecond value of the time.
    void setNanosecond(Nanosecond const& nanosecond);

    Time& operator+=(DatetimeInterval const& interval);
    
    Time& operator-=(DatetimeInterval const& interval);

    // Adds the specified interval to the time, returning the number of times
    // the value 00:00:00.000 was crossed, i.e. the day changed.
    Days add(DatetimeInterval const& interval);
    
    Days subtract(DatetimeInterval const& interval);
    
    // Retrieves the hour component of the time.
    Hour hour() const;

    // Retrieves the minute component of the time.
    Minute minute() const;

    // Retrieves the second component of the time.
    Second second() const;

    // Retrieves the millisecond component of the time.
    Millisecond millisecond() const;
    
    // Retrieves the microsecond component of the time.
    Microsecond microsecond() const;
    
    // Retrieves the nanosecond component of the time.
    Nanosecond nanosecond() const;
    
    // Prints the time value to the supplied stream, using the
    // ISO 8601 extended format HH:MM:SS.mmm
    std::ostream& print(std::ostream& os) const;

private:
    friend DatetimeInterval operator-(Time const& lhs, Time const& rhs);
    friend bool operator==(Time const& lhs, Time const& rhs);
    friend bool operator!=(Time const& lhs, Time const& rhs);
    friend bool operator<(Time const& lhs, Time const& rhs);
    friend bool operator<=(Time const& lhs, Time const& rhs);
    friend bool operator>(Time const& lhs, Time const& rhs);
    friend bool operator>=(Time const& lhs, Time const& rhs);

    uint64_t m_nanoseconds;
};

Time operator+(Time const& lhs, DatetimeInterval const& rhs);

Time operator-(Time const& lhs, DatetimeInterval const& rhs);

DatetimeInterval operator-(Time const& lhs, Time const& rhs);

bool operator==(Time const& lhs, Time const& rhs);

bool operator!=(Time const& lhs, Time const& rhs);

bool operator<(Time const& lhs, Time const& rhs);

bool operator<=(Time const& lhs, Time const& rhs);

bool operator>(Time const& lhs, Time const& rhs);

bool operator>=(Time const& lhs, Time const& rhs);

std::ostream& operator<<(std::ostream& os, Time const& time);

} // namespace

#endif // INCLUDED
