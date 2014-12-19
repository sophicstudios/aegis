#ifndef INCLUDED_AEGIS_AGTM_MATRIX4_H
#define INCLUDED_AEGIS_AGTM_MATRIX4_H

#include <agtm_vector4.h>
#include <algorithm>
#include <ostream>

namespace agtm {

template<typename T>
class Matrix4
{
public:
    Matrix4();

    Matrix4(
        T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
        T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
        T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
        T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3);

    Matrix4(T const* const arr, size_t length);
    
    Matrix4(Matrix4<T> const& m);
    
    ~Matrix4();
    
    Matrix4<T>& operator=(Matrix4<T> const& m);
    
    void assign(
        T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
        T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
        T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
        T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3);
    
    void assign(T const* const arr, size_t length);
    
    Matrix4<T>& operator+=(Matrix4<T> const& m);
    
    Matrix4<T>& operator+=(T const& scalar);
    
    Matrix4<T>& operator-=(Matrix4<T> const& m);
    
    Matrix4<T>& operator-=(T const& scalar);

    Matrix4<T>& operator*=(Matrix4<T> const& m);
    
    Matrix4<T>& operator*=(T const& scalar);
    
    Matrix4<T>& operator/=(T const& scalar);

    T const& operator()(size_t i, size_t j) const;

    T& operator()(size_t i, size_t j);

    Vector4<T> row(size_t i) const;
    
    Vector4<T> col(size_t i) const;
    
    Matrix4<T>& transpose();

    T const* const arr() const;
    
private:
    union {
        T m_m[4][4];
        T m_arr[16];
        struct {
            T m_r0c0; T m_r0c1; T m_r0c2; T m_r0c3;
            T m_r1c0; T m_r1c1; T m_r1c2; T m_r1c3;
            T m_r2c0; T m_r2c1; T m_r2c2; T m_r2c3;
            T m_r3c0; T m_r3c1; T m_r3c2; T m_r3c3;
        };
    };
};

template<typename T>
bool operator==(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
bool operator!=(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator+(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator+(Matrix4<T> const& lhs, T const& rhs);

template<typename T>
Matrix4<T> operator-(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator-(Matrix4<T> const& lhs, T const& rhs);

template<typename T>
Matrix4<T> operator*(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Vector4<T> operator*(Matrix4<T> const& lhs, Vector4<T> const& rhs);

template<typename T>
Vector4<T> operator*(Vector4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator*(Matrix4<T> const& lhs, T const& rhs);

template<typename T>
Matrix4<T> operator*(T const& lhs, Matrix4<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix4<T> const& m);

template<typename T>
inline Matrix4<T>::Matrix4()
: m_r0c0(T()), m_r0c1(T()), m_r0c2(T()), m_r0c3(T()),
  m_r1c0(T()), m_r1c1(T()), m_r1c2(T()), m_r1c3(T()),
  m_r2c0(T()), m_r2c1(T()), m_r2c2(T()), m_r2c3(T()),
  m_r3c0(T()), m_r3c1(T()), m_r3c2(T()), m_r3c3(T())
{}

template<typename T>
inline Matrix4<T>::Matrix4(
    T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
    T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
    T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
    T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3)
: m_r0c0(r0c0), m_r0c1(r0c1), m_r0c2(r0c2), m_r0c3(r0c3),
  m_r1c0(r1c0), m_r1c1(r1c1), m_r1c2(r1c2), m_r1c3(r1c3),
  m_r2c0(r2c0), m_r2c1(r2c1), m_r2c2(r2c2), m_r2c3(r2c3),
  m_r3c0(r3c0), m_r3c1(r3c1), m_r3c2(r3c2), m_r3c3(r3c3)
{}

template<typename T>
inline Matrix4<T>::Matrix4(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(16), length), m_arr);
}

template<typename T>
inline Matrix4<T>::Matrix4(Matrix4<T> const& m)
{
    std::copy(m.m_arr, m.m_arr + 16, m_arr);
}

template<typename T>
Matrix4<T>::~Matrix4()
{}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator=(Matrix4<T> const& m)
{
    std::copy(m.m_arr, m.m_arr + 16, m_arr);
}

template<typename T>
inline void Matrix4<T>::assign(
    T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
    T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
    T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
    T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3)
{
    m_r0c0 = r0c0;
    m_r0c1 = r0c1;
    m_r0c2 = r0c2;
    m_r0c3 = r0c3;

    m_r1c0 = r1c0;
    m_r1c1 = r1c1;
    m_r1c2 = r1c2;
    m_r1c3 = r1c3;

    m_r2c0 = r2c0;
    m_r2c1 = r2c1;
    m_r2c2 = r2c2;
    m_r2c3 = r2c3;

    m_r3c0 = r3c0;
    m_r3c1 = r3c1;
    m_r3c2 = r3c2;
    m_r3c3 = r3c3;
}

template<typename T>
inline void Matrix4<T>::assign(T const* const arr, size_t length)
{
    std::copy(arr, arr + std::min(size_t(16), length), m_arr);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(Matrix4<T> const& m)
{
    m_r0c0 += m.m_r0c0;
    m_r0c1 += m.m_r0c1;
    m_r0c2 += m.m_r0c2;
    m_r0c3 += m.m_r0c3;

    m_r1c0 += m.m_r1c0;
    m_r1c1 += m.m_r1c1;
    m_r1c2 += m.m_r1c2;
    m_r1c3 += m.m_r1c3;

    m_r2c0 += m.m_r2c0;
    m_r2c1 += m.m_r2c1;
    m_r2c2 += m.m_r2c2;
    m_r2c3 += m.m_r2c3;

    m_r3c0 += m.m_r3c0;
    m_r3c1 += m.m_r3c1;
    m_r3c2 += m.m_r3c2;
    m_r3c3 += m.m_r3c3;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(T const& scalar)
{
    m_r0c0 += scalar;
    m_r0c1 += scalar;
    m_r0c2 += scalar;
    m_r0c3 += scalar;

    m_r1c0 += scalar;
    m_r1c1 += scalar;
    m_r1c2 += scalar;
    m_r1c3 += scalar;

    m_r2c0 += scalar;
    m_r2c1 += scalar;
    m_r2c2 += scalar;
    m_r2c3 += scalar;

    m_r3c0 += scalar;
    m_r3c1 += scalar;
    m_r3c2 += scalar;
    m_r3c3 += scalar;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(Matrix4<T> const& m)
{
    m_r0c0 -= m.m_r0c0;
    m_r0c1 -= m.m_r0c1;
    m_r0c2 -= m.m_r0c2;
    m_r0c3 -= m.m_r0c3;

    m_r1c0 -= m.m_r1c0;
    m_r1c1 -= m.m_r1c1;
    m_r1c2 -= m.m_r1c2;
    m_r1c3 -= m.m_r1c3;

    m_r2c0 -= m.m_r2c0;
    m_r2c1 -= m.m_r2c1;
    m_r2c2 -= m.m_r2c2;
    m_r2c3 -= m.m_r2c3;

    m_r3c0 -= m.m_r3c0;
    m_r3c1 -= m.m_r3c1;
    m_r3c2 -= m.m_r3c2;
    m_r3c3 -= m.m_r3c3;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(T const& scalar)
{
    m_r0c0 -= scalar;
    m_r0c1 -= scalar;
    m_r0c2 -= scalar;
    m_r0c3 -= scalar;

    m_r1c0 -= scalar;
    m_r1c1 -= scalar;
    m_r1c2 -= scalar;
    m_r1c3 -= scalar;

    m_r2c0 -= scalar;
    m_r2c1 -= scalar;
    m_r2c2 -= scalar;
    m_r2c3 -= scalar;

    m_r3c0 -= scalar;
    m_r3c1 -= scalar;
    m_r3c2 -= scalar;
    m_r3c3 -= scalar;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(Matrix4<T> const& m)
{
    T arr[16];

    arr[0]  = (m_r0c0 * m.m_r0c0) + (m_r0c1 * m.m_r1c0) + (m_r0c2 * m.m_r2c0) + (m_r0c3 * m_r3c0);
    arr[1]  = (m_r0c0 * m.m_r0c1) + (m_r0c1 * m.m_r1c1) + (m_r0c2 * m.m_r2c1) + (m_r0c3 * m_r3c1);
    arr[2]  = (m_r0c0 * m.m_r0c2) + (m_r0c1 * m.m_r1c2) + (m_r0c2 * m.m_r2c2) + (m_r0c3 * m_r3c2);
    arr[3]  = (m_r0c0 * m.m_r0c3) + (m_r0c1 * m.m_r1c3) + (m_r0c2 * m.m_r2c3) + (m_r0c3 * m_r3c3);

    arr[4]  = (m_r1c0 * m.m_r0c0) + (m_r1c1 * m.m_r1c0) + (m_r1c2 * m.m_r2c0) + (m_r1c3 * m_r3c0);
    arr[5]  = (m_r1c0 * m.m_r0c1) + (m_r1c1 * m.m_r1c1) + (m_r1c2 * m.m_r2c1) + (m_r1c3 * m_r3c1);
    arr[6]  = (m_r1c0 * m.m_r0c2) + (m_r1c1 * m.m_r1c2) + (m_r1c2 * m.m_r2c2) + (m_r1c3 * m_r3c2);
    arr[7]  = (m_r1c0 * m.m_r0c3) + (m_r1c1 * m.m_r1c3) + (m_r1c2 * m.m_r2c3) + (m_r1c3 * m_r3c3);

    arr[8]  = (m_r2c0 * m.m_r0c0) + (m_r2c1 * m.m_r1c0) + (m_r2c2 * m.m_r2c0) + (m_r2c3 * m_r3c0);
    arr[9]  = (m_r2c0 * m.m_r0c1) + (m_r2c1 * m.m_r1c1) + (m_r2c2 * m.m_r2c1) + (m_r2c3 * m_r3c1);
    arr[10] = (m_r2c0 * m.m_r0c2) + (m_r2c1 * m.m_r1c2) + (m_r2c2 * m.m_r2c2) + (m_r2c3 * m_r3c2);
    arr[11] = (m_r2c0 * m.m_r0c3) + (m_r2c1 * m.m_r1c3) + (m_r2c2 * m.m_r2c3) + (m_r2c3 * m_r3c3);

    arr[12] = (m_r3c0 * m.m_r0c0) + (m_r3c1 * m.m_r1c0) + (m_r3c2 * m.m_r2c0) + (m_r3c3 * m_r3c0);
    arr[13] = (m_r3c0 * m.m_r0c1) + (m_r3c1 * m.m_r1c1) + (m_r3c2 * m.m_r2c1) + (m_r3c3 * m_r3c1);
    arr[14] = (m_r3c0 * m.m_r0c2) + (m_r3c1 * m.m_r1c2) + (m_r3c2 * m.m_r2c2) + (m_r3c3 * m_r3c2);
    arr[15] = (m_r3c0 * m.m_r0c3) + (m_r3c1 * m.m_r1c3) + (m_r3c2 * m.m_r2c3) + (m_r3c3 * m_r3c3);

    std::copy(arr, arr + 16, m_arr);
    
    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(T const& scalar)
{
    m_r0c0 *= scalar;
    m_r0c1 *= scalar;
    m_r0c2 *= scalar;
    m_r0c3 *= scalar;

    m_r1c0 *= scalar;
    m_r1c1 *= scalar;
    m_r1c2 *= scalar;
    m_r1c3 *= scalar;

    m_r2c0 *= scalar;
    m_r2c1 *= scalar;
    m_r2c2 *= scalar;
    m_r2c3 *= scalar;

    m_r3c0 *= scalar;
    m_r3c1 *= scalar;
    m_r3c2 *= scalar;
    m_r3c3 *= scalar;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator/=(T const& scalar)
{
    m_r0c0 /= scalar;
    m_r0c1 /= scalar;
    m_r0c2 /= scalar;
    m_r0c3 /= scalar;

    m_r1c0 /= scalar;
    m_r1c1 /= scalar;
    m_r1c2 /= scalar;
    m_r1c3 /= scalar;

    m_r2c0 /= scalar;
    m_r2c1 /= scalar;
    m_r2c2 /= scalar;
    m_r2c3 /= scalar;

    m_r3c0 /= scalar;
    m_r3c1 /= scalar;
    m_r3c2 /= scalar;
    m_r3c3 /= scalar;
}

template<typename T>
inline T const& Matrix4<T>::operator()(size_t i, size_t j) const
{
    return m_m[i][j];
}

template<typename T>
inline T& Matrix4<T>::operator()(size_t i, size_t j)
{
    return m_m[i][j];
}

template<typename T>
inline Vector4<T> Matrix4<T>::row(size_t i) const
{
    return Vector4<T>(m_m[i][0], m_m[i][1], m_m[i][2], m_m[i][3]);
}

template<typename T>
inline Vector4<T> Matrix4<T>::col(size_t i) const
{
    return Vector4<T>(m_m[0][i], m_m[1][i], m_m[2][i], m_m[3][i]);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::transpose()
{
    std::swap(m_r0c1, m_r1c0);
    std::swap(m_r0c2, m_r2c0);
    std::swap(m_r0c3, m_r3c0);
    std::swap(m_r1c2, m_r2c1);
    std::swap(m_r1c3, m_r3c1);
    std::swap(m_r2c3, m_r3c2);
}

template<typename T>
inline T const* const Matrix4<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline bool operator==(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        && afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        && afts::ComparisonUtil::equal(lhs(0, 2), rhs(0, 2))
        && afts::ComparisonUtil::equal(lhs(0, 3), rhs(0, 3))
        && afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        && afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1))
        && afts::ComparisonUtil::equal(lhs(1, 2), rhs(1, 2))
        && afts::ComparisonUtil::equal(lhs(1, 3), rhs(1, 3))
        && afts::ComparisonUtil::equal(lhs(2, 0), rhs(2, 0))
        && afts::ComparisonUtil::equal(lhs(2, 1), rhs(2, 1))
        && afts::ComparisonUtil::equal(lhs(2, 2), rhs(2, 2))
        && afts::ComparisonUtil::equal(lhs(2, 3), rhs(2, 3))
        && afts::ComparisonUtil::equal(lhs(3, 0), rhs(3, 0))
        && afts::ComparisonUtil::equal(lhs(3, 1), rhs(3, 1))
        && afts::ComparisonUtil::equal(lhs(3, 2), rhs(3, 2))
        && afts::ComparisonUtil::equal(lhs(3, 3), rhs(3, 3));
}

template<typename T>
inline bool operator!=(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return !afts::ComparisonUtil::equal(lhs(0, 0), rhs(0, 0))
        || !afts::ComparisonUtil::equal(lhs(0, 1), rhs(0, 1))
        || !afts::ComparisonUtil::equal(lhs(0, 2), rhs(0, 2))
        || !afts::ComparisonUtil::equal(lhs(0, 3), rhs(0, 3))
        || !afts::ComparisonUtil::equal(lhs(1, 0), rhs(1, 0))
        || !afts::ComparisonUtil::equal(lhs(1, 1), rhs(1, 1))
        || !afts::ComparisonUtil::equal(lhs(1, 2), rhs(1, 2))
        || !afts::ComparisonUtil::equal(lhs(1, 3), rhs(1, 3))
        || !afts::ComparisonUtil::equal(lhs(2, 0), rhs(2, 0))
        || !afts::ComparisonUtil::equal(lhs(2, 1), rhs(2, 1))
        || !afts::ComparisonUtil::equal(lhs(2, 2), rhs(2, 2))
        || !afts::ComparisonUtil::equal(lhs(2, 3), rhs(2, 3))
        || !afts::ComparisonUtil::equal(lhs(3, 0), rhs(3, 0))
        || !afts::ComparisonUtil::equal(lhs(3, 1), rhs(3, 1))
        || !afts::ComparisonUtil::equal(lhs(3, 2), rhs(3, 2))
        || !afts::ComparisonUtil::equal(lhs(3, 3), rhs(3, 3));
}

template<typename T>
inline Matrix4<T> operator+(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        lhs(0, 0) + rhs(0, 0), lhs(0, 1) + rhs(0, 1), lhs(0, 2) + rhs(0, 2), lhs(0,3) + rhs(0, 3),
        lhs(1, 0) + rhs(1, 0), lhs(1, 1) + rhs(1, 1), lhs(1, 2) + rhs(1, 2), lhs(1,3) + rhs(1, 3),
        lhs(2, 0) + rhs(2, 0), lhs(2, 1) + rhs(2, 1), lhs(2, 2) + rhs(2, 2), lhs(2,3) + rhs(2, 3),
        lhs(3, 0) + rhs(3, 0), lhs(3, 1) + rhs(3, 1), lhs(3, 2) + rhs(3, 2), lhs(3,3) + rhs(3, 3));
}

template<typename T>
inline Matrix4<T> operator+(Matrix4<T> const& lhs, T const& rhs)
{
    return Matrix4<T>(
        lhs(0, 0) + rhs, lhs(0, 1) + rhs, lhs(0, 2) + rhs, lhs(0,3) + rhs,
        lhs(1, 0) + rhs, lhs(1, 1) + rhs, lhs(1, 2) + rhs, lhs(1,3) + rhs,
        lhs(2, 0) + rhs, lhs(2, 1) + rhs, lhs(2, 2) + rhs, lhs(2,3) + rhs,
        lhs(3, 0) + rhs, lhs(3, 1) + rhs, lhs(3, 2) + rhs, lhs(3,3) + rhs);
}

template<typename T>
inline Matrix4<T> operator-(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        lhs(0, 0) - rhs(0, 0), lhs(0, 1) - rhs(0, 1), lhs(0, 2) - rhs(0, 2), lhs(0,3) - rhs(0, 3),
        lhs(1, 0) - rhs(1, 0), lhs(1, 1) - rhs(1, 1), lhs(1, 2) - rhs(1, 2), lhs(1,3) - rhs(1, 3),
        lhs(2, 0) - rhs(2, 0), lhs(2, 1) - rhs(2, 1), lhs(2, 2) - rhs(2, 2), lhs(2,3) - rhs(2, 3),
        lhs(3, 0) - rhs(3, 0), lhs(3, 1) - rhs(3, 1), lhs(3, 2) - rhs(3, 2), lhs(3,3) - rhs(3, 3));
}

template<typename T>
inline Matrix4<T> operator-(Matrix4<T> const& lhs, T const& rhs)
{
    return Matrix4<T>(
        lhs(0, 0) - rhs, lhs(0, 1) - rhs, lhs(0, 2) - rhs, lhs(0,3) - rhs,
        lhs(1, 0) - rhs, lhs(1, 1) - rhs, lhs(1, 2) - rhs, lhs(1,3) - rhs,
        lhs(2, 0) - rhs, lhs(2, 1) - rhs, lhs(2, 2) - rhs, lhs(2,3) - rhs,
        lhs(3, 0) - rhs, lhs(3, 1) - rhs, lhs(3, 2) - rhs, lhs(3,3) - rhs);
}

template<typename T>
inline Matrix4<T> operator*(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        (lhs(0, 0) * rhs(0, 0)) + (lhs(0, 1) * rhs(1, 0)) + (lhs(0, 2) * rhs(2, 0)) + (lhs(0, 3) * rhs(3, 0)),
        (lhs(0, 0) * rhs(0, 1)) + (lhs(0, 1) * rhs(1, 1)) + (lhs(0, 2) * rhs(2, 1)) + (lhs(0, 3) * rhs(3, 1)),
        (lhs(0, 0) * rhs(0, 2)) + (lhs(0, 1) * rhs(1, 2)) + (lhs(0, 2) * rhs(2, 2)) + (lhs(0, 3) * rhs(3, 2)),
        (lhs(0, 0) * rhs(0, 3)) + (lhs(0, 1) * rhs(1, 3)) + (lhs(0, 2) * rhs(2, 3)) + (lhs(0, 3) * rhs(3, 3)),

        (lhs(1, 0) * rhs(0, 0)) + (lhs(1, 1) * rhs(1, 0)) + (lhs(1, 2) * rhs(2, 0)) + (lhs(1, 3) * rhs(3, 0)),
        (lhs(1, 0) * rhs(0, 1)) + (lhs(1, 1) * rhs(1, 1)) + (lhs(1, 2) * rhs(2, 1)) + (lhs(1, 3) * rhs(3, 1)),
        (lhs(1, 0) * rhs(0, 2)) + (lhs(1, 1) * rhs(1, 2)) + (lhs(1, 2) * rhs(2, 2)) + (lhs(1, 3) * rhs(3, 2)),
        (lhs(1, 0) * rhs(0, 3)) + (lhs(1, 1) * rhs(1, 3)) + (lhs(1, 2) * rhs(2, 3)) + (lhs(1, 3) * rhs(3, 3)),

        (lhs(2, 0) * rhs(0, 0)) + (lhs(2, 1) * rhs(1, 0)) + (lhs(2, 2) * rhs(2, 0)) + (lhs(2, 3) * rhs(3, 0)),
        (lhs(2, 0) * rhs(0, 1)) + (lhs(2, 1) * rhs(1, 1)) + (lhs(2, 2) * rhs(2, 1)) + (lhs(2, 3) * rhs(3, 1)),
        (lhs(2, 0) * rhs(0, 2)) + (lhs(2, 1) * rhs(1, 2)) + (lhs(2, 2) * rhs(2, 2)) + (lhs(2, 3) * rhs(3, 2)),
        (lhs(2, 0) * rhs(0, 3)) + (lhs(2, 1) * rhs(1, 3)) + (lhs(2, 2) * rhs(2, 3)) + (lhs(2, 3) * rhs(3, 3)),

        (lhs(3, 0) * rhs(0, 0)) + (lhs(3, 1) * rhs(1, 0)) + (lhs(3, 2) * rhs(2, 0)) + (lhs(3, 3) * rhs(3, 0)),
        (lhs(3, 0) * rhs(0, 1)) + (lhs(3, 1) * rhs(1, 1)) + (lhs(3, 2) * rhs(2, 1)) + (lhs(3, 3) * rhs(3, 1)),
        (lhs(3, 0) * rhs(0, 2)) + (lhs(3, 1) * rhs(1, 2)) + (lhs(3, 2) * rhs(2, 2)) + (lhs(3, 3) * rhs(3, 2)),
        (lhs(3, 0) * rhs(0, 3)) + (lhs(3, 1) * rhs(1, 3)) + (lhs(3, 2) * rhs(2, 3)) + (lhs(3, 3) * rhs(3, 3)));        
}

template<typename T>
inline Vector4<T> operator*(Matrix4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(
        (lhs(0, 0) * rhs.x()) + (lhs(0, 1) * rhs.y()) + (lhs(0, 2) * rhs.z()) + (lhs(0, 3) * rhs.w()),
        (lhs(1, 0) * rhs.x()) + (lhs(1, 1) * rhs.y()) + (lhs(1, 2) * rhs.z()) + (lhs(1, 3) * rhs.w()),
        (lhs(2, 0) * rhs.x()) + (lhs(2, 1) * rhs.y()) + (lhs(2, 2) * rhs.z()) + (lhs(2, 3) * rhs.w()),
        (lhs(3, 0) * rhs.x()) + (lhs(3, 1) * rhs.y()) + (lhs(3, 2) * rhs.z()) + (lhs(3, 3) * rhs.w()));
}

template<typename T>
inline Vector4<T> operator*(Vector4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Vector4<T>(
        (lhs.x() * rhs(0, 0)) + (lhs.y() * rhs(1, 0)) + (lhs.z() * rhs(2, 0)) + (lhs.w() * rhs(3, 0)),
        (lhs.x() * rhs(0, 1)) + (lhs.y() * rhs(1, 1)) + (lhs.z() * rhs(2, 1)) + (lhs.w() * rhs(3, 1)),
        (lhs.x() * rhs(0, 2)) + (lhs.y() * rhs(1, 2)) + (lhs.z() * rhs(2, 2)) + (lhs.w() * rhs(3, 2)),
        (lhs.x() * rhs(0, 3)) + (lhs.y() * rhs(1, 3)) + (lhs.z() * rhs(2, 3)) + (lhs.w() * rhs(3, 3)));
}

template<typename T>
inline Matrix4<T> operator*(Matrix4<T> const& lhs, T const& rhs)
{
    return Matrix4<T>(
        lhs(0, 0) * rhs, lhs(0, 1) * rhs, lhs(0, 2) * rhs, lhs(0,3) * rhs,
        lhs(1, 0) * rhs, lhs(1, 1) * rhs, lhs(1, 2) * rhs, lhs(1,3) * rhs,
        lhs(2, 0) * rhs, lhs(2, 1) * rhs, lhs(2, 2) * rhs, lhs(2,3) * rhs,
        lhs(3, 0) * rhs, lhs(3, 1) * rhs, lhs(3, 2) * rhs, lhs(3,3) * rhs);
}

template<typename T>
inline Matrix4<T> operator*(T const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        lhs * rhs(0, 0), lhs * rhs(0, 1), lhs * rhs(0, 2), lhs * rhs(0, 3),
        lhs * rhs(1, 0), lhs * rhs(1, 1), lhs * rhs(1, 2), lhs * rhs(1, 3),
        lhs * rhs(2, 0), lhs * rhs(2, 1), lhs * rhs(2, 2), lhs * rhs(2, 3),
        lhs * rhs(3, 0), lhs * rhs(3, 1), lhs * rhs(3, 2), lhs * rhs(3, 3));
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Matrix4<T> const& m)
{
    os << std::endl
        << "|" << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << m(0, 3) << "|" << std::endl
        << "|" << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << m(1, 3) << "|" << std::endl
        << "|" << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << m(2, 3) << "|" << std::endl
        << "|" << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << m(3, 3) << "|" << std::endl;
    
    return os;
}

} // namespace

#endif // INCLUDED
