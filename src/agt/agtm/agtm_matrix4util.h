#ifndef INCLUDED_AEGIS_AGTM_MATRIX4UTIL_H
#define INCLUDED_AEGIS_AGTM_MATRIX4UTIL_H

#include <agtm_matrix4.h>
#include <agtm_vector4.h>
#include <array>

namespace agtm {

struct Matrix4Util
{
    template<typename T>
    static Matrix4<T> fromRowMajor(std::array<T, 16> const& arr);

    template<typename T>
    static Matrix4<T> fromColMajor(std::array<T, 16> const& arr);

    template<typename T>
    static Matrix4<T> fromRowVectors(
        Vector4<T> const& row0,
        Vector4<T> const& row1,
        Vector4<T> const& row2,
        Vector4<T> const& row3);

    template<typename T>
    static Matrix4<T> fromColVectors(
        Vector4<T> const& col0,
        Vector4<T> const& col1,
        Vector4<T> const& col2,
        Vector4<T> const& col3);

    template<typename T>
    static std::array<T, 16> toRowMajor(Matrix4<T> const& m);

    template<typename T>
    static std::array<T, 16> toColMajor(Matrix4<T> const& m);

    template<typename T>
    static Matrix4<T> transpose(Matrix4<T> const& m);

    template<typename T>
    static T determinant(Matrix4<T> const& m);
};

template<typename T>
inline Matrix4<T> Matrix4Util::fromRowMajor(std::array<T, 16> const& arr)
{
    return Matrix4<T>(
        arr[0], arr[1], arr[2], arr[3],
        arr[4], arr[5], arr[6], arr[7],
        arr[8], arr[9], arr[10], arr[11],
        arr[12], arr[13], arr[14], arr[15]);
}

template<typename T>
inline Matrix4<T> Matrix4Util::fromColMajor(std::array<T, 16> const& arr)
{
    return Matrix4<T>(
        arr[0], arr[4], arr[8], arr[12],
        arr[1], arr[5], arr[9], arr[13],
        arr[2], arr[6], arr[10], arr[14],
        arr[3], arr[7], arr[11], arr[15]);
}

template<typename T>
inline Matrix4<T> Matrix4Util::fromRowVectors(
    Vector4<T> const& row0,
    Vector4<T> const& row1,
    Vector4<T> const& row2,
    Vector4<T> const& row3)
{
    return Matrix4<T>(
        row0.x(), row0.y(), row0.z(), row0.w(),
        row1.x(), row1.y(), row1.z(), row1.w(),
        row2.x(), row2.y(), row2.z(), row2.w(),
        row3.x(), row3.y(), row3.z(), row3.w());        
}

template<typename T>
inline Matrix4<T> Matrix4Util::fromColVectors(
    Vector4<T> const& col0,
    Vector4<T> const& col1,
    Vector4<T> const& col2,
    Vector4<T> const& col3)
{
    return Matrix4<T>(
        col0.x(), col1.x(), col2.x(), col3.x(),
        col0.y(), col1.y(), col2.y(), col3.y(),
        col0.z(), col1.z(), col2.z(), col3.z(),
        col0.w(), col1.w(), col2.w(), col3.w());
}

template<typename T>
inline std::array<T, 16> Matrix4Util::toRowMajor(Matrix4<T> const& m)
{
    return std::array<T, 16>{{
        m(0, 0), m(0, 1), m(0, 2), m(0, 3),
        m(1, 0), m(1, 1), m(1, 2), m(1, 3),
        m(2, 0), m(2, 1), m(2, 2), m(2, 3),
        m(3, 0), m(3, 1), m(3, 2), m(3, 3)
    }};
}

template<typename T>
inline std::array<T, 16> Matrix4Util::toColMajor(Matrix4<T> const& m)
{
    return std::array<T, 16>{{
        m(0, 0), m(1, 0), m(2, 0), m(3, 0),
        m(0, 1), m(1, 1), m(2, 1), m(3, 1),
        m(0, 2), m(1, 2), m(2, 2), m(3, 2),
        m(0, 3), m(1, 3), m(2, 3), m(3, 3)
    }};
}

template<typename T>
inline Matrix4<T> Matrix4Util::transpose(Matrix4<T> const& m)
{
    return Matrix4<T>(
        m(0, 0), m(1, 0), m(2, 0), m(3, 0),
        m(0, 1), m(1, 1), m(2, 1), m(3, 1),
        m(0, 2), m(1, 2), m(2, 2), m(3, 2),
        m(0, 3), m(1, 3), m(2, 3), m(3, 3));
}

template<typename T>
T Matrix4Util::determinant(Matrix4<T> const& m)
{
    T detLower01 = (m(2, 0) * m(3, 1)) - (m(2, 1) * m(3, 0));
    T detLower02 = (m(2, 0) * m(3, 2)) - (m(2, 2) * m(3, 0));
    T detLower03 = (m(2, 0) * m(3, 3)) - (m(2, 3) * m(3, 0));
    T detLower12 = (m(2, 1) * m(3, 2)) - (m(2, 2) * m(3, 1));
    T detLower13 = (m(2, 1) * m(3, 3)) - (m(2, 3) * m(3, 1));
    T detLower23 = (m(2, 2) * m(3, 3)) - (m(2, 3) * m(3, 2));
    
    T det00 = m(0, 0) * (
        (m(1, 1) * detLower23)
      - (m(1, 2) * detLower13)
      + (m(1, 3) * detLower12));
    
    T det01 = m(0, 1) * (
        (m(1, 0) * detLower23)
      - (m(1, 2) * detLower03)
      + (m(1, 3) * detLower02));

    T det02 = m(0, 2) * (
        (m(1, 0) * detLower13)
      - (m(1, 1) * detLower03)
      + (m(1, 3) * detLower01));

    T det03 = m(0, 3) * (
        (m(1, 0) * detLower12)
      - (m(1, 1) * detLower02)
      + (m(1, 2) * detLower01));
      
    return det00 - det01 + det02 - det03;
}

} // namespace

#endif // INCLUDED
