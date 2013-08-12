#ifndef INCLUDED_AEGIS_AGTM_VECTOR2_H
#define INCLUDED_AEGIS_AGTM_VECTOR2_H

#include <afts_comparisonutil.h>
#include <algorithm>
#include <cmath>
#include <ostream>

namespace agtm {

template<typename T>
class Vector2
{
public:
    /// Constructs a Vector with magnitude and direction (0, 0).
    Vector2();
    
    /// Constructs a position Vector2 with magnitude and direction (x, y).
    /// @param x The x component of the Vector2
    /// @param y The y component of the Vector2
    Vector2(T const& x, T const& y);

    /// Constructs a Vector2 with magnitude and direction (arr[0], arr[1]).
    /// If the length of arr is != 2, the results are undefined
    /// @param arr Array of length 2
    /// @param length Length of the input array
    Vector2(T const* const arr, size_t length);

    /// Copy constructor.
    Vector2(Vector2<T> const& v);

    /// Destructor
    ~Vector2();
    
    Vector2<T>& operator=(Vector2<T> const& rhs);

    void assign(T const& x, T const& y);
    
    void assign(T const* const arr, size_t length);

    Vector2<T>& operator+=(Vector2<T> const& rhs);
    
    Vector2<T>& operator+=(T scalar);
    
    Vector2<T>& operator-=(Vector2<T> const& rhs);
    
    Vector2<T>& operator-=(T scalar);
    
    Vector2<T>& operator*=(Vector2<T> const& rhs);
    
    Vector2<T>& operator*=(T scalar);
    
    Vector2<T>& operator/=(Vector2<T> const& rhs);
    
    Vector2<T>& operator/=(T scalar);
    
    T const& x() const;
    
    T const& y() const;

    T const* const arr() const;

    T length() const;
    
    T lengthSquared() const;
    
    void normalize();
        
private:
    union {
        T m_arr[2];
        struct {
            T m_x;
            T m_y;
        };
    };
};

template<typename T>
bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T>
bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T>
Vector2<T> operator-(Vector2<T> const& v);

template<typename T>
Vector2<T> operator+(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T, typename U>
Vector2<T> operator+(Vector2<T> const& lhs, U const& rhs);

template<typename T>
Vector2<T> operator-(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T, typename U>
Vector2<T> operator-(Vector2<T>const& lhs, U const& rhs);

template<typename T>
Vector2<T> operator*(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T, typename U>
Vector2<T> operator*(Vector2<T> const& lhs, U const& rhs);

template<typename T>
Vector2<T> operator/(Vector2<T> const& lhs, Vector2<T> const& rhs);

template<typename T, typename U>
Vector2<T> operator/(Vector2<T> const& lhs, U const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& v);

template<typename T>
inline Vector2<T>::Vector2()
: m_x(T()),
  m_y(T())
{}

template<typename T>
inline Vector2<T>::Vector2(T const& x, T const& y)
: m_x(x),
  m_y(y)
{}

template<typename T>
inline Vector2<T>::Vector2(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(2), length), m_arr);
};

template<typename T>
inline Vector2<T>::Vector2(Vector2<T> const& v)
: m_x(v.m_x),
  m_y(v.m_y)
{}

template<typename T>
Vector2<T>::~Vector2()
{}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(Vector2<T> const& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    
    return *this;
}

template<typename T>
inline void Vector2<T>::assign(T const& x, T const& y)
{
    m_x = x;
    m_y = y;
}

template<typename T>
inline void Vector2<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(2), length), m_arr);
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(Vector2<T> const& rhs)
{
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(T scalar)
{
    m_x += scalar;
    m_y += scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& rhs)
{
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(T scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(Vector2<T> const& rhs)
{
    m_x *= rhs.m_x;
    m_y *= rhs.m_y;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(Vector2<T> const& rhs)
{
    m_x /= rhs.m_x;
    m_y /= rhs.m_y;
    
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Vector2<T>::x() const
{
    return m_x;
}
    
template<typename T>
inline T const& Vector2<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const* const Vector2<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline T Vector2<T>::length() const
{
    return std::sqrt((m_x * m_x) + (m_y * m_y));
}

template<typename T>
inline T Vector2<T>::lengthSquared() const
{
    return (m_x * m_x) + (m_y * m_y);
}

template<typename T>
inline void Vector2<T>::normalize()
{
    T len = length();
    
    m_x /= len;
    m_y /= len;
}

template<typename T>
inline bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        && afts::ComparisonUtil::equal(lhs.y(), rhs.y());
}

template<typename T>
inline bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        || !afts::ComparisonUtil::equal(lhs.y(), rhs.y());
}

template<typename T>
inline Vector2<T> operator-(Vector2<T> const& v)
{
    return Vector2<T>(-v.x(), -v.y());
}

template<typename T>
inline Vector2<T> operator+(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(
        lhs.x() + rhs.x(),
        lhs.y() + rhs.y());
}

template<typename T, typename U>
inline Vector2<T> operator+(Vector2<T> const& lhs, U const& rhs)
{
    return Vector2<T>(
        lhs.x() + rhs,
        lhs.y() + rhs);
}

template<typename T>
inline Vector2<T> operator-(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(
        lhs.x() - rhs.x(),
        lhs.y() - rhs.y());
}

template<typename T, typename U>
inline Vector2<T> operator-(Vector2<T>const& lhs, U const& rhs)
{
    return Vector2<T>(
        lhs.x() - rhs,
        lhs.y() - rhs);
}

template<typename T>
inline Vector2<T> operator*(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(
        lhs.x() * rhs.x(),
        lhs.y() * rhs.y());
}

template<typename T, typename U>
inline Vector2<T> operator*(Vector2<T> const& lhs, U const& rhs)
{
    return Vector2<T>(
        lhs.x() * rhs,
        lhs.y() * rhs);
}

template<typename T>
inline Vector2<T> operator/(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(
        lhs.x() / rhs.x(),
        lhs.y() / rhs.y());
}

template<typename T, typename U>
inline Vector2<T> operator/(Vector2<T> const& lhs, U const& rhs)
{
    return Vector2<T>(
        lhs.x() / rhs,
        lhs.y() / rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& v)
{
    os << "[ " << v.x() << " " << v.y() << " ]";

    return os;
}

} // namespace

#endif // INCLUDED
