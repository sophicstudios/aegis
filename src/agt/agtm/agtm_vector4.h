#ifndef INCLUDED_AEGIS_AGTM_VECTOR4_H
#define INCLUDED_AEGIS_AGTM_VECTOR4_H

#include <agtm_vector3.h>
#include <afts_comparisonutil.h>
#include <algorithm>
#include <ostream>

namespace agtm {

template<typename T>
class Vector4
{
public:
    Vector4();
    
    Vector4(T const& x, T const& y, T const& z, T const& w = T(1));

    explicit Vector4(Vector3<T> const& v, T const& w= T(1));

    Vector4(T const* const arr, size_t length);
    
    Vector4(Vector4<T> const& v);

    ~Vector4();
    
    Vector4<T>& operator=(Vector4<T> const& rhs);
    
    void assign(T const& x, T const& y, T const& z, T const& w = T(1));

    void assign(Vector3<T> const& v, T const& w = T(1));
    
    void assign(T const* const arr, size_t length);
        
    Vector4<T>& operator+=(Vector4<T> const& v);
    
    Vector4<T>& operator+=(T scalar);

    Vector4<T>& operator-=(Vector4<T> const& v);
    
    Vector4<T>& operator-=(T scalar);

    Vector4<T>& operator*=(Vector4<T> const& v);
    
    Vector4<T>& operator*=(T scalar);
    
    Vector4<T>& operator/=(Vector4<T> const& v);

    Vector4<T>& operator/=(T scalar);
    
    T const& x() const;
    
    T const& y() const;
    
    T const& z() const;
    
    T const& w() const;
    
    T const* const arr() const;
    
    Vector3<T> vector3() const;
    
private:
    union {
        T m_arr[4];
        struct {
            T m_x;
            T m_y;
            T m_z;
            T m_w;
        };
    };
};

template<typename T>
bool operator==(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T>
bool operator!=(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T>
Vector4<T> operator-(Vector4<T> const& v);

template<typename T>
Vector4<T> operator+(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T, typename U>
Vector4<T> operator+(Vector4<T> const& lhs, U const& scalar);

template<typename T>
Vector4<T> operator-(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T, typename U>
Vector4<T> operator-(Vector4<T> const& lhs, U const& scalar);

template<typename T>
Vector4<T> operator*(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T, typename U>
Vector4<T> operator*(Vector4<T> const& lhs, U const& scalar);

template<typename T>
Vector4<T> operator/(Vector4<T> const& lhs, Vector4<T> const& rhs);

template<typename T, typename U>
Vector4<T> operator/(Vector4<T> const& lhs, U const& scalar);

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& v);

template<typename T>
inline Vector4<T>::Vector4()
: m_x(T()),
  m_y(T()),
  m_z(T()),
  m_w(T())
{}

template<typename T>
inline Vector4<T>::Vector4(T const& x, T const& y, T const& z, T const& w)
: m_x(x),
  m_y(y),
  m_z(z),
  m_w(w)
{}

template<typename T>
inline Vector4<T>::Vector4(Vector3<T> const& v, T const& w)
: m_x(v.x()),
  m_y(v.y()),
  m_z(v.z()),
  m_w(w)
{}

template<typename T>
inline Vector4<T>::Vector4(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(4), length), m_arr);
}

template<typename T>
inline Vector4<T>::Vector4(Vector4<T> const& v)
: m_x(v.m_x),
  m_y(v.m_y),
  m_z(v.m_z),
  m_w(v.m_w)
{}

template<typename T>
Vector4<T>::~Vector4()
{}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(Vector4<T> const& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    m_z = rhs.m_z;
    m_w = rhs.m_w;
}

template<typename T>
inline void Vector4<T>::assign(T const& x, T const& y, T const& z, T const& w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

template<typename T>
inline void Vector4<T>::assign(Vector3<T> const& v, T const& w)
{
    m_x = v.x();
    m_y = v.y();
    m_z = v.z();
    m_w = w;
}

template<typename T>
inline void Vector4<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(4), length), m_arr);
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(Vector4<T> const& v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    m_z += v.m_z;
    m_w += v.m_w;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(T scalar)
{
    m_x += scalar;
    m_y += scalar;
    m_z += scalar;
    m_w += scalar;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(Vector4<T> const& v)
{
    m_x -= v.m_x;
    m_y -= v.m_y;
    m_z -= v.m_z;
    m_w -= v.m_w;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(T scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    m_z -= scalar;
    m_w -= scalar;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::Vector4<T>::operator*=(Vector4<T> const& v)
{
    m_x *= v.m_x;
    m_y *= v.m_y;
    m_z *= v.m_z;
    m_w *= v.m_w;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(Vector4<T> const& v)
{
    m_x /= v.m_x;
    m_y /= v.m_y;
    m_z /= v.m_z;
    m_w /= v.m_w;
    
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(T scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    m_w /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Vector4<T>::x() const
{
    return m_x;
}

template<typename T>
inline T const& Vector4<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const& Vector4<T>::z() const
{
    return m_z;
}

template<typename T>
inline T const& Vector4<T>::w() const
{
    return m_w;
}

template<typename T>
inline T const* const Vector4<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline Vector3<T> Vector4<T>::vector3() const
{
    return Vector3<T>(m_x / m_w, m_y / m_w, m_z / m_w);
}

template<typename T>
inline bool operator==(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        && afts::ComparisonUtil::equal(lhs.y(), rhs.y())
        && afts::ComparisonUtil::equal(lhs.z(), rhs.z())
        && afts::ComparisonUtil::equal(lhs.w(), rhs.w());
}

template<typename T>
inline bool operator!=(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs.x(), rhs.x())
        || !afts::ComparisonUtil::equal(lhs.y(), rhs.y())
        || !afts::ComparisonUtil::equal(lhs.z(), rhs.z())
        || !afts::ComparisonUtil::equal(lhs.w(), rhs.w());
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& v)
{
    return Vector4<T>(
        -v.x(),
        -v.y(),
        -v.z(),
        -v.w());
}

template<typename T>
inline Vector4<T> operator+(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(
        lhs.x() + rhs.x(),
        lhs.y() + rhs.y(),
        lhs.z() + rhs.z(),
        lhs.w() + rhs.w());
}

template<typename T, typename U>
inline Vector4<T> operator+(Vector4<T> const& lhs, U const& rhs)
{
    return Vector4<T>(
        lhs.x() + rhs,
        lhs.y() + rhs,
        lhs.z() + rhs,
        lhs.w() + rhs);
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(
        lhs.x() - rhs.x(),
        lhs.y() - rhs.y(),
        lhs.z() - rhs.z(),
        lhs.w() - rhs.w());
}

template<typename T, typename U>
inline Vector4<T> operator-(Vector4<T> const& lhs, U const& rhs)
{
    return Vector4<T>(
        lhs.x() - rhs,
        lhs.y() - rhs,
        lhs.z() - rhs,
        lhs.w() - rhs);
}

template<typename T>
inline Vector4<T> operator*(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(
        lhs.x() * rhs.x(),
        lhs.y() * rhs.y(),
        lhs.z() * rhs.z(),
        lhs.w() * rhs.w());
}

template<typename T, typename U>
inline Vector4<T> operator*(Vector4<T> const& lhs, U const& rhs)
{
    return Vector4<T>(
        lhs.x() * rhs,
        lhs.y() * rhs,
        lhs.z() * rhs,
        lhs.w() * rhs);
}

template<typename T>
inline Vector4<T> operator/(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(
        lhs.x() / rhs.x(),
        lhs.y() / rhs.y(),
        lhs.z() / rhs.z(),
        lhs.w() / rhs.w());
}

template<typename T, typename U>
inline Vector4<T> operator/(Vector4<T> const& lhs, U const& rhs)
{
    return Vector4<T>(
        lhs.x() / rhs,
        lhs.y() / rhs,
        lhs.z() / rhs,
        lhs.w() / rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& v)
{
    os << "[" << v.x() << " " << v.y() << " " << v.z() << " " << v.w() << "]";
    return os;
}

} // namespace

#endif // INCLUDED
