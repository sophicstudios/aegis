#ifndef INCLUDED_AEGIS_AGTM_MATRIX2_H
#define INCLUDED_AEGIS_AGTM_MATRIX2_H

#include <agtm_vector2.h>
#include <afts_comparisonutil.h>
#include <afts_assert.h>
#include <array>
#include <algorithm>
#include <ostream>
#include <iomanip>

namespace agtm {

template<typename T>
class Matrix2
{
public:
    static Matrix2<T> identity();

    Matrix2();
    
    Matrix2(
        T const& r0c0, T const& r0c1,
        T const& r1c0, T const& r1c1);

    Matrix2(std::array<std::array<T, 2>, 2> const& arr);

    Matrix2(Matrix2<T> const& m);
    
    ~Matrix2();
    
    Matrix2<T>& operator=(Matrix2<T> const& m);
    
    Matrix2<T>& operator+=(Matrix2<T> const& m);
    
    Matrix2<T>& operator+=(T scalar);
    
    Matrix2<T>& operator-=(Matrix2<T> const& m);
    
    Matrix2<T>& operator-=(T scalar);
    
    Matrix2<T>& operator*=(Matrix2<T> const& m);

    Matrix2<T>& operator*=(T scalar);
    
    Matrix2<T>& operator/=(T scalar);

    T operator()(size_t i, size_t j) const;
    
    T& operator()(size_t i, size_t j);
    
    Vector2<T> row(size_t i) const;
    
    Vector2<T> col(size_t i) const;
        
private:
    std::array<std::array<T, 2>, 2> m_arr;
};

template<typename T>
bool operator==(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
bool operator!=(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator+(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator+(Matrix2<T> const& lhs, T scalar);

template<typename T>
Matrix2<T> operator-(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator-(Matrix2<T> const& lhs, T scalar);

template<typename T>
Matrix2<T> operator*(Matrix2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Vector2<T> operator*(Vector2<T> const& lhs, Matrix2<T> const& rhs);

template<typename T>
Vector2<T> operator*(Matrix2<T> const& lhs, Vector2<T> const& rhs);

template<typename T>
Matrix2<T> operator*(Matrix2<T> const& lhs, T scalar);

template<typename T>
Matrix2<T> operator*(T scalar, Matrix2<T> const& rhs);

template<typename T>
Matrix2<T> operator/(Matrix2<T> const& lhs, T scalar);

template<typename T>
Matrix2<T> operator/(T scalar, Matrix2<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix2<T> const& m);

template<typename T>
inline Matrix2<T> Matrix2<T>::identity()
{
    return Matrix2<T>(
        static_cast<T>(1), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(1));
}

template<typename T>
inline Matrix2<T>::Matrix2()
: m_arr{{
    {{T(), T()}},
    {{T(), T()}}
}}
{
    static_assert(std::is_floating_point<T>::value, "Matrix2 only supports floating point types");
}

template<typename T>
inline Matrix2<T>::Matrix2(
    T const& r0c0, T const& r0c1,
    T const& r1c0, T const& r1c1)
: m_arr{{
    {{r0c0, r0c1}},
    {{r1c0, r1c1}}
}}
{
    static_assert(std::is_floating_point<T>::value, "Matrix2 only supports floating point types");
}

template<typename T>
inline Matrix2<T>::Matrix2(std::array<std::array<T, 2>, 2> const& arr)
: m_arr(arr)
{
    static_assert(std::is_floating_point<T>::value, "Matrix2 only supports floating point types");
}

template<typename T>
inline Matrix2<T>::Matrix2(Matrix2<T> const& m)
: m_arr(m.m_arr)
{}

template<typename T>
Matrix2<T>::~Matrix2()
{}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator=(Matrix2<T> const& m)
{
    m_arr = m.m_arr;

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator+=(Matrix2<T> const& m)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] += m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator+=(T scalar)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] += scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator-=(Matrix2<T> const& m)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] -= m.m_arr[i][j];
        }
    }

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator-=(T scalar)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] -= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator*=(Matrix2<T> const& m)
{
    std::array<std::array<T, 2>, 2> arr;
    arr[0][0] = (m_arr[0][0] * m.m_arr[0][0]) + (m_arr[0][1] * m.m_arr[1][0]);
    arr[0][1] = (m_arr[0][0] * m.m_arr[0][1]) + (m_arr[0][1] * m.m_arr[1][1]);
    arr[1][0] = (m_arr[1][0] * m.m_arr[0][0]) + (m_arr[1][1] * m.m_arr[1][0]);
    arr[1][1] = (m_arr[1][0] * m.m_arr[0][1]) + (m_arr[1][1] * m.m_arr[1][1]);

    m_arr = arr;

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator*=(T scalar)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] *= scalar;
        }
    }

    return *this;
}

template<typename T>
inline Matrix2<T>& Matrix2<T>::operator/=(T scalar)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            m_arr[i][j] /= scalar;
        }
    }

    return *this;
}

template<typename T>
inline T Matrix2<T>::operator()(size_t i, size_t j) const
{
    AFTS_ASSERT_DEBUG(i >= 0 && i <= 1 && 0 <= j && j <= 1);
    return m_arr[i][j];
}

template<typename T>
inline T& Matrix2<T>::operator()(size_t i, size_t j)
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 1 && 0 <= j && j <= 1);
    return m_arr[i][j];
}

template<typename T>
inline Vector2<T> Matrix2<T>::row(size_t i) const
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 1);
    return Vector2<T>(m_arr[i][0], m_arr[i][1]);
}

template<typename T>
inline Vector2<T> Matrix2<T>::col(size_t i) const
{
    AFTS_ASSERT_DEBUG(0 <= i && i <= 1)
    return Vector2<T>(m_arr[0][i], m_arr[1][i]);
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
inline Matrix2<T> operator+(Matrix2<T> const& lhs, T scalar)
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
inline Matrix2<T> operator-(Matrix2<T> const& lhs, T scalar)
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
        (lhs(0, 0) * rhs.x()) + (lhs(0, 1) * rhs.y()),
        (lhs(1, 0) * rhs.x()) + (lhs(1, 1) * rhs.y()));
}

template<typename T>
inline Matrix2<T> operator*(Matrix2<T> const& lhs, T scalar)
{
    return Matrix2<T>(
        lhs(0, 0) * scalar, lhs(0, 1) * scalar,
        lhs(1, 0) * scalar, lhs(1, 1) * scalar);
}

template<typename T>
inline Matrix2<T> operator*(T scalar, Matrix2<T> const& rhs)
{
    return Matrix2<T>(
        scalar * rhs(0, 0), scalar * rhs(0, 1),
        scalar * rhs(1, 0), scalar * rhs(1, 1));
}

template<typename T>
inline Matrix2<T> operator/(Matrix2<T> const& lhs, T scalar)
{
    return Matrix2<T>(
        lhs(0, 0) / scalar, lhs(0, 1) / scalar,
        lhs(1, 0) / scalar, lhs(1, 1) / scalar);
}

template<typename T>
inline Matrix2<T> operator/(T scalar, Matrix2<T> const& rhs)
{
    return Matrix2<T>(
        scalar / rhs(0, 0), scalar / rhs(0, 1),
        scalar / rhs(1, 0), scalar / rhs(1, 1));
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Matrix2<T> const& m)
{
    std::streamsize w = os.width();

    os << std::endl
        << std::setw(0)
        << "|" << std::setw(w) << m(0, 0) << " " << std::setw(w) << m(0, 1) << "|" << std::endl
        << "|" << std::setw(w) << m(1, 0) << " " << std::setw(w) << m(1, 1) << "|" << std::endl;
    
    return os;
}

} // namespace

#endif // INCLUDED
