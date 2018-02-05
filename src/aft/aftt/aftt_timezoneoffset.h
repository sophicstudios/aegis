#ifndef INCLUDED_AEGIS_AFTT_TIMEZONEOFFSET_H
#define INCLUDED_AEGIS_AFTT_TIMEZONEOFFSET_H

namespace aftt {

class TimezoneOffset
{
public:
    TimezoneOffset();

    explicit TimezoneOffset(short value);

    ~TimezoneOffset();

    short value() const;

private:
    short m_value;
};

} // namespace

#endif // INCLUDED
