// agtm_rect.h
#ifndef INCLUDED_AEGIS_AGTM_RECT_H
#define INCLUDED_AEGIS_AGTM_RECT_H

// h1. Purpose
// Provide a 2d, axis-aligned, rectangular boundary.
//
// h1. Classes
// Rect
//
// h1. Description
// This component provides a representation of a 2-dimensional, axis-aligned,
// rectangular boundary, positioned at an origin point (x,y) and extending
// to a size of (width,height). The canonical representation of the origin
// is the lower-left point of the rectangle, although a user of this component
// may determine the origin to be a different corner of the rectangle with the
// width and height still valid. For example, a user may understand the origin
// to be the the upper left corner, as is standard for many windowing systems.
//
// *Note:*
// The specification of the rectangle using the left, right, bottom and top
// parameters assumes a lower-left origin.
//
// h2. Usage
// This section illustrates the intended use of this component.
//
// h3. Example 1: Constructing a Rect
// [code]
// Rect<int> rect(make_point(0, 0), make_size(640, 480));
//
// assert(rect.x() == 0);
// assert(rect.y() == 0);
// assert(rect.width() == 640);
// assert(rect.height() == 480);
// [code]

#include <agtm_vector2.h>
#include <agtm_size2d.h>
#include <ostream>

namespace agtm {

// @class
//   Rect
//
// @description
//
// Represents a 2 dimensional rectangle defined either
// by an origin
//
template<typename T>
class Rect
{
public:
    static Rect<T> fromLeftRightBottomTop(T l, T r, T b, T t);

    static Rect<T> fromXYWidthHeight(T x, T y, T width, T height);

    Rect();
    
    Rect(Vector2<T> const& origin, Size2d<T> const& size);
    
    ~Rect();
    
    T x() const;
    
    Rect<T>& x(T x);
    
    T y() const;
    
    Rect<T>& y(T y);
    
    T width() const;
    
    Rect<T>& width(T width);
    
    T height() const;
    
    Rect<T>& height(T height);
    
    Vector2<T> const& origin() const;

    Rect<T>& origin(Vector2<T> const& origin);
    
    Size2d<T> const& size() const;
    
    Rect<T>& size(Size2d<T> const& size);
        
private:
    Vector2<T> m_origin;
    Size2d<T> m_size; 
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Rect<T> const& rect);

template<typename T>
Rect<T> Rect<T>::fromLeftRightBottomTop(T l, T r, T b, T t)
{
    return Rect<T>(Vector2<T>(l, b), Size2d<T>(r - l, t - b));
}

template<typename T>
Rect<T> Rect<T>::fromXYWidthHeight(T x, T y, T width, T height)
{
    return Rect<T>(Vector2<T>(x, y), Size2d<T>(width, height));
}

template<typename T>
Rect<T>::Rect()
{
    static_assert(std::is_floating_point<T>::value, "Rect only supports floating point types");
}

template<typename T>
Rect<T>::Rect(Vector2<T> const& origin, Size2d<T> const& size)
: m_origin(origin),
  m_size(size)
{
    static_assert(std::is_floating_point<T>::value, "Rect only supports floating point types");
}

template<typename T>
Rect<T>::~Rect()
{}

template<typename T>
T Rect<T>::x() const
{
    return m_origin.x();
}

template<typename T>
Rect<T>& Rect<T>::x(T x)
{
    m_origin.x(x);
    return *this;
}

template<typename T>
T Rect<T>::y() const
{
    return m_origin.y();
}

template<typename T>
Rect<T>& Rect<T>::y(T y)
{
    m_origin.y(y);
    return *this;
}

template<typename T>
T Rect<T>::width() const
{
    return m_size.width();
}

template<typename T>
Rect<T>& Rect<T>::width(T width)
{
    m_size.width(width);
    return *this;
}

template<typename T>
T Rect<T>::height() const
{
    return m_size.height();
}

template<typename T>
Rect<T>& Rect<T>::height(T height)
{
    m_size.height(height);
    return &this;
}

template<typename T>
Vector2<T> const& Rect<T>::origin() const
{
    return m_origin;
}

template<typename T>
Rect<T>& Rect<T>::origin(Vector2<T> const& origin)
{
    m_origin = origin;
    return *this;
}

template<typename T>
Size2d<T> const& Rect<T>::size() const
{
    return m_size;
}

template<typename T>
Rect<T>& Rect<T>::size(Size2d<T> const& size)
{
    m_size = size;
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Rect<T> const& rect)
{
    os << "[" << rect.origin() << " " << rect.size() << "]";
    return os;
}

} // namespace

#endif // INCLUDED
