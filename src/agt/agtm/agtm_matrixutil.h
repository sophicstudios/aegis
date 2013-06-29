#ifndef INCLUDED_AEGIS_AGTM_MATRIXUTIL_H
#define INCLUDED_AEGIS_AGTM_MATRIXUTIL_H

#include <agtm_matrix2.h>
#include <agtm_matrix3.h>
#include <agtm_matrix4.h>
#include <agtm_vector2.h>
#include <agtm_vector3.h>
#include <agtm_vector4.h>

namespace aegis {
namespace agtm {

struct MatrixUtil
{
    template<typename T>
    static Matrix2<T> fromColVectors(
        Vector2<T> const& col0,
        Vector2<T> const& col1);
        
    template<typename T>
    static Matrix2<T> fromRowVectors(
        Vector2<T> const& row0,
        Vector2<T> const& row1);
        
    template<typename T>
    static Matrix3<T> fromColVectors(
        Vector3<T> const& col0,
        Vector3<T> const& col1,
        Vector3<T> const& col2);
    
    template<typename T>
    static Matrix3<T> fromRowVectors(
        Vector3<T> const& row0,
        Vector3<T> const& row1,
        Vector3<T> const& row2);

    template<typename T>
    static Matrix4<T> fromColVectors(
        Vector4<T> const& col0,
        Vector4<T> const& col1,
        Vector4<T> const& col2,
        Vector4<T> const& col3);
        
    template<typename T>
    static Matrix4<T> fromRowVectors(
        Vector4<T> const& row0,
        Vector4<T> const& row1,
        Vector4<T> const& row2,
        Vector4<T> const& row3);

    template<typename T>
    static Matrix2<T> transpose(Matrix2<T> const& m);

    template<typename T>
    static Matrix3<T> transpose(Matrix3<T> const& m);
    
    template<typename T>
    static Matrix4<T> transpose(Matrix4<T> const& m);
    
    template<typename T>
    static T determinant(Matrix2<T> const& m);
    
    template<typename T>
    static T determinant(Matrix3<T> const& m);
    
    template<typename T>
    static T determinant(Matrix4<T> const& m);
};

template<typename T>
inline Matrix2<T> MatrixUtil::fromColVectors(
    Vector2<T> const& col0,
    Vector2<T> const& col1)
{
    return Matrix2<T>(
        col0.x(), col1.x(),
        col0.y(), col1.y());
}

template<typename T>
inline Matrix2<T> MatrixUtil::fromRowVectors(
    Vector2<T> const& row0,
    Vector2<T> const& row1)
{
    return Matrix2<T>(
        row0.x(), row0.y(),
        row1.x(), row1.y());
}

template<typename T>
inline Matrix3<T> MatrixUtil::fromColVectors(
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
inline Matrix3<T> MatrixUtil::fromRowVectors(
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
inline Matrix4<T> MatrixUtil::fromColVectors(
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
inline Matrix4<T> MatrixUtil::fromRowVectors(
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
inline Matrix2<T> MatrixUtil::transpose(Matrix2<T> const& m)
{
    return Matrix2<T>(
        m(0, 0), m(1, 0),
        m(0, 1), m(1, 1));
}
    
template<typename T>
inline Matrix3<T> MatrixUtil::transpose(Matrix3<T> const& m)
{
    return Matrix3<T>(
        m(0, 0), m(1, 0), m(2, 0),
        m(0, 1), m(1, 1), m(2, 1),
        m(0, 2), m(1, 2), m(2, 2));
}

template<typename T>
inline Matrix4<T> MatrixUtil::transpose(Matrix4<T> const& m)
{
    return Matrix4<T>(
        m(0, 0), m(1, 0), m(2, 0), m(3, 0),
        m(0, 1), m(1, 1), m(2, 1), m(3, 1),
        m(0, 2), m(1, 2), m(2, 2), m(3, 2),
        m(0, 3), m(1, 3), m(2, 3), m(3, 3));
}

template<typename T>
inline T MatrixUtil::determinant(Matrix2<T> const& m)
{
    return (m(0, 0) * m(1, 1)) - (m(0, 1) * m(1, 0));
}

template<typename T>
inline T MatrixUtil::determinant(Matrix3<T> const& m)
{
    return (m(0, 0) * ((m(1, 1) * m(2, 2)) - (m(1, 2) * m(2, 1))))
         - (m(0, 1) * ((m(1, 0) * m(2, 2)) - (m(1, 2) * m(2, 0))))
         + (m(0, 2) * ((m(1, 0) * m(2, 1)) - (m(1, 1) * m(2, 0))));
}

template<typename T>
T MatrixUtil::determinant(Matrix4<T> const& m)
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
} // namespace

#endif // INCLUDED
