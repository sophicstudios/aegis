#ifndef INCLUDED_AUNIT_EXPECT_H
#define INCLUDED_AUNIT_EXPECT_H

#include <iostream>

namespace aunit {

template<typename T>
class Expect
{
public:
    Expect(T const& value);

    ~Expect();

    Expect& non();

    void toEqual(T const& value);

    void toBeNull();

    void toBeTrue();

private:
    T const& m_value;
    bool m_negate;
};

template<typename T>
Expect<T> expect(T const& value)
{
    return Expect<T>(value);
}

template<typename T>
Expect<T>::Expect(T const& value)
: m_value(value),
  m_negate(false)
{
}

template<typename T>
Expect<T>::~Expect()
{}

template<typename T>
Expect<T>& Expect<T>::non()
{
    m_negate = !m_negate;

    return *this;
}

template<typename T>
void Expect<T>::toEqual(T const& value)
{
    bool result;

    if (m_negate)
    {
        result = m_value != value;
    }
    else
    {
        result = m_value == value;
    }

    if (!result)
    {
        throw std::exception();
    }
}

template<typename T>
void Expect<T>::toBeNull()
{
    if (!std::is_pointer<T>())
    {
        throw std::exception();
    }

    if ((m_negate && m_value == nullptr) || (!m_negate && m_value != nullptr))
    {
        throw std::exception();
    }
}

template<typename T>
void Expect<T>::toBeTrue()
{
    if(!std::is_fundamental<T>())
    {
        throw std::exception();
    }

    if ((m_negate && m_value == true) || (!m_negate && m_value != true))
    {
        throw std::exception();
    }
}

} // namespace

#endif // INCLUDED
