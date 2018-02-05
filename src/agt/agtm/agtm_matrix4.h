#ifndef INCLUDED_AEGIS_AGTM_MATRIX4_H
#define INCLUDED_AEGIS_AGTM_MATRIX4_H

#include <agtm_vector4.h>
#include <algorithm>
#include <ostream>
#include <iomanip>

namespace agtm {
/**
 * @class Matrix4
 *
 * A 4x4 Matrix.
 */
template<typename T>
class Matrix4
{
public:
    static Matrix4<T> identity();

    Matrix4();

    Matrix4(
        T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
        T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
        T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
        T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3);

    Matrix4(std::array<std::array<T, 4>, 4> const& arr);

    Matrix4(Matrix4<T> const& m);
    
    ~Matrix4();
    
    Matrix4<T>& operator=(Matrix4<T> const& m);
    
    Matrix4<T>& operator+=(Matrix4<T> const& m);
    
    Matrix4<T>& operator+=(T scalar);
    
    Matrix4<T>& operator-=(Matrix4<T> const& m);
    
    Matrix4<T>& operator-=(T scalar);

    Matrix4<T>& operator*=(Matrix4<T> const& m);
    
    Matrix4<T>& operator*=(T scalar);
    
    Matrix4<T>& operator/=(T scalar);

    T const& operator()(size_t i, size_t j) const;

    T& operator()(size_t i, size_t j);

    Vector4<T> row(size_t i) const;
    
    Vector4<T> col(size_t i) const;
    
private:
    std::array<std::array<T, 4>, 4> m_arr;
};

template<typename T>
bool operator==(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
bool operator!=(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator+(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator+(Matrix4<T> const& lhs, T scalar);

template<typename T>
Matrix4<T> operator-(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator-(Matrix4<T> const& lhs, T scalar);

template<typename T>
Matrix4<T> operator*(Matrix4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Vector4<T> operator*(Matrix4<T> const& lhs, Vector4<T> const& rhs);

template<typename T>
Vector4<T> operator*(Vector4<T> const& lhs, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator*(Matrix4<T> const& lhs, T scalar);

template<typename T>
Matrix4<T> operator*(T scalar, Matrix4<T> const& rhs);

template<typename T>
Matrix4<T> operator/(Matrix4<T> const& lhs, T scalar);

template<typename T>
Matrix4<T> operator/(T scalar, Matrix4<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix4<T> const& m);

template<typename T>
Matrix4<T> Matrix4<T>::identity()
{
    return Matrix4<T>(
        static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}

template<typename T>
inline Matrix4<T>::Matrix4()
: m_arr{{
    {{ T(), T(), T(), T() }},
    {{ T(), T(), T(), T() }},
    {{ T(), T(), T(), T() }},
    {{ T(), T(), T(), T() }}
}}
{
    static_assert(std::is_floating_point<T>::value, "Matrix4 only supports floating point types");
}

template<typename T>
inline Matrix4<T>::Matrix4(
    T const& r0c0, T const& r0c1, T const& r0c2, T const& r0c3,
    T const& r1c0, T const& r1c1, T const& r1c2, T const& r1c3,
    T const& r2c0, T const& r2c1, T const& r2c2, T const& r2c3,
    T const& r3c0, T const& r3c1, T const& r3c2, T const& r3c3)
: m_arr{{
    {{ r0c0, r0c1, r0c2, r0c3 }},
    {{ r1c0, r1c1, r1c2, r1c3 }},
    {{ r2c0, r2c1, r2c2, r2c3 }},
    {{ r3c0, r3c1, r3c2, r3c3 }}
}}
{
    static_assert(std::is_floating_point<T>::value, "Matrix4 only supports floating point types");
}

template<typename T>
inline Matrix4<T>::Matrix4(std::array<std::array<T, 4>, 4> const& arr)
: m_arr(arr)
{
    static_assert(std::is_floating_point<T>::value, "Matrix4 only supports floating point types");
}

template<typename T>
inline Matrix4<T>::Matrix4(Matrix4<T> const& m)
: m_arr(m.m_arr)
{}

template<typename T>
Matrix4<T>::~Matrix4()
{}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator=(Matrix4<T> const& m)
{
    m_arr = m.m_arr;

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(Matrix4<T> const& m)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] += m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(T scalar)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] += scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(Matrix4<T> const& m)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] -= m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(T scalar)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] -= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(Matrix4<T> const& m)
{
    std::array<std::array<T, 4>, 4> arr;

    arr[0][0] = (m_arr[0][0] * m.m_arr[0][0]) + (m_arr[0][1] * m.m_arr[1][0]) + (m_arr[0][2] * m.m_arr[2][0]) + (m_arr[0][3] * m.m_arr[3][0]);
    arr[0][1] = (m_arr[0][0] * m.m_arr[0][1]) + (m_arr[0][1] * m.m_arr[1][1]) + (m_arr[0][2] * m.m_arr[2][1]) + (m_arr[0][3] * m.m_arr[3][1]);
    arr[0][2] = (m_arr[0][0] * m.m_arr[0][2]) + (m_arr[0][1] * m.m_arr[1][2]) + (m_arr[0][2] * m.m_arr[2][2]) + (m_arr[0][3] * m.m_arr[3][2]);
    arr[0][3] = (m_arr[0][0] * m.m_arr[0][3]) + (m_arr[0][1] * m.m_arr[1][3]) + (m_arr[0][2] * m.m_arr[2][3]) + (m_arr[0][3] * m.m_arr[3][3]);

    arr[1][0] = (m_arr[1][0] * m.m_arr[0][0]) + (m_arr[1][1] * m.m_arr[1][0]) + (m_arr[1][2] * m.m_arr[2][0]) + (m_arr[1][3] * m.m_arr[3][0]);
    arr[1][1] = (m_arr[1][0] * m.m_arr[0][1]) + (m_arr[1][1] * m.m_arr[1][1]) + (m_arr[1][2] * m.m_arr[2][1]) + (m_arr[1][3] * m.m_arr[3][1]);
    arr[1][2] = (m_arr[1][0] * m.m_arr[0][2]) + (m_arr[1][1] * m.m_arr[1][2]) + (m_arr[1][2] * m.m_arr[2][2]) + (m_arr[1][3] * m.m_arr[3][2]);
    arr[1][3] = (m_arr[1][0] * m.m_arr[0][3]) + (m_arr[1][1] * m.m_arr[1][3]) + (m_arr[1][2] * m.m_arr[2][3]) + (m_arr[1][3] * m.m_arr[3][3]);

    arr[2][0] = (m_arr[2][0] * m.m_arr[0][0]) + (m_arr[2][1] * m.m_arr[1][0]) + (m_arr[2][2] * m.m_arr[2][0]) + (m_arr[2][3] * m.m_arr[3][0]);
    arr[2][1] = (m_arr[2][0] * m.m_arr[0][1]) + (m_arr[2][1] * m.m_arr[1][1]) + (m_arr[2][2] * m.m_arr[2][1]) + (m_arr[2][3] * m.m_arr[3][1]);
    arr[2][2] = (m_arr[2][0] * m.m_arr[0][2]) + (m_arr[2][1] * m.m_arr[1][2]) + (m_arr[2][2] * m.m_arr[2][2]) + (m_arr[2][3] * m.m_arr[3][2]);
    arr[2][3] = (m_arr[2][0] * m.m_arr[0][3]) + (m_arr[2][1] * m.m_arr[1][3]) + (m_arr[2][2] * m.m_arr[2][3]) + (m_arr[2][3] * m.m_arr[3][3]);

    arr[3][0] = (m_arr[3][0] * m.m_arr[0][0]) + (m_arr[3][1] * m.m_arr[1][0]) + (m_arr[3][2] * m.m_arr[2][0]) + (m_arr[3][3] * m.m_arr[3][0]);
    arr[3][1] = (m_arr[3][0] * m.m_arr[0][1]) + (m_arr[3][1] * m.m_arr[1][1]) + (m_arr[3][2] * m.m_arr[2][1]) + (m_arr[3][3] * m.m_arr[3][1]);
    arr[3][2] = (m_arr[3][0] * m.m_arr[0][2]) + (m_arr[3][1] * m.m_arr[1][2]) + (m_arr[3][2] * m.m_arr[2][2]) + (m_arr[3][3] * m.m_arr[3][2]);
    arr[3][3] = (m_arr[3][0] * m.m_arr[0][3]) + (m_arr[3][1] * m.m_arr[1][3]) + (m_arr[3][2] * m.m_arr[2][3]) + (m_arr[3][3] * m.m_arr[3][3]);

    m_arr = arr;
    
    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(T scalar)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] *= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator/=(T scalar)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            m_arr[i][j] /= scalar;
        }
    }

    return *this;
}

template<typename T>
inline T const& Matrix4<T>::operator()(size_t i, size_t j) const
{
    return m_arr[i][j];
}

template<typename T>
inline T& Matrix4<T>::operator()(size_t i, size_t j)
{
    return m_arr[i][j];
}

template<typename T>
inline Vector4<T> Matrix4<T>::row(size_t i) const
{
    return Vector4<T>(m_arr[i][0], m_arr[i][1], m_arr[i][2], m_arr[i][3]);
}

template<typename T>
inline Vector4<T> Matrix4<T>::col(size_t i) const
{
    return Vector4<T>(m_arr[0][i], m_arr[1][i], m_arr[2][i], m_arr[3][i]);
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
inline Matrix4<T> operator+(Matrix4<T> const& lhs, T scalar)
{
    return Matrix4<T>(
        lhs(0, 0) + scalar, lhs(0, 1) + scalar, lhs(0, 2) + scalar, lhs(0,3) + scalar,
        lhs(1, 0) + scalar, lhs(1, 1) + scalar, lhs(1, 2) + scalar, lhs(1,3) + scalar,
        lhs(2, 0) + scalar, lhs(2, 1) + scalar, lhs(2, 2) + scalar, lhs(2,3) + scalar,
        lhs(3, 0) + scalar, lhs(3, 1) + scalar, lhs(3, 2) + scalar, lhs(3,3) + scalar);
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
inline Matrix4<T> operator-(Matrix4<T> const& lhs, T scalar)
{
    return Matrix4<T>(
        lhs(0, 0) - scalar, lhs(0, 1) - scalar, lhs(0, 2) - scalar, lhs(0,3) - scalar,
        lhs(1, 0) - scalar, lhs(1, 1) - scalar, lhs(1, 2) - scalar, lhs(1,3) - scalar,
        lhs(2, 0) - scalar, lhs(2, 1) - scalar, lhs(2, 2) - scalar, lhs(2,3) - scalar,
        lhs(3, 0) - scalar, lhs(3, 1) - scalar, lhs(3, 2) - scalar, lhs(3,3) - scalar);
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
inline Matrix4<T> operator*(Matrix4<T> const& lhs, T scalar)
{
    return Matrix4<T>(
        lhs(0, 0) * scalar, lhs(0, 1) * scalar, lhs(0, 2) * scalar, lhs(0,3) * scalar,
        lhs(1, 0) * scalar, lhs(1, 1) * scalar, lhs(1, 2) * scalar, lhs(1,3) * scalar,
        lhs(2, 0) * scalar, lhs(2, 1) * scalar, lhs(2, 2) * scalar, lhs(2,3) * scalar,
        lhs(3, 0) * scalar, lhs(3, 1) * scalar, lhs(3, 2) * scalar, lhs(3,3) * scalar);
}

template<typename T>
inline Matrix4<T> operator*(T scalar, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        scalar * rhs(0, 0), scalar * rhs(0, 1), scalar * rhs(0, 2), scalar * rhs(0, 3),
        scalar * rhs(1, 0), scalar * rhs(1, 1), scalar * rhs(1, 2), scalar * rhs(1, 3),
        scalar * rhs(2, 0), scalar * rhs(2, 1), scalar * rhs(2, 2), scalar * rhs(2, 3),
        scalar * rhs(3, 0), scalar * rhs(3, 1), scalar * rhs(3, 2), scalar * rhs(3, 3));
}

template<typename T>
inline Matrix4<T> operator/(Matrix4<T> const& lhs, T scalar)
{
    return Matrix4<T>(
        lhs(0, 0) / scalar, lhs(0, 1) / scalar, lhs(0, 2) / scalar, lhs(0,3) / scalar,
        lhs(1, 0) / scalar, lhs(1, 1) / scalar, lhs(1, 2) / scalar, lhs(1,3) / scalar,
        lhs(2, 0) / scalar, lhs(2, 1) / scalar, lhs(2, 2) / scalar, lhs(2,3) / scalar,
        lhs(3, 0) / scalar, lhs(3, 1) / scalar, lhs(3, 2) / scalar, lhs(3,3) / scalar);
}

template<typename T>
inline Matrix4<T> operator/(T scalar, Matrix4<T> const& rhs)
{
    return Matrix4<T>(
        scalar / rhs(0, 0), scalar / rhs(0, 1), scalar / rhs(0, 2), scalar / rhs(0, 3),
        scalar / rhs(1, 0), scalar / rhs(1, 1), scalar / rhs(1, 2), scalar / rhs(1, 3),
        scalar / rhs(2, 0), scalar / rhs(2, 1), scalar / rhs(2, 2), scalar / rhs(2, 3),
        scalar / rhs(3, 0), scalar / rhs(3, 1), scalar / rhs(3, 2), scalar / rhs(3, 3));
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Matrix4<T> const& m)
{
    std::streamsize w = os.width();

    os << std::endl
        << std::setw(0)
        << "|" << std::setw(w) << m(0, 0) << " " << std::setw(w) << m(0, 1) << " " << std::setw(w) << m(0, 2) << " " << std::setw(w) << m(0, 3) << "|" << std::endl
        << "|" << std::setw(w) << m(1, 0) << " " << std::setw(w) << m(1, 1) << " " << std::setw(w) << m(1, 2) << " " << std::setw(w) << m(1, 3) << "|" << std::endl
        << "|" << std::setw(w) << m(2, 0) << " " << std::setw(w) << m(2, 1) << " " << std::setw(w) << m(2, 2) << " " << std::setw(w) << m(2, 3) << "|" << std::endl
        << "|" << std::setw(w) << m(3, 0) << " " << std::setw(w) << m(3, 1) << " " << std::setw(w) << m(3, 2) << " " << std::setw(w) << m(3, 3) << "|" << std::endl;

    return os;
}

} // namespace

#endif // INCLUDED
