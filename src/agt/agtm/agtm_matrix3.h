#ifndef INCLUDED_AEGIS_AGTM_MATRIX3_H
#define INCLUDED_AEGIS_AGTM_MATRIX3_H

#include <agtm_vector3.h>
#include <afts_assert.h>
#include <algorithm>
#include <array>
#include <ostream>

namespace agtm {

template<typename T>
class Matrix3
{
public:
    Matrix3();
    
    Matrix3(
        T r0c0, T r0c1, T r0c2,
        T r1c0, T r1c1, T r1c2,
        T r2c0, T r2c1, T r2c2);
    
    Matrix3(std::array<T, 9> const& arr);

    Matrix3(Matrix3<T> const& m);
    
    ~Matrix3();
    
    Matrix3<T>& operator=(Matrix3<T> const& m);
    
    Matrix3<T>& operator+=(Matrix3<T> const& m);
    
    Matrix3<T>& operator+=(T scalar);
    
    Matrix3<T>& operator-=(Matrix3<T> const& m);
    
    Matrix3<T>& operator-=(T scalar);
    
    Matrix3<T>& operator*=(Matrix3<T> const& m);
    
    Matrix3<T>& operator*=(T scalar);
    
    Matrix3<T>& operator/=(T scalar);
    
    T operator()(size_t i, size_t j) const;
    
    T& operator()(size_t i, size_t j);
    
    Vector3<T> row(size_t i) const;
    
    Vector3<T> col(size_t i) const;
    
private:
    std::array<std::array<T, 3>, 3> m_arr;
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
: m_arr{{
    {{T(), T(), T()}},
    {{T(), T(), T()}},
    {{T(), T(), T()}}
}}
{}

template<typename T>
inline Matrix3<T>::Matrix3(
    T r0c0, T r0c1, T r0c2,
    T r1c0, T r1c1, T r1c2,
    T r2c0, T r2c1, T r2c2)
: m_arr{{
    {{r0c0, r0c1, r0c2}},
    {{r1c0, r1c1, r1c2}},
    {{r2c0, r2c1, r2c2}}
}}
{}

template<typename T>
inline Matrix3<T>::Matrix3(std::array<T, 9> const& arr)
: m_arr{{
    {{arr[0], arr[1], arr[2]}},
    {{arr[3], arr[4], arr[5]}},
    {{arr[6], arr[7], arr[8]}}
}}
{}

template<typename T>
inline Matrix3<T>::Matrix3(Matrix3<T> const& m)
: m_arr(m.m_arr)
{}

template<typename T>
Matrix3<T>::~Matrix3()
{}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator=(Matrix3<T> const& m)
{
    m_arr = m.m_arr;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator+=(Matrix3<T> const& m)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] += m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator+=(T scalar)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] += scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator-=(Matrix3<T> const& m)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] -= m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator-=(T scalar)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] -= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator*=(Matrix3<T> const& m)
{
    std::array<std::array<T, 3>, 3> arr;

    arr[0][0] = (m_arr[0][0] * m.m_arr[0][0]) + (m_arr[0][1] * m.m_arr[1][0]) + (m_arr[0][2] * m.m_arr[2][0]);
    arr[0][1] = (m_arr[0][0] * m.m_arr[0][1]) + (m_arr[0][1] * m.m_arr[1][1]) + (m_arr[0][2] * m.m_arr[2][1]);
    arr[0][2] = (m_arr[0][0] * m.m_arr[0][2]) + (m_arr[0][1] * m.m_arr[1][2]) + (m_arr[0][2] * m.m_arr[2][2]);

    arr[1][0] = (m_arr[1][0] * m.m_arr[0][0]) + (m_arr[1][1] * m.m_arr[1][0]) + (m_arr[1][2] * m.m_arr[2][0]);
    arr[1][1] = (m_arr[1][0] * m.m_arr[0][1]) + (m_arr[1][1] * m.m_arr[1][1]) + (m_arr[1][2] * m.m_arr[2][1]);
    arr[1][2] = (m_arr[1][0] * m.m_arr[0][2]) + (m_arr[1][1] * m.m_arr[1][2]) + (m_arr[1][2] * m.m_arr[2][2]);

    arr[2][0] = (m_arr[2][0] * m.m_arr[0][0]) + (m_arr[2][1] * m.m_arr[1][0]) + (m_arr[2][2] * m.m_arr[2][0]);
    arr[2][1] = (m_arr[2][0] * m.m_arr[0][1]) + (m_arr[2][1] * m.m_arr[1][1]) + (m_arr[2][2] * m.m_arr[2][1]);
    arr[2][2] = (m_arr[2][0] * m.m_arr[0][2]) + (m_arr[2][1] * m.m_arr[1][2]) + (m_arr[2][2] * m.m_arr[2][2]);

    m_arr = arr;

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator*=(T scalar)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] *= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix3<T>& Matrix3<T>::operator/=(T scalar)
{
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            m_arr[i][j] /= scalar;
        }
    }

    return *this;
}

template<typename T>
inline T Matrix3<T>::operator()(size_t i, size_t j) const
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 2 && 0 <= j && j <= 2);
    return m_arr[i][j];
}

template<typename T>
inline T& Matrix3<T>::operator()(size_t i, size_t j)
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 2 && 0 <= j && j <= 2);
    return m_arr[i][j];
}

template<typename T>
inline Vector3<T> Matrix3<T>::row(size_t i) const
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 2);
    return Vector3<T>(m_arr[i][0], m_arr[i][1], m_arr[i][2]);
}

template<typename T>
inline Vector3<T> Matrix3<T>::col(size_t i) const
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 2);
    return Vector3<T>(m_arr[0][i], m_arr[1][i], m_arr[2][i]);
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
        << "|" << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << "|" << std::endl
        << "|" << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << "|" << std::endl
        << "|" << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << "|" << std::endl;
    
    return os;
}

} // namespace

#endif // INCLUDED
