#ifndef INCLUDED_AEGIS_AGTM_MATRIX2_H
#define INCLUDED_AEGIS_AGTM_MATRIX2_H

#include <agtm_vector2.h>
#include <afts_comparisonutil.h>
#include <algorithm>
#include <iosfwd>

namespace aegis {
namespace agtm {

template<typename T>
class Matrix2
{
public:    
    Matrix2();
    
    Matrix2(
        T const& r0c0, T const& r0c1,
        T const& r1c0, T const& r1c1);

    Matrix2(T const* const arr, size_t length);
    
    Matrix2(Matrix2<T> const& m);
    
    ~Matrix2();
    
    Matrix2<T>& operator=(Matrix2<T> const& m);
    
    void assign(
        T const& r0c0, T const& r0c1,
        T const& r1c0, T const& r1c1);
    
    void assign(T const* const arr, size_t length);
    
    Matrix2<T>& operator+=(Matrix2<T> const& m);
    
    Matrix2<T>& operator+=(T const& scalar);
    
    Matrix2<T>& operator-=(Matrix2<T> const& m);
    
    Matrix2<T>& operator-=(T const& scalar);
    
    Matrix2<T>& operator*=(Matrix2<T> const& m);

    Matrix2<T>& operator*=(T const& scalar);
    
    Matrix2<T>& operator/=(T const& scalar);

    T const& operator()(size_t i, size_t j) const;
    
    T& operator()(size_t i, size_t j);
    
    Vector2<T> row(size_t i) const;
    
    Vector2<T> col(size_t i) const;
        
    Matrix2<T>& transpose();
    
private:
    union {
        T m_m[2][2];
        T m_arr[4];
        struct {
            T m_r0c0; T m_r0c1;
            T m_r1c0; T m_r1c1;
        };
    };
};

template<typename T>
bool operator==(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
bool operator!=(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator+(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator+(Matrix2<T> const& lhs, T const& scalar);

template<typename T>
Matrix2<T> operator-(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator-(Matrix2<T> const& lhs, T const& scalar);

template<typename T>
Matrix2<T> operator*(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Vector2<T> operator*(Vector2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Vector2<T> operator*(Matrix2<T> const& lhs, Vector2<T> const& rhs);

template<typename T>
Matrix2<T> operator*(Matrix2<T> const& lhs, T const& rhs);

template<typename T>
Matrix2<T> operator*(T const& lhs, Matrix2<T>const& rhs);

template<typename T>
Matrix2<T> operator/(Matrix2<T> const& lhs, T const& rhs);

template<typename T>
Matrix2<T> operator/(T const& lhs, Matrix2<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix2<T> const& m);

template<typename T>
inline Matrix2<T>::Matrix2()
: m_r0c0(T()), m_r0c1(T()),
  m_r1c0(T()), m_r1c1(T())
{}

template<typename T>
inline Matrix2<T>::Matrix2(
    T const& r0c0, T const& r0c1,
    T const& r1c0, T const& r1c1)
: m_r0c0(r0c0), m_r0c1(r0c1),
  m_r1c0(r1c0), m_r1c1(r1c1)
{}

template<typename T>
inline Matrix2<T>::Matrix2(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(4), length), m_arr);
}

template<typename T>
inline Matrix2<T>::Matrix2(Matrix2<T> const& m)
: m_r0c0(m.m_r0c0), m_r0c1(m.m_r0c1),
  m_r1c0(m.m_r1c0), m_r1c1(m.m_r1c1)
{}

template<typename T>
Matrix2<T>::~Matrix2()
{}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator=(Matrix2<T> const& m)
{
    std::copy(m.m_arr, m.m_arr + 4, m_arr);

    return *this;
}

template<typename T>
inline void Matrix2<T>::assign(
    T const& r0c0, T const& r0c1,
    T const& r1c0, T const& r1c1)
{
    m_r0c0 = r0c0;
    m_r0c1 = r0c1;
    m_r1c0 = r1c0;
    m_r1c1 = r1c1;
}

template<typename T>
inline void Matrix2<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(4), length), m_arr);
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator+=(Matrix2<T> const& m)
{
    m_r0c0 += m.m_r0c0;
    m_r0c1 += m.m_r0c1;
    m_r1c0 += m.m_r1c0;
    m_r1c1 += m.m_r1c1;
    
    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator+=(T const& scalar)
{
    m_r0c0 += scalar;
    m_r0c1 += scalar;
    m_r1c0 += scalar;
    m_r1c1 += scalar;

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator-=(Matrix2<T> const& m)
{
    m_r0c0 -= m.m_r0c0;
    m_r0c1 -= m.m_r0c1;
    m_r1c0 -= m.m_r1c0;
    m_r1c1 -= m.m_r1c1;
    
    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator-=(T const& scalar)
{
    m_r0c0 -= scalar;
    m_r0c1 -= scalar;
    m_r1c0 -= scalar;
    m_r1c1 -= scalar;

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator*=(Matrix2<T> const& m)
{
    T arr[4];
    arr[0] = (m_r0c0 * m.m_r0c0) + (m_r0c1 * m.m_r1c0);
    arr[1] = (m_r0c0 * m.m_r1c0) + (m_r0c1 * m.m_r1c1);
    arr[2] = (m_r1c0 * m.m_r0c0) + (m_r1c1 * m.m_r1c0);
    arr[3] = (m_r1c0 * m.m_r1c0) + (m_r1c1 * m.m_r1c1);
    
    std::copy(arr, arr + 4, m_arr);
    
    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator*=(T const& scalar)
{
    m_r0c0 *= scalar;
    m_r0c1 *= scalar;
    m_r1c0 *= scalar;
    m_r1c1 *= scalar;
    
    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator/=(T const& scalar)
{
    m_r0c0 /= scalar;
    m_r0c1 /= scalar;
    m_r1c0 /= scalar;
    m_r1c1 /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Matrix2<T>::operator()(size_t i, size_t j) const
{
    return m_m[i][j];
}

template<typename T>
inline T& Matrix2<T>::operator()(size_t i, size_t j)
{
    return m_m[i][j];
}

template<typename T>
inline Vector2<T> Matrix2<T>::row(size_t i) const
{
    return Vector2<T>(m_m[i][0], m_m[i][1]);
}

template<typename T>
inline Vector2<T> Matrix2<T>::col(size_t i) const
{
    return Vector2<T>(m_m[0][i], m_m[1][i]);
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::transpose()
{
    std::swap(m_r0c1, m_r1c0);
    
    return *this;
}

template<typename T>
inline bool operator==(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        && afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        && afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        && afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1));
}

template<typename T>
inline bool operator!=(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        || !afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        || !afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        || !afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1));
}

template<typename T>
inline Matrix2<T> operator+(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(
        lhs(0, 0) + rhs(0, 0), lhs(0, 1) + rhs(0, 1),
        lhs(1, 0) + rhs(1, 0), lhs(1, 1) + rhs(1, 1));
}

template<typename T>
inline Matrix2<T> operator+(Matrix2<T> const& lhs, T const& scalar)
{
    return Matrix2<T>(
        lhs(0, 0) + scalar, lhs(0, 1) + scalar,
        lhs(1, 0) + scalar, lhs(1, 1) + scalar);
}

template<typename T>
inline Matrix2<T> operator-(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(
        lhs(0, 0) - rhs(0, 0), lhs(0, 1) - rhs(0, 1),
        lhs(1, 0) - rhs(1, 0), lhs(1, 1) - rhs(1, 1));
}

template<typename T>
inline Matrix2<T> operator-(Matrix2<T> const& lhs, T const& scalar)
{
    return Matrix2<T>(
        lhs(0, 0) - scalar, lhs(0, 1) - scalar,
        lhs(1, 0) - scalar, lhs(1, 1) - scalar);
}

template<typename T>
inline Matrix2<T> operator*(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(
        (lhs(0, 0) * rhs(0, 0)) + (lhs(0, 1) * rhs(1, 0)),
        (lhs(0, 0) * rhs(0, 1)) + (lhs(0, 1) * rhs(1, 1)),
        (lhs(1, 0) * rhs(0, 0)) + (lhs(1, 1) * rhs(1, 0)),
        (lhs(1, 0) * rhs(0, 1)) + (lhs(1, 1) * rhs(1, 1)));
}

template<typename T>
inline Vector2<T> operator*(Vector2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Vector2<T>(
        (lhs.x() * rhs(0, 0)) + (lhs.y() * rhs(1, 0)),
        (lhs.x() * rhs(0, 1)) + (lhs.y() * rhs(1, 1)));
}

template<typename T>
inline Vector2<T> operator*(Matrix2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(
        (lhs(0, 0) * lhs.x()) + (lhs(0, 1) * lhs.y()),
        (lhs(1, 0) * lhs.x()) + (lhs(1, 1) * lhs.y()));
}

template<typename T>
inline Matrix2<T> operator*(Matrix2<T> const& lhs, T const& scalar)
{
    return Matrix2<T>(
        lhs(0, 0) * scalar, lhs(0, 1) * scalar,
        lhs(1, 0) * scalar, lhs(1, 1) * scalar);
}

template<typename T>
inline Matrix2<T> operator*(T const& scalar, Matrix2<T>const& rhs)
{
    return Matrix2<T>(
        scalar * rhs(0, 0), scalar * rhs(0, 1),
        scalar * rhs(1, 0), scalar * rhs(1, 1));
}

template<typename T>
inline Matrix2<T> operator/(Matrix2<T> const& lhs, T const& scalar)
{
    return Matrix2<T>(
        lhs(0, 0) / scalar, lhs(0, 1) / scalar,
        lhs(1, 0) / scalar, lhs(1, 1) / scalar);
}

template<typename T>
inline Matrix2<T> operator/(T const& scalar, Matrix2<T>const& rhs)
{
    return Matrix2<T>(
        scalar / rhs(0, 0), scalar / rhs(0, 1),
        scalar / rhs(1, 0), scalar / rhs(1, 1));
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Matrix2<T> const& m)
{
    os << std::endl
        << "|" << m(0, 0) << " " << m(0, 1) << "|" << std::endl
        << "|" << m(1, 0) << " " << m(1, 1) << "|" << std::endl;
    
    return os;
}

} // namespace
} // namespace

#endif // INCLUDED
