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

#include <agtm_point2d.h>
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
    static Rect<T> fromLeftRightBottomTop(T const& l, T const& r, T const& b, T const& t);

    static Rect<T> fromXYWidthHeight(T const& x, T const& y, T const& width, T const& height);

    Rect();
    
    Rect(Point2d<T> const& origin, Size2d<T> const& size);
    
    ~Rect();
    
    T const& x() const;
    
    Rect<T>& x(T const& x);
    
    T const& y() const;
    
    Rect<T>& y(T const& y);
    
    T const& width() const;
    
    Rect<T>& width(T const& width);
    
    T const& height() const;
    
    Rect<T>& height(T const& height);
    
    Point2d<T> const& origin() const;

    Rect<T>& origin(Point2d<T> const& origin);
    
    Size2d<T> const& size() const;
    
    Rect<T>& size(Size2d<T> const& size);
        
private:
    Point2d<T> m_origin;
    Size2d<T> m_size; 
};

template<typename T>
Rect<T> make_rect(Point2d<T> const& origin, Size2d<T> const& size);

template<typename T>
std::ostream& operator<<(std::ostream& os, Rect<T> const& rect);

template<typename T>
Rect<T> Rect<T>::fromLeftRightBottomTop(T const& l, T const& r, T const& b, T const& t)
{
    return Rect<T>(Point2d<T>(l, b), Size2d<float>(r - l, t - b));
}

template<typename T>
Rect<T> Rect<T>::fromXYWidthHeight(T const& x, T const& y, T const& width, T const& height)
{
    return Rect<T>(Point2d<float>(x, y), Size2d<float>(width, height));
}

template<typename T>
Rect<T>::Rect()
{}

template<typename T>
Rect<T>::Rect(Point2d<T> const& origin, Size2d<T> const& size)
: m_origin(origin),
  m_size(size)
{}

template<typename T>
Rect<T>::~Rect()
{}

template<typename T>
T const& Rect<T>::x() const
{
    return m_origin.x();
}

template<typename T>
Rect<T>& Rect<T>::x(T const& x)
{
    m_origin.x(x);
    return *this;
}

template<typename T>
T const& Rect<T>::y() const
{
    return m_origin.y();
}

template<typename T>
Rect<T>& Rect<T>::y(T const& y)
{
    m_origin.y(y);
    return *this;
}

template<typename T>
T const& Rect<T>::width() const
{
    return m_size.width();
}

template<typename T>
Rect<T>& Rect<T>::width(T const& width)
{
    m_size.width(width);
    return *this;
}

template<typename T>
T const& Rect<T>::height() const
{
    return m_size.height();
}

template<typename T>
Rect<T>& Rect<T>::height(T const& height)
{
    m_size.height(height);
    return &this;
}

template<typename T>
Point2d<T> const& Rect<T>::origin() const
{
    return m_origin;
}

template<typename T>
Rect<T>& Rect<T>::origin(Point2d<T> const& origin)
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
Rect<T> make_rect(Point2d<T> const& origin, Size2d<T> const& size)
{
    return Rect<T>(origin, size);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Rect<T> const& rect)
{
    os << "[" << rect.origin() << " " << rect.size() << "]";
    return os;
}

} // namespace

#endif // INCLUDED
