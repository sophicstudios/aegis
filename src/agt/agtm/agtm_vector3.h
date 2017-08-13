#ifndef INCLUDED_AEGIS_AGTM_VECTOR3_H
#define INCLUDED_AEGIS_AGTM_VECTOR3_H

#include <agtm_vector2.h>
#include <afts_comparisonutil.h>
#include <afts_assert.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <ostream>
#include <vector>

namespace agtm {

/**
 * @class Vector3
 *
 * Represents a 3-dimensional Vector with magnitude and direction (x, y, z).
 */
template<typename T>
class Vector3
{
public:
    /**
     * Constructor.
     */
    Vector3();
    
    /**
     * Constructor. Constructs a Vector3 with magnitude and direction (x, y, z).
     * 
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     */
    Vector3(T const& x, T const& y, T const& z);
    
    /**
     * Constructor. Constructs a Vector3 with magnitude and direction
     * (vec.x, vec.y, z).
     *
     * @param vec A Vector2.
     * @param z The z component
     */
    explicit Vector3(Vector2<T> const& vec, T const& z);
    
    /**
     * Constructor. Constructs a Vector3 from the supplied std::array arr.
     *
     * @param arr The std::array.
     */
    Vector3(std::array<T, 3> const& arr);

    /**
     * Constructor. Constructs a Vector3 from the supplied std::vector vec. The
     * vec must have size === 3, otherwise the results are undefined.
     *
     * @param vec The std::vector<T> of size 3.
     */
    Vector3(std::vector<T> const& vec);

    /**
     * Copy Constructor.
     *
     * @param vec A Vector3.
     */
    Vector3(Vector3<T> const& vec);
    
    /**
     * Destructor.
     */
    ~Vector3();

    /**
     * Assignment operator.
     */
    Vector3<T>& operator=(Vector3<T> const& vec);

    /**
     * Assignment operator.
     */
    Vector3<T>& operator=(std::array<T, 3> const& arr);

    /**
     * Assignment operator.
     */
    Vector3<T>& operator=(std::vector<T> const& vec);

    /**
     * Assigns the values of x, y and z to this.x, this.y and this.z.
     */
    void assign(T const& x, T const& y, T const& z);

    /**
     * Assigns vec.x and vec.y and z to this.x, this.y and this.z.
     */
    void assign(Vector2<T> const& vec, T const& z);

    /**
     * Addition assignment operator.
     */
    Vector3<T>& operator+=(Vector3<T> const& vec);
    
    /**
     * Addition assignment operator.
     */
    Vector3<T>& operator+=(T scalar);
    
    /**
     * Subtraction assignment operator.
     */
    Vector3<T>& operator-=(Vector3<T> const& vec);
    
    /**
     * Subtraction assignment operator.
     */
    Vector3<T>& operator-=(T scalar);
    
    /**
     * Multiplication assignment operator.
     */
    Vector3<T>& operator*=(T scalar);
    
    /**
     * Division assignment operator.
     *
     * @param scalar The value to be divided by.
     * @return A reference to this.
     */
    Vector3<T>& operator/=(T scalar);
    
    /**
     * Gets the value of x.
     *
     * @return The x value.
     */
    T const& x() const;
    
    /**
     * Gets the value of y.
     *
     * @return The y value.
     */
    T const& y() const;
    
    /**
     * Gets the value of z.
     *
     * @return The z value.
     */
    T const& z() const;
    
    /**
     * Gets a const reference to an array representation of the x, y and z
     * values, where arr[0] is x, arr[1] is y, and arr[2] is z.
     *
     * @return The array
     */
    T const* const arr() const;
    
    /**
     *
     */
    double length() const;
    
    /**
     *
     */
    double lengthSquared() const;
    
    /**
     *
     */
    void normalize();
    
private:
    union {
        T m_arr[3];
        struct {
            T m_x;
            T m_y;
            T m_z;
        };
    };
};

/**
 *
 */
template<typename T>
bool operator==(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 *
 */
template<typename T>
bool operator!=(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 *
 */
template<typename T>
Vector3<T> operator-(Vector3<T> const& vec);

/**
 *
 */
template<typename T>
Vector3<T> operator+(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 *
 */
template<typename T>
Vector3<T> operator+(Vector3<T> const& vec, T const& scalar);

/**
 *
 */
template<typename T>
Vector3<T> operator-(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 *
 */
template<typename T>
Vector3<T> operator-(Vector3<T> const& vec, T const& scalar);

/**
 *
 */
template<typename T>
Vector3<T> operator*(Vector3<T> const& vec, T const& scalar);

/**
 *
 */
template<typename T>
Vector3<T> operator/(Vector3<T> const& vec, T const& scalar);

/**
 *
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>::Vector3()
: m_x(T()),
  m_y(T()),
  m_z(T())
{}

template<typename T>
inline Vector3<T>::Vector3(T const& x, T const& y, T const& z)
: m_x(x),
  m_y(y),
  m_z(z)
{}

template<typename T>
inline Vector3<T>::Vector3(Vector2<T> const& vec, T const& z)
: m_x(vec.x()),
  m_y(vec.y()),
  m_z(z)
{}

template<typename T>
inline Vector3<T>::Vector3(std::array<T, 3> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);
}

template<typename T>
inline Vector3<T>::Vector3(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 3);
    std::copy(vec.begin(), vec.end(), m_arr);
}

template<typename T>
inline Vector3<T>::Vector3(Vector3<T> const& vec)
: m_x(vec.m_x),
  m_y(vec.m_y),
  m_z(vec.m_z)
{}

template<typename T>
Vector3<T>::~Vector3()
{}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(Vector3<T> const& vec)
{
    m_x = vec.m_x;
    m_y = vec.m_y;
    m_z = vec.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(std::array<T, 3> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 3);
    std::copy(vec.begin(), vec.end(), m_arr);

    return *this;
}

template<typename T>
inline void Vector3<T>::assign(T const& x, T const& y, T const& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

template<typename T>
inline void Vector3<T>::assign(Vector2<T> const& vec, T const& z)
{
    m_x = vec.x();
    m_y = vec.y();
    m_z = z;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(Vector3<T> const& vec)
{
    m_x += vec.m_x;
    m_y += vec.m_y;
    m_z += vec.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(T scalar)
{
    m_x += scalar;
    m_y += scalar;
    m_z += scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(Vector3<T> const& vec)
{
    m_x -= vec.m_x;
    m_y -= vec.m_y;
    m_z -= vec.m_z;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(T scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    m_z -= scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(T scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Vector3<T>::x() const
{
    return m_x;
}

template<typename T>
inline T const& Vector3<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const& Vector3<T>::z() const
{
    return m_z;
}

template<typename T>
inline T const* const Vector3<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline double Vector3<T>::length() const
{
    return std::sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

template<typename T>
inline double Vector3<T>::lengthSquared() const
{
    return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

template<typename T>
inline void Vector3<T>::normalize()
{
    T len = length();

    m_x /= len;
    m_y /= len;
    m_z /= len;
}

template<typename T>
inline bool operator==(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        && afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        && afts::ComparisonUtil::equal(vec1.z(), vec2.z());
}

template<typename T>
inline bool operator!=(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return !afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        || !afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        || !afts::ComparisonUtil::equal(vec1.z(), vec2.z());
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& vec)
{
    return Vector3<T>(-vec.x(), -vec.y(), -vec.z());
}

template<typename T>
inline Vector3<T> operator+(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return Vector3<T>(
        vec1.x() + vec2.x(),
        vec1.y() + vec2.y(),
        vec1.z() + vec2.z());
}

template<typename T>
inline Vector3<T> operator+(Vector3<T> const& vec, T const& scalar)
{
    return Vector3<T>(
        vec.x() + scalar,
        vec.y() + scalar,
        vec.z() + scalar);
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return Vector3<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y(),
        vec1.z() - vec2.z());
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& vec, T const& scalar)
{
    return Vector3<T>(
        vec.x() - scalar,
        vec.y() - scalar,
        vec.z() - scalar);
}

template<typename T>
inline Vector3<T> operator*(Vector3<T> const& vec, T const& scalar)
{
    return Vector3<T>(
        vec.x() * scalar,
        vec.y() * scalar,
        vec.z() * scalar);
}

template<typename T>
inline Vector3<T> operator/(Vector3<T> const& vec, T const& scalar)
{
    return Vector3<T>(
        vec.x() / scalar,
        vec.y() / scalar,
        vec.z() / scalar);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& vec)
{
    os << "[" << vec.x() << " " << vec.y() << " " << vec.z() << "]";
    return os;
}

} // namespace

#endif // INCLUDED
