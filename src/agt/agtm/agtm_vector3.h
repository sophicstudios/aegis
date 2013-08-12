#ifndef INCLUDED_AEGIS_AGTM_VECTOR3_H
#define INCLUDED_AEGIS_AGTM_VECTOR3_H

#include <agtm_vector2.h>
#include <afts_comparisonutil.h>
#include <algorithm>
#include <cmath>
#include <iosfwd>

namespace agtm {

template<typename T>
class Vector3
{
public:
    Vector3();
    
    Vector3(T const& x, T const& y, T const& z);
    
    explicit Vector3(Vector2<T> const& v, T const& z = T(0));
    
    Vector3(T const* const arr, size_t length);
    
    Vector3(Vector3<T> const& v);
    
    ~Vector3();

    Vector3<T>& operator=(Vector3<T> const& rhs);
    
    void assign(T const& x, T const& y, T const& z);

    void assign(Vector2<T> const& v, T const& z = T(0));
    
    void assign(T const* const arr, size_t length);
    
    Vector3<T>& operator+=(Vector3<T> const& v);
    
    Vector3<T>& operator+=(T scalar);
    
    Vector3<T>& operator-=(Vector3<T> const& v);
    
    Vector3<T>& operator-=(T scalar);
    
    Vector3<T>& operator*=(Vector3<T> const& v);
    
    Vector3<T>& operator*=(T scalar);
    
    Vector3<T>& operator/=(Vector3<T> const& v);

    Vector3<T>& operator/=(T scalar);
    
    T const& x() const;
    
    T const& y() const;
    
    T const& z() const;
    
    T const* const arr() const;
    
    double length() const;
    
    double lengthSquared() const;
    
    void normalize();
    
private:
    union {
        T m_arr[3];
        struct {
            T m_x;
            T m_y;
            T m_z;
        };
    };
};

template<typename T>
bool operator==(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T>
bool operator!=(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T>
Vector3<T> operator-(Vector3<T> const& v);

template<typename T>
Vector3<T> operator+(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T, typename U>
Vector3<T> operator+(Vector3<T> const& lhs, U const& rhs);

template<typename T>
Vector3<T> operator-(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T, typename U>
Vector3<T> operator-(Vector3<T> const& lhs, U const& rhs);

template<typename T>
Vector3<T> operator*(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T, typename U>
Vector3<T> operator*(Vector3<T> const& lhs, U const& rhs);

template<typename T>
Vector3<T> operator/(Vector3<T> const& lhs, Vector3<T> const& rhs);

template<typename T, typename U>
Vector3<T> operator/(Vector3<T> const& lhs, U const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& v);

template<typename T>
inline Vector3<T>::Vector3()
: m_x(T()),
  m_y(T()),
  m_z(T())
{}

template<typename T>
inline Vector3<T>::Vector3(T const& x, T const& y, T const& z)
: m_x(x),
  m_y(y),
  m_z(z)
{}

template<typename T>
inline Vector3<T>::Vector3(Vector2<T> const& v, T const& z)
: m_x(v.x()),
  m_y(v.y()),
  m_z(z)
{}

template<typename T>
inline Vector3<T>::Vector3(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(3), length), m_arr);
}

template<typename T>
inline Vector3<T>::Vector3(Vector3<T> const& v)
: m_x(v.m_x),
  m_y(v.m_y),
  m_z(v.m_z)
{}

template<typename T>
Vector3<T>::~Vector3()
{}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(Vector3<T> const& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;
    
    return *this;
}

template<typename T>
inline void Vector3<T>::assign(T const& x, T const& y, T const& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

template<typename T>
inline void Vector3<T>::assign(Vector2<T> const& v, T const& z)
{
    m_x = v.x();
    m_y = v.y();
    m_z = z;
}

template<typename T>
inline void Vector3<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(3), length), m_arr);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(Vector3<T> const& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(T scalar)
{
    m_x += scalar;
    m_y += scalar;
    m_z += scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(Vector3<T> const& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(T scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    m_z -= scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(Vector3<T> const& v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(Vector3<T> const& v)
{
    m_x /= v.m_x;
    m_y /= v.m_y;
    m_z /= v.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(T scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Vector3<T>::x() const
{
    return m_x;
}

template<typename T>
inline T const& Vector3<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const& Vector3<T>::z() const
{
    return m_z;
}

template<typename T>
inline T const* const Vector3<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline double Vector3<T>::length() const
{
    return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

template<typename T>
inline double Vector3<T>::lengthSquared() const
{
    return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

template<typename T>
inline void Vector3<T>::normalize()
{
    T len = length();

    m_x /= len;
    m_y /= len;
    m_z /= len;
}

template<typename T>
inline bool operator==(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        && afts::ComparisonUtil::equal(lhs.y(), rhs.y())
        && afts::ComparisonUtil::equal(lhs.z(), rhs.z());
}

template<typename T>
inline bool operator!=(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        || !afts::ComparisonUtil::equal(lhs.y(), rhs.y())
        || !afts::ComparisonUtil::equal(lhs.z(), rhs.z());
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& v)
{
    return Vector3<T>(-v.x(), -v.y(), -v.z());
}

template<typename T>
inline Vector3<T> operator+(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(
        lhs.x() + rhs.x(),
        lhs.y() + rhs.y(),
        lhs.z() + rhs.z());
}

template<typename T, typename U>
inline Vector3<T> operator+(Vector3<T> const& lhs, U const& rhs)
{
    return Vector3<T>(
        lhs.x() + rhs,
        lhs.y() + rhs,
        lhs.z() + rhs);
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(
        lhs.x() - rhs.x(),
        lhs.y() - rhs.y(),
        lhs.z() - rhs.z());
}

template<typename T, typename U>
inline Vector3<T> operator-(Vector3<T> const& lhs, U const& rhs)
{
    return Vector3<T>(
        lhs.x() - rhs,
        lhs.y() - rhs,
        lhs.z() - rhs);
}

template<typename T>
inline Vector3<T> operator*(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(
        lhs.x() * rhs.x(),
        lhs.y() * rhs.y(),
        lhs.z() * rhs.z());
}

template<typename T, typename U>
inline Vector3<T> operator*(Vector3<T> const& lhs, U const& rhs)
{
    return Vector3<T>(
        lhs.x() * rhs,
        lhs.y() * rhs,
        lhs.z() * rhs);
}

template<typename T>
inline Vector3<T> operator/(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(
        lhs.x() / rhs.x(),
        lhs.y() / rhs.y(),
        lhs.z() / rhs.z());
}

template<typename T, typename U>
inline Vector3<T> operator/(Vector3<T> const& lhs, U const& rhs)
{
    return Vector3<T>(
        lhs.x() / rhs,
        lhs.y() / rhs,
        lhs.z() / rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& v)
{
    os << "[ " << v.x() << " " << v.y() << " " << v.z() << " ]";
    return os;
}

} // namespace

#endif // INCLUDED
