#ifndef INCLUDED_AEGIS_AGTM_VECTOR4_H
#define INCLUDED_AEGIS_AGTM_VECTOR4_H

#include <agtm_vector3.h>
#include <afts_comparisonutil.h>
#include <algorithm>
#include <array>
#include <ostream>
#include <vector>

namespace agtm {

template<typename T>
class Vector4
{
public:
    Vector4();
    
    Vector4(T const& x, T const& y, T const& z, T const& w);

    explicit Vector4(Vector3<T> const& v, T const& w);

    Vector4(std::array<T, 4> const& arr);

    Vector4(std::vector<T> const& vec);

    Vector4(Vector4<T> const& vec);

    ~Vector4();
    
    Vector4<T>& operator=(Vector4<T> const& vec);

    Vector4<T>& operator=(std::array<T, 4> const& arr);

    Vector4<T>& operator=(std::vector<T> const& vec);

    void assign(T const& x, T const& y, T const& z, T const& w);

    void assign(Vector3<T> const& v, T const& w);
        
    Vector4<T>& operator+=(Vector4<T> const& v);
    
    Vector4<T>& operator+=(T scalar);

    Vector4<T>& operator-=(Vector4<T> const& v);
    
    Vector4<T>& operator-=(T scalar);

    Vector4<T>& operator*=(T scalar);

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
bool operator==(Vector4<T> const& vec1, Vector4<T> const& vec2);

template<typename T>
bool operator!=(Vector4<T> const& vec1, Vector4<T> const& vec2);

template<typename T>
Vector4<T> operator-(Vector4<T> const& vec);

template<typename T>
Vector4<T> operator+(Vector4<T> const& vec1, Vector4<T> const& vec2);

template<typename T>
Vector4<T> operator+(Vector4<T> const& vec, T const& scalar);

template<typename T>
Vector4<T> operator-(Vector4<T> const& vec1, Vector4<T> const& vec2);

template<typename T>
Vector4<T> operator-(Vector4<T> const& vec, T const& scalar);

template<typename T>
Vector4<T> operator*(Vector4<T> const& vec, T const& scalar);

template<typename T>
Vector4<T> operator/(Vector4<T> const& vec, T const& scalar);

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

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
inline Vector4<T>::Vector4(Vector3<T> const& vec, T const& w)
: m_x(vec.x()),
  m_y(vec.y()),
  m_z(vec.z()),
  m_w(w)
{}

template<typename T>
inline Vector4<T>::Vector4(std::array<T, 4> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);
}

template<typename T>
inline Vector4<T>::Vector4(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 4);
    std::copy(vec.begin(), vec.end(), m_arr);
}

template<typename T>
inline Vector4<T>::Vector4(Vector4<T> const& vec)
: m_x(vec.m_x),
  m_y(vec.m_y),
  m_z(vec.m_z),
  m_w(vec.m_w)
{}

template<typename T>
Vector4<T>::~Vector4()
{}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(Vector4<T> const& vec)
{
    m_x = vec.m_x;
    m_y = vec.m_y;
    m_z = vec.m_z;
    m_w = vec.m_w;

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(std::array<T, 4> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 4);
    std::copy(vec.begin(), vec.end(), m_arr);

    return *this;
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
inline void Vector4<T>::assign(Vector3<T> const& vec, T const& w)
{
    m_x = vec.x();
    m_y = vec.y();
    m_z = vec.z();
    m_w = w;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(Vector4<T> const& vec)
{
    m_x += vec.m_x;
    m_y += vec.m_y;
    m_z += vec.m_z;
    m_w += vec.m_w;
    
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
inline Vector4<T>& Vector4<T>::operator-=(Vector4<T> const& vec)
{
    m_x -= vec.m_x;
    m_y -= vec.m_y;
    m_z -= vec.m_z;
    m_w -= vec.m_w;
    
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
inline Vector4<T>& Vector4<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    m_w *= scalar;
    
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
inline bool operator==(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        && afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        && afts::ComparisonUtil::equal(vec1.z(), vec2.z())
        && afts::ComparisonUtil::equal(vec1.w(), vec2.w());
}

template<typename T>
inline bool operator!=(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return !afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        || !afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        || !afts::ComparisonUtil::equal(vec1.z(), vec2.z())
        || !afts::ComparisonUtil::equal(vec1.w(), vec2.w());
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& vec)
{
    return Vector4<T>(
        -vec.x(),
        -vec.y(),
        -vec.z(),
        -vec.w());
}

template<typename T>
inline Vector4<T> operator+(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return Vector4<T>(
        vec1.x() + vec2.x(),
        vec1.y() + vec2.y(),
        vec1.z() + vec2.z(),
        vec1.w() + vec2.w());
}

template<typename T>
inline Vector4<T> operator+(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() + scalar,
        vec.y() + scalar,
        vec.z() + scalar,
        vec.w() + scalar);
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return Vector4<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y(),
        vec1.z() - vec2.z(),
        vec1.w() - vec2.w());
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() - scalar,
        vec.y() - scalar,
        vec.z() - scalar,
        vec.w() - scalar);
}

template<typename T>
inline Vector4<T> operator*(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() * scalar,
        vec.y() * scalar,
        vec.z() * scalar,
        vec.w() * scalar);
}
template<typename T>
inline Vector4<T> operator/(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() / scalar,
        vec.y() / scalar,
        vec.z() / scalar,
        vec.w() / scalar);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& vec)
{
    os << "[" << vec.x() << " " << vec.y() << " " << vec.z() << " " << vec.w() << "]";

    return os;
}

} // namespace

#endif // INCLUDED
