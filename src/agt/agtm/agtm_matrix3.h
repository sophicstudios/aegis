#ifndef INCLUDED_AEGIS_AGTM_MATRIX3_H
#define INCLUDED_AEGIS_AGTM_MATRIX3_H

#include <agtm_vector3.h>
#include <algorithm>
#include <iosfwd>

namespace aegis {
namespace agtm {

template<typename T>
class Matrix3
{
public:
    Matrix3();
    
    Matrix3(
        T const& r0c0, T const& r0c1, T const& r0c2,
        T const& r1c0, T const& r1c1, T const& r1c2,
        T const& r2c0, T const& r2c1, T const& r2c2);
    
    Matrix3(T const* const arr, size_t length);

    Matrix3(Matrix3<T> const& m);
    
    ~Matrix3();
    
    Matrix3<T>& operator=(Matrix3<T> const& m);
    
    void assign(
        T const& r0c0, T const& r0c1, T const& r0c2,
        T const& r1c0, T const& r1c1, T const& r1c2,
        T const& r2c0, T const& r2c1, T const& r2c2);
    
    void assign(T const* const arr, size_t length);

    Matrix3<T>& operator+=(Matrix3<T> const& m);
    
    Matrix3<T>& operator+=(T const& scalar);
    
    Matrix3<T>& operator-=(Matrix3<T> const& m);
    
    Matrix3<T>& operator-=(T const& scalar);
    
    Matrix3<T>& operator*=(Matrix3<T> const& m);
    
    Matrix3<T>& operator*=(T const& scalar);
    
    Matrix3<T>& operator/=(T const& scalar);
    
    T const& operator()(size_t i, size_t j) const;
    
    T& operator()(size_t i, size_t j);
    
    Vector3<T> row(size_t i) const;
    
    Vector3<T> col(size_t i) const;
    
    Matrix3<T>& transpose();
    
private:
    union {
        T m_m[3][3];
        T m_arr[9];
        struct {
            T m_r0c0; T m_r0c1; T m_r0c2;
            T m_r1c0; T m_r1c1; T m_r1c2;
            T m_r2c0; T m_r2c1; T m_r2c2;
        };
    };
};

template<typename T>
bool operator==(Matrix3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
bool operator!=(Matrix3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
Matrix3<T> operator+(Matrix3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
Matrix3<T> operator+(Matrix3<T> const& lhs, T const& scalar);

template<typename T>
Matrix3<T> operator-(Matrix3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
Matrix3<T> operator-(Matrix3<T> const& lhs, T const& scalar);

template<typename T>
Matrix3<T> operator*(Matrix3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
Vector3<T> operator*(Matrix3<T> const& lhs, Vector3<T> const& rhs);

template<typename T>
Vector3<T> operator*(Vector3<T> const& lhs, Matrix3<T> const& rhs);

template<typename T>
Matrix3<T> operator*(Matrix3<T> const& lhs, T const& rhs);

template<typename T>
Matrix3<T> operator*(T const& lhs, Matrix3<T> const& rhs);

template<typename T>
Matrix3<T> operator/(Matrix3<T> const& lhs, T const& rhs);

template<typename T>
Matrix3<T> operator/(T const& lhs, Matrix3<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix3<T> const& m);

template<typename T>
inline Matrix3<T>::Matrix3()
: m_r0c0(T()), m_r0c1(T()), m_r0c2(T()),
  m_r1c0(T()), m_r1c1(T()), m_r1c2(T()),
  m_r2c0(T()), m_r2c1(T()), m_r2c2(T())
{}

template<typename T>
inline Matrix3<T>::Matrix3(
    T const& r0c0, T const& r0c1, T const& r0c2,
    T const& r1c0, T const& r1c1, T const& r1c2,
    T const& r2c0, T const& r2c1, T const& r2c2)
: m_r0c0(r0c0), m_r0c1(r0c1), m_r0c2(r0c2),
  m_r1c0(r1c0), m_r1c1(r1c1), m_r1c2(r1c2),
  m_r2c0(r2c0), m_r2c1(r2c1), m_r2c2(r2c2)
{}

template<typename T>
inline Matrix3<T>::Matrix3(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(9), length), m_arr);
}

template<typename T>
inline Matrix3<T>::Matrix3(Matrix3<T> const& m)
{
    std::copy(m.m_arr, m.m_arr + 9, m_arr);
}

template<typename T>
Matrix3<T>::~Matrix3()
{}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator=(Matrix3<T> const& m)
{
    std::copy(m.m_arr, m.m_arr + 9, m_arr);
}

template<typename T>
inline void Matrix3<T>::assign(
    T const& r0c0, T const& r0c1, T const& r0c2,
    T const& r1c0, T const& r1c1, T const& r1c2,
    T const& r2c0, T const& r2c1, T const& r2c2)
{
    m_r0c0 = r0c0;
    m_r0c1 = r0c1;
    m_r0c2 = r0c2;
    
    m_r1c0 = r1c0;
    m_r1c1 = r1c1;
    m_r1c2 = r1c2;

    m_r2c0 = r2c0;
    m_r2c1 = r2c1;
    m_r2c2 = r2c2;
}

template<typename T>
inline void Matrix3<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(9), length), m_arr);
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator+=(Matrix3<T> const& m)
{
    m_r0c0 += m.m_r0c0;
    m_r0c1 += m.m_r0c1;
    m_r0c2 += m.m_r0c2;

    m_r1c0 += m.m_r1c0;
    m_r1c1 += m.m_r1c1;
    m_r1c2 += m.m_r1c2;

    m_r2c0 += m.m_r2c0;
    m_r2c1 += m.m_r2c1;
    m_r2c2 += m.m_r2c2;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator+=(T const& scalar)
{
    m_r0c0 += scalar;
    m_r0c1 += scalar;
    m_r0c2 += scalar;

    m_r1c0 += scalar;
    m_r1c1 += scalar;
    m_r1c2 += scalar;

    m_r2c0 += scalar;
    m_r2c1 += scalar;
    m_r2c2 += scalar;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator-=(Matrix3<T> const& m)
{
    m_r0c0 -= m.m_r0c0;
    m_r0c1 -= m.m_r0c1;
    m_r0c2 -= m.m_r0c2;

    m_r1c0 -= m.m_r1c0;
    m_r1c1 -= m.m_r1c1;
    m_r1c2 -= m.m_r1c2;

    m_r2c0 -= m.m_r2c0;
    m_r2c1 -= m.m_r2c1;
    m_r2c2 -= m.m_r2c2;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator-=(T const& scalar)
{
    m_r0c0 -= scalar;
    m_r0c1 -= scalar;
    m_r0c2 -= scalar;

    m_r1c0 -= scalar;
    m_r1c1 -= scalar;
    m_r1c2 -= scalar;

    m_r2c0 -= scalar;
    m_r2c1 -= scalar;
    m_r2c2 -= scalar;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator*=(Matrix3<T> const& m)
{
    T arr[9];

    arr[0] = (m_r0c0 * m.m_r0c0) + (m_r0c1 * m.m_r1c0) + (m_r0c2 * m.m_r2c0);
    arr[1] = (m_r0c0 * m.m_r0c1) + (m_r0c1 * m.m_r1c1) + (m_r0c2 * m.m_r2c1);
    arr[2] = (m_r0c0 * m.m_r0c2) + (m_r0c1 * m.m_r1c2) + (m_r0c2 * m.m_r2c2);

    arr[3] = (m_r1c0 * m.m_r0c0) + (m_r1c1 * m.m_r1c0) + (m_r1c2 * m.m_r2c0);
    arr[4] = (m_r1c0 * m.m_r0c1) + (m_r1c1 * m.m_r1c1) + (m_r1c2 * m.m_r2c1);
    arr[5] = (m_r1c0 * m.m_r0c2) + (m_r1c1 * m.m_r1c2) + (m_r1c2 * m.m_r2c2);

    arr[6] = (m_r2c0 * m.m_r0c0) + (m_r2c1 * m.m_r1c0) + (m_r2c2 * m.m_r2c0);
    arr[7] = (m_r2c0 * m.m_r0c1) + (m_r2c1 * m.m_r1c1) + (m_r2c2 * m.m_r2c1);
    arr[8] = (m_r2c0 * m.m_r0c2) + (m_r2c1 * m.m_r1c2) + (m_r2c2 * m.m_r2c2);

    std::copy(arr, arr + 9, m_arr);
    
    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator*=(T const& scalar)
{
    m_r0c0 *= scalar;
    m_r0c1 *= scalar;
    m_r0c2 *= scalar;

    m_r1c0 *= scalar;
    m_r1c1 *= scalar;
    m_r1c2 *= scalar;

    m_r2c0 *= scalar;
    m_r2c1 *= scalar;
    m_r2c2 *= scalar;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator/=(T const& scalar)
{
    m_r0c0 /= scalar;
    m_r0c1 /= scalar;
    m_r0c2 /= scalar;

    m_r1c0 /= scalar;
    m_r1c1 /= scalar;
    m_r1c2 /= scalar;

    m_r2c0 /= scalar;
    m_r2c1 /= scalar;
    m_r2c2 /= scalar;

    return *this;
}

template<typename T>
inline T const& Matrix3<T>::operator()(size_t i, size_t j) const
{
    return m_m[i][j];
}

template<typename T>
inline T& Matrix3<T>::operator()(size_t i, size_t j)
{
    return m_m[i][j];
}

template<typename T>
inline Vector3<T> Matrix3<T>::row(size_t i) const
{
    return Vector3<T>(m_m[i][0], m_m[i][1], m_m[i][2]);
}

template<typename T>
inline Vector3<T> Matrix3<T>::col(size_t i) const
{
    return Vector3<T>(m_m[0][i], m_m[1][i], m_m[2][i]);
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::transpose()
{
    std::swap(m_r0c1, m_r1c0);
    std::swap(m_r0c2, m_r2c0);
    std::swap(m_r1c2, m_r2c1);
}

template<typename T>
inline bool operator==(Matrix3<T> const& lhs, Matrix3<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        && afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        && afts::ComparisonUtil::equal(lhs(0, 2), rhs(0, 2))
        && afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        && afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1))
        && afts::ComparisonUtil::equal(lhs(1, 2), rhs(1, 2))
        && afts::ComparisonUtil::equal(lhs(2, 0), rhs(2, 0))
        && afts::ComparisonUtil::equal(lhs(2, 1), rhs(2, 1))
        && afts::ComparisonUtil::equal(lhs(2, 2), rhs(2, 2));
}

template<typename T>
inline bool operator!=(Matrix3<T> const& lhs, Matrix3<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        || !afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        || !afts::ComparisonUtil::equal(lhs(0, 2), rhs(0, 2))
        || !afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        || !afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1))
        || !afts::ComparisonUtil::equal(lhs(1, 2), rhs(1, 2))
        || !afts::ComparisonUtil::equal(lhs(2, 0), rhs(2, 0))
        || !afts::ComparisonUtil::equal(lhs(2, 1), rhs(2, 1))
        || !afts::ComparisonUtil::equal(lhs(2, 2), rhs(2, 2));
}

template<typename T>
inline Matrix3<T> operator+(Matrix3<T> const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) + rhs(0, 0), lhs(0, 1) + rhs(0, 1), lhs(0, 2) + rhs(0, 2),
        lhs(1, 0) + rhs(1, 0), lhs(1, 1) + rhs(1, 1), lhs(1, 2) + rhs(1, 2),
        lhs(2, 0) + rhs(2, 0), lhs(2, 1) + rhs(2, 1), lhs(2, 2) + rhs(2, 2));
}

template<typename T>
inline Matrix3<T> operator+(Matrix3<T> const& lhs, T const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) + rhs, lhs(0, 1) + rhs, lhs(0, 2) + rhs,
        lhs(1, 0) + rhs, lhs(1, 1) + rhs, lhs(1, 2) + rhs,
        lhs(2, 0) + rhs, lhs(2, 1) + rhs, lhs(2, 2) + rhs);
}

template<typename T>
inline Matrix3<T> operator-(Matrix3<T> const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) - rhs(0, 0), lhs(0, 1) - rhs(0, 1), lhs(0, 2) - rhs(0, 2),
        lhs(1, 0) - rhs(1, 0), lhs(1, 1) - rhs(1, 1), lhs(1, 2) - rhs(1, 2),
        lhs(2, 0) - rhs(2, 0), lhs(2, 1) - rhs(2, 1), lhs(2, 2) - rhs(2, 2));
}

template<typename T>
inline Matrix3<T> operator-(Matrix3<T> const& lhs, T const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) - rhs, lhs(0, 1) - rhs, lhs(0, 2) - rhs,
        lhs(1, 0) - rhs, lhs(1, 1) - rhs, lhs(1, 2) - rhs,
        lhs(2, 0) - rhs, lhs(2, 1) - rhs, lhs(2, 2) - rhs);
}

template<typename T>
inline Matrix3<T> operator*(Matrix3<T> const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        (lhs(0, 0) * rhs(0, 0)) + (lhs(0, 1) * rhs(1, 0)) + (lhs(0, 2) * rhs(2, 0)),
        (lhs(0, 0) * rhs(0, 1)) + (lhs(0, 1) * rhs(1, 1)) + (lhs(0, 2) * rhs(2, 1)),
        (lhs(0, 0) * rhs(0, 2)) + (lhs(0, 1) * rhs(1, 2)) + (lhs(0, 2) * rhs(2, 2)),
        (lhs(1, 0) * rhs(0, 0)) + (lhs(1, 1) * rhs(1, 0)) + (lhs(1, 2) * rhs(2, 0)),
        (lhs(1, 0) * rhs(0, 1)) + (lhs(1, 1) * rhs(1, 1)) + (lhs(1, 2) * rhs(2, 1)),
        (lhs(1, 0) * rhs(0, 2)) + (lhs(1, 1) * rhs(1, 2)) + (lhs(1, 2) * rhs(2, 2)),
        (lhs(2, 0) * rhs(0, 0)) + (lhs(2, 1) * rhs(1, 0)) + (lhs(2, 2) * rhs(2, 0)),
        (lhs(2, 0) * rhs(0, 1)) + (lhs(2, 1) * rhs(1, 1)) + (lhs(2, 2) * rhs(2, 1)),
        (lhs(2, 0) * rhs(0, 2)) + (lhs(2, 1) * rhs(1, 2)) + (lhs(2, 2) * rhs(2, 2)));
}

template<typename T>
inline Vector3<T> operator*(Matrix3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(
        (lhs(0, 0) * rhs.x()) + (lhs(0, 1) * rhs.y()) + (lhs(0, 2) * rhs.z()),
        (lhs(1, 0) * rhs.x()) + (lhs(1, 1) * rhs.y()) + (lhs(1, 2) * rhs.z()),
        (lhs(2, 0) * rhs.x()) + (lhs(2, 1) * rhs.y()) + (lhs(2, 2) * rhs.z()));
}

template<typename T>
inline Vector3<T> operator*(Vector3<T> const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        (lhs.x() * rhs(0, 0)) + (lhs.y() * rhs(1, 0)) + (lhs.z() * rhs(2, 0)),
        (lhs.x() * rhs(0, 1)) + (lhs.y() * rhs(1, 1)) + (lhs.z() * rhs(2, 1)),
        (lhs.x() * rhs(0, 2)) + (lhs.y() * rhs(1, 2)) + (lhs.z() * rhs(2, 2)));
}

template<typename T>
inline Matrix3<T> operator*(Matrix3<T> const& lhs, T const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) * rhs, lhs(0, 1) * rhs, lhs(0, 2) * rhs,
        lhs(1, 0) * rhs, lhs(1, 1) * rhs, lhs(1, 2) * rhs,
        lhs(2, 0) * rhs, lhs(2, 1) * rhs, lhs(2, 2) * rhs);
}

template<typename T>
inline Matrix3<T> operator*(T const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        lhs * rhs(0, 0), lhs * rhs(0, 1), lhs * rhs(0, 2),
        lhs * rhs(1, 0), lhs * rhs(1, 1), lhs * rhs(1, 2),
        lhs * rhs(2, 0), lhs * rhs(2, 1), lhs * rhs(2, 2));
}

template<typename T>
inline Matrix3<T> operator/(Matrix3<T> const& lhs, T const& rhs)
{
    return Matrix3<T>(
        lhs(0, 0) / rhs, lhs(0, 1) / rhs, lhs(0, 2) / rhs,
        lhs(1, 0) / rhs, lhs(1, 1) / rhs, lhs(1, 2) / rhs,
        lhs(2, 0) / rhs, lhs(2, 1) / rhs, lhs(2, 2) / rhs);
}

template<typename T>
inline Matrix3<T> operator/(T const& lhs, Matrix3<T> const& rhs)
{
    return Matrix3<T>(
        lhs / rhs(0, 0), lhs / rhs(0, 1), lhs / rhs(0, 2),
        lhs / rhs(1, 0), lhs / rhs(1, 1), lhs / rhs(1, 2),
        lhs / rhs(2, 0), lhs / rhs(2, 1), lhs / rhs(2, 2));
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Matrix3<T> const& m)
{
    os << std::endl
        << "| " << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " |" << std::endl
        << "| " << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " |" << std::endl
        << "| " << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " |" << std::endl;
    
    return os;
}

} // namespace
} // namespace

#endif // INCLUDED
