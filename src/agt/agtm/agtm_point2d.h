#ifndef INCLUDED_AEGIS_AGTM_POINT2D_H
#define INCLUDED_AEGIS_AGTM_POINT2D_H

#include <afts_comparisonutil.h>
#include <ostream>

namespace aegis {
namespace agtm {

template<typename T>
class Point2d
{
public:
    Point2d();
      // Constructs a Point2d with coordinates (0,0)
    
    Point2d(T const& x, T const& y);
      // Constructs a Point2d with coordinates (x,y)
    
    Point2d(T const arr[2]);
      // Constructs a Point2d with coordinates(arr[0],arr[1])

    Point2d(Point2d<T> const& original);
      // Copy constructor
        
    ~Point2d();
      // Destructor
    
    Point2d<T>& operator=(Point2d const& original);
      // Assignment Operator
      
    template<typename U>
    Point2d<T>& operator+=(U const& value);
      // Adds the specified value to the x and y coordinates of this
      // Point2d, such that (x,y) <= (x + value,y + value)
    
    template<typename U>
    Point2d<T>& operator-=(U const& value);
      // Subtracts the specified value from the x and y coordinates of this
      // Point2d, so that (x1, y1) = (x - value, y - value)
    
    template<typename U>
    Point2d<T>& operator*=(U const& value);
    
    template<typename U>
    Point2d<T>& operator/=(U const& value);
    
    Point2d<T>& operator+=(Point2d const& point);
    
    Point2d<T>& operator-=(Point2d const& point);
    
    T const& x() const;
        
    T const& y() const;
    
private:
    T m_x;
    T m_y;
};

template<typename T>
Point2d<T> make_point(T const& x, T const& y);

/**
 *
 */
template<typename T>
bool operator==(Point2d<T> const& lhs, Point2d<T> const& rhs);

/**
 *
 */
template<typename T>
bool operator!=(Point2d<T> const& lhs, Point2d<T> const& rhs);

/**
 *
 */
template<typename T, typename U>
Point2d<T> operator+(Point2d<T> const& point, U const& value);

/**
 *
 */
template<typename T, typename U>
Point2d<T> operator-(Point2d<T> const& point, U const& value);

/**
 *
 */
template<typename T, typename U>
Point2d<T> operator*(Point2d<T> const& point, U const& value);

/**
 *
 */
template<typename T, typename U>
Point2d<T> operator/(Point2d<T> const& point, U const& value);

/**
 *
 */
template<typename T>
Point2d<T> operator+(Point2d<T> const& lhs, Point2d<T> const& rhs);

/**
 *
 */
template<typename T>
Point2d<T> operator-(Point2d<T> const& lhs, Point2d<T> const& rhs);

template<typename T>
std::ostream& operator<<(std::ostream& os, Point2d<T> const& p);

template<typename T>
Point2d<T>::Point2d()
: m_x(T()), m_y(T())
{}

template<typename T>
Point2d<T>::Point2d(T const& x, T const& y)
: m_x(x), m_y(y)
{}

template<typename T>
Point2d<T>::Point2d(T const arr[2])
: m_x(arr[0]), m_y(arr[1])
{}

template<typename T>
Point2d<T>::Point2d(Point2d<T> const& p)
: m_x(p.m_x), m_y(p.m_y)
{}

template<typename T>
Point2d<T>::~Point2d()
{}

template<typename T>
Point2d<T>& Point2d<T>::operator=(Point2d<T> const& p)
{
    m_x = p.m_x;
    m_y = p.m_y;
}

template<typename T> template<typename U>
Point2d<T>& Point2d<T>::operator+=(U const& value)
{
    m_x += value;
    m_y += value;

    return *this;
}

template<typename T> template<typename U>
Point2d<T>& Point2d<T>::operator-=(U const& value)
{
    m_x -= value;
    m_y -= value;
    
    return *this;
}

template<typename T> template<typename U>
Point2d<T>& Point2d<T>::operator*=(U const& value)
{
    m_x *= value;
    m_y *= value;
    
    return *this;
}

template<typename T> template<typename U>
Point2d<T>& Point2d<T>::operator/=(U const& value)
{
    m_x /= value;
    m_y /= value;
    
    return *this;
}

template<typename T>
Point2d<T>& Point2d<T>::operator+=(Point2d<T> const& point)
{
    m_x += point.m_x;
    m_y += point.m_y;
    
    return *this;
}

template<typename T>
Point2d<T>& Point2d<T>::operator-=(Point2d<T> const& point)
{
    m_x -= point.m_x;
    m_y -= point.m_y;
    
    return *this;
}

template<typename T>
inline T const& Point2d<T>::x() const
{
    return m_x;
}

template<typename T>
inline T const& Point2d<T>::y() const
{
    return m_y;
}

template<typename T>
Point2d<T> make_point(T const& x, T const& y)
{
    return Point2d<T>(x, y);
}

template<typename T>
bool operator==(Point2d<T> const& lhs, Point2d<T> const& rhs)
{
    return afts::ComparisonUtil::equalULP(lhs.x(), rhs.x(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        && afts::ComparisonUtil::equalULP(lhs.y(), rhs.y(), afts::ComparisonUtil::DEFAULT_MAX_ULP);
}

template<typename T>
bool operator!=(Point2d<T> const& lhs, Point2d<T> const& rhs)
{
    return !afts::ComparisonUtil::equalULP(lhs.x(), rhs.x(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        || !afts::ComparisonUtil::equalULP(lhs.y(), rhs.y(), afts::ComparisonUtil::DEFAULT_MAX_ULP);
}

template<typename T, typename U>
Point2d<T> operator+(Point2d<T> const& point, U const& value)
{
    return Point2d<T>(
        point.x() + value,
        point.y() + value);
}

template<typename T, typename U>
Point2d<T> operator-(Point2d<T> const& point, U const& value)
{
    return Point2d<T>(
        point.x() - value,
        point.y() - value);
}

template<typename T, typename U>
Point2d<T> operator*(Point2d<T> const& point, U const& value)
{
    return Point2d<T>(
        point.x() * value,
        point.y() * value);
}

template<typename T, typename U>
Point2d<T> operator/(Point2d<T> const& point, U const& value)
{
    return Point2d<T>(
        point.x() / value,
        point.y() / value);
}

template<typename T>
Point2d<T> operator+(Point2d<T> const& lhs, Point2d<T> const& rhs)
{
    return Point2d<T>(
        lhs.x() + rhs.x(),
        lhs.y() + rhs.y());
}

template<typename T>
Point2d<T> operator-(Point2d<T> const& lhs, Point2d<T> const& rhs)
{
    return Point2d<T>(
        lhs.x() - rhs.x(),
        lhs.y() - rhs.y());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Point2d<T> const& p)
{
    os << "[ " << p.x() << " " << p.y() << " ]";
    return os;
}

} // namespace
} // namespace

#endif // INCLUDED
