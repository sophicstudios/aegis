#ifndef INCLUDED_AEGIS_AGTM_MATRIX3UTIL_H
#define INCLUDED_AEGIS_AGTM_MATRIX3UTIL_H

#include <agtm_matrix3.h>
#include <agtm_vector3.h>
#include <array>

namespace agtm {

struct Matrix3Util
{
    template<typename T>
    static Matrix3<T> fromRowMajor(std::array<T, 9> const& arr);

    template<typename T>
    static Matrix3<T> fromColMajor(std::array<T, 9> const& arr);

    template<typename T>
    static Matrix3<T> fromRowVectors(
        Vector3<T> const& row0,
        Vector3<T> const& row1,
        Vector3<T> const& row2);

    template<typename T>
    static Matrix3<T> fromColVectors(
        Vector3<T> const& col0,
        Vector3<T> const& col1,
        Vector3<T> const& col2);

    template<typename T>
    static std::array<T, 9> toRowMajor(Matrix3<T> const& m);

    template<typename T>
    static std::array<T, 9> toColMajor(Matrix3<T> const& m);

    template<typename T>
    static Matrix3<T> transpose(Matrix3<T> const& m);
    
    template<typename T>
    static T determinant(Matrix3<T> const& m);
};

template<typename T>
Matrix3<T> Matrix3Util::fromRowMajor(std::array<T, 9> const& arr)
{
    return Matrix3<T>(
        arr[0], arr[1], arr[2],
        arr[3], arr[4], arr[5],
        arr[6], arr[7], arr[8]);
}

template<typename T>
Matrix3<T> Matrix3Util::fromColMajor(std::array<T, 9> const& arr)
{
    return Matrix3<T>(
        arr[0], arr[3], arr[6],
        arr[1], arr[4], arr[7],
        arr[2], arr[5], arr[8]);
}

template<typename T>
inline Matrix3<T> Matrix3Util::fromRowVectors(
    Vector3<T> const& row0,
    Vector3<T> const& row1,
    Vector3<T> const& row2)
{
    return Matrix3<T>(
        row0.x(), row0.y(), row0.z(),
        row1.x(), row1.y(), row1.z(),
        row2.x(), row2.y(), row2.z());
}
    
template<typename T>
inline Matrix3<T> Matrix3Util::fromColVectors(
    Vector3<T> const& col0,
    Vector3<T> const& col1,
    Vector3<T> const& col2)
{
    return Matrix3<T>(
        col0.x(), col1.x(), col2.x(),
        col0.y(), col1.y(), col2.y(),
        col0.z(), col1.z(), col2.z());
}
    
template<typename T>
std::array<T, 9> Matrix3Util::toRowMajor(Matrix3<T> const& m)
{
    return std::array<T, 9>{{
        m(0, 0), m(0, 1), m(0, 2),
        m(1, 0), m(1, 1), m(1, 2),
        m(2, 0), m(2, 1), m(2, 2)
    }};
}

template<typename T>
std::array<T, 9> Matrix3Util::toColMajor(Matrix3<T> const& m)
{
    return std::array<T, 9>{{
        m(0, 0), m(1, 0), m(2, 0),
        m(0, 1), m(1, 1), m(2, 1),
        m(0, 2), m(1, 2), m(2, 2)
    }};
}

template<typename T>
inline Matrix3<T> Matrix3Util::transpose(Matrix3<T> const& m)
{
    return Matrix3<T>(
        m(0, 0), m(1, 0), m(2, 0),
        m(0, 1), m(1, 1), m(2, 1),
        m(0, 2), m(1, 2), m(2, 2));
}

template<typename T>
inline T Matrix3Util::determinant(Matrix3<T> const& m)
{
    return (m(0, 0) * ((m(1, 1) * m(2, 2)) - (m(1, 2) * m(2, 1))))
         - (m(0, 1) * ((m(1, 0) * m(2, 2)) - (m(1, 2) * m(2, 0))))
         + (m(0, 2) * ((m(1, 0) * m(2, 1)) - (m(1, 1) * m(2, 0))));
}

} // namespace

#endif // INCLUDED
