#ifndef INCLUDED_AEGIS_AGTM_POINT3D_H
#define INCLUDED_AEGIS_AGTM_POINT3D_H

#include <afts_comparisonutil.h>
#include <iosfwd>

namespace agtm {

template<typename T>
class Point3d
{
public:
    /**
     * \brief Default constructor which creates a point with location (0, 0, 0).
     */
    Point3d();

    /**
     * \brief Constructor which creates a point with location (x, y, z).
     * \param x The x coordinate in 3d space.
     * \param y The y coordinate in 3d space.
     * \param z The z coordinate in 3d space.
     */
    Point3d(T const& x, T const& y, T const& z);

    /**
     * \brief Constructor which creates a point with location (arr[0], arr[1], arr[2]).
     * \param arr An array of 3 elements to indicate the x, y and z coordinates.
     */
    Point3d(T const arr[3]);

    /**
     * \brief Destructor.
     */
    ~Point3d();

    /**
     *
     */    
    Point3d<T>& operator=(Point3d<T> const& point);
    
    /**
     *
     */    
    template<typename U>
    Point3d<T>& operator+=(U const& value);
    
    /**
     *
     */    
    template<typename U>
    Point3d<T>& operator-=(U const& value);
    
    /**
     *
     */    
    template<typename U>
    Point3d<T>& operator*=(U const& value);
    
    /**
     *
     */    
    template<typename U>
    Point3d<T>& operator/=(U const& value);
    
    /**
     *
     */    
    Point3d<T>& operator+=(Point3d<T> const& point);
    
    /**
     *
     */    
    Point3d<T>& operator-=(Point3d<T> const& point);
    
    /**
     * \brief Gets a const reference to the x coordinate.
     * \return The x coordinate.
     */    
    T const& x() const;

    /**
     * \brief Gets a const reference to the y coordinate.
     * \return The y coordinate.
     */    
    T const& y() const;
    
    /**
     * \brief Gets a const reference to the z coordinate.
     * \return The z coordinate.
     */    
    T const& z() const;
            
    /**
     * \brief Set the point from the three components which sets the location
     * of the point to (x, y, z).
     * \param x The x coordinate.
     * \param y The y coordinate.
     * \param z The z coordinate.
     */
    void assign(T const& x, T const& y, T const& z);

    /**
     * \brief Sets the point to the coordinate indicated by the 3 elements of
     * the array, so that the point has the value (arr[0], arr[1], arr[2])
     * \param arr The 3 element array
     */
    void assign(T const arr[3]);

private:
    T m_x;
    T m_y;
    T m_z;
};

template<typename T>
bool operator==(Point3d<T> const& lhs, Point3d<T> const& rhs);

template<typename T>
bool operator!=(Point3d<T> const& lhs, Point3d<T> const& rhs);

template<typename T, typename U>
Point3d<T> operator+(Point3d<T> const& point, U const& value);

template<typename T, typename U>
Point3d<T> operator-(Point3d<T> const& point, U const& value);

template<typename T, typename U>
Point3d<T> operator*(Point3d<T> const& point, U const& value);

template<typename T, typename U>
Point3d<T> operator/(Point3d<T> const& point, U const& value);

template<typename T>
Point3d<T> operator+(Point3d<T> const& lhs, Point3d<T> const& rhs);

template<typename T>
Point3d<T> operator-(Point3d<T> const& lhs, Point3d<T> const& rhs);

template<typename T>
Point3d<T>::Point3d()
: m_x(T()), m_y(T()), m_z(T())
{}

template<typename T>
Point3d<T>::Point3d(const T &x, const T &y, const T &z)
: m_x(x), m_y(y), m_z(z)
{}

template<typename T>
Point3d<T>::Point3d(T const arr[3])
: m_x(arr[0]), m_y(arr[1]), m_z(arr[2])
{}

template<typename T>
Point3d<T>::~Point3d()
{}

template<typename T>
Point3d<T>& Point3d<T>::operator=(Point3d<T> const& point)
{
    m_x = point.m_x;
    m_y = point.m_y;
    m_z = point.m_z;
    
    return *this;
}

template<typename T> template<typename U>
Point3d<T>& Point3d<T>::operator+=(U const& value)
{
    m_x += value;
    m_y += value;
    m_z += value;
    
    return *this;
}

template<typename T> template<typename U>
Point3d<T>& Point3d<T>::operator-=(U const& value)
{
    m_x -= value;
    m_y -= value;
    m_z -= value;
    
    return *this;
}

template<typename T> template<typename U>
Point3d<T>& Point3d<T>::operator*=(U const& value)
{
    m_x *= value;
    m_y *= value;
    m_z *= value;
    
    return *this;
}

template<typename T> template<typename U>
Point3d<T>& Point3d<T>::operator/=(U const& value)
{
    m_x /= value;
    m_y /= value;
    m_z /= value;
    
    return *this;
}

template<typename T>
Point3d<T>& Point3d<T>::operator+=(Point3d<T> const& point)
{
    m_x += point.m_x;
    m_y += point.m_y;
    m_z += point.m_z;
    
    return *this;
}

template<typename T>
Point3d<T>& Point3d<T>::operator-=(Point3d<T> const& point)
{
    m_x -= point.m_x;
    m_y -= point.m_y;
    m_z -= point.m_z;
    
    return *this;
}

template<typename T>
inline T const& Point3d<T>::x() const
{
    return m_x;
}

template<typename T>
inline T const& Point3d<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const& Point3d<T>::z() const
{
    return m_z;
}

template<typename T>
inline void Point3d<T>::assign(T const& x, T const& y, T const& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

template<typename T>
inline void Point3d<T>::assign(T const arr[3])
{
    m_x = arr[0];
    m_y = arr[1];
    m_z = arr[2];
}

template<typename T>
bool operator==(Point3d<T> const& lhs, Point3d<T> const& rhs)
{
    return afts::ComparisonUtil::equalULP(lhs.x(), rhs.x(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        && afts::ComparisonUtil::equalULP(lhs.y(), rhs.y(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        && afts::ComparisonUtil::equalULP(lhs.z(), rhs.z(), afts::ComparisonUtil::DEFAULT_MAX_ULP);
}

template<typename T>
bool operator!=(Point3d<T> const& lhs, Point3d<T> const& rhs)
{
    return !afts::ComparisonUtil::equalULP(lhs.x(), rhs.x(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        || !afts::ComparisonUtil::equalULP(lhs.y(), rhs.y(), afts::ComparisonUtil::DEFAULT_MAX_ULP)
        || !afts::ComparisonUtil::equalULP(lhs.z(), rhs.z(), afts::ComparisonUtil::DEFAULT_MAX_ULP);
}

template<typename T, typename U>
Point3d<T> operator+(Point3d<T> const& point, U const& value)
{
    return Point3d<T>(
        point.x() + value,
        point.y() + value,
        point.z() + value);
}

template<typename T, typename U>
Point3d<T> operator-(Point3d<T> const& point, U const& value)
{
    return Point3d<T>(
        point.x() - value,
        point.y() - value,
        point.z() - value);
}

template<typename T, typename U>
Point3d<T> operator*(Point3d<T> const& point, U const& value)
{
    return Point3d<T>(
        point.x() * value,
        point.y() * value,
        point.z() * value);
}

template<typename T, typename U>
Point3d<T> operator/(Point3d<T> const& point, U const& value)
{
    return Point3d<T>(
        point.x() / value,
        point.y() / value,
        point.z() / value);
}

template<typename T>
Point3d<T> operator+(Point3d<T> const& lhs, Point3d<T> const& rhs)
{
    return Point3d<T>(
        lhs.x() + rhs.x(),
        lhs.y() + rhs.y(),
        lhs.z() + rhs.z());
}

template<typename T>
Point3d<T> operator-(Point3d<T> const& lhs, Point3d<T> const& rhs)
{
    return Point3d<T>(
        lhs.x() - rhs.x(),
        lhs.y() - rhs.y(),
        lhs.z() - rhs.z());
}

} // namespace

#endif // INCLUDED
