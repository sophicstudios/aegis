#ifndef INCLUDED_AEGIS_AGTM_MATRIX2UTIL_H
#define INCLUDED_AEGIS_AGTM_MATRIX2UTIL_H

#include <agtm_matrix2.h>
#include <agtm_vector2.h>
#include <array>

namespace agtm {

struct Matrix2Util
{
    template<typename T>
    static Matrix2<T> fromRowMajor(std::array<T, 4> const& arr);

    template<typename T>
    static Matrix2<T> fromColMajor(std::array<T, 4> const& arr);

    template<typename T>
    static Matrix2<T> fromRowVectors(Vector2<T> const& row0, Vector2<T> const& row1);

    template<typename T>
    static Matrix2<T> fromColVectors(Vector2<T> const& col0, Vector2<T> const& col1);

    template<typename T>
    static std::array<T, 4> toRowMajor(Matrix2<T> const& m);

    template<typename T>
    static std::array<T, 4> toColMajor(Matrix2<T> const& m);

    template<typename T>
    static Matrix2<T> transpose(Matrix2<T> const& m);

    template<typename T>
    static T determinant(Matrix2<T> const& m);
};

template<typename T>
Matrix2<T> Matrix2Util::fromRowMajor(std::array<T, 4> const& arr)
{
    return Matrix2<T>(arr[0], arr[1], arr[2], arr[3]);
}

template<typename T>
Matrix2<T> Matrix2Util::fromColMajor(std::array<T, 4> const& arr)
{
    return Matrix2<T>(arr[0], arr[2], arr[1], arr[3]);
}

template<typename T>
inline Matrix2<T> Matrix2Util::fromRowVectors(
    Vector2<T> const& row0,
    Vector2<T> const& row1)
{
    return Matrix2<T>(
        row0.x(), row0.y(),
        row1.x(), row1.y());
}

template<typename T>
inline Matrix2<T> Matrix2Util::fromColVectors(
    Vector2<T> const& col0,
    Vector2<T> const& col1)
{
    return Matrix2<T>(
        col0.x(), col1.x(),
        col0.y(), col1.y());
}

template<typename T>
std::array<T, 4> Matrix2Util::toRowMajor(Matrix2<T> const& m)
{
    return std::array<T, 4>{{
        m(0, 0), m(0, 1),
        m(1, 0), m(1, 1)
    }};
}

template<typename T>
std::array<T, 4> Matrix2Util::toColMajor(Matrix2<T> const& m)
{
    return std::array<T, 4>{{
        m(0, 0), m(1, 0),
        m(0, 1), m(1, 1)
    }};
}

template<typename T>
inline Matrix2<T> Matrix2Util::transpose(Matrix2<T> const& m)
{
    return Matrix2<T>(
        m(0, 0), m(1, 0),
        m(0, 1), m(1, 1));
}
    
template<typename T>
inline T Matrix2Util::determinant(Matrix2<T> const& m)
{
    return (m(0, 0) * m(1, 1)) - (m(0, 1) * m(1, 0));
}

} // namespace

#endif // INCLUDED
