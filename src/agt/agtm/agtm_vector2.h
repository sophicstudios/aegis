#ifndef INCLUDED_AEGIS_AGTM_VECTOR2_H
#define INCLUDED_AEGIS_AGTM_VECTOR2_H

#include <afts_comparisonutil.h>
#include <afts_assert.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <ostream>
#include <vector>

namespace agtm {

/**
 * @class Vector2
 *
 * Represents a 2-dimensional Vector with magnitude and direction (x, y).
 */
template<typename T>
class Vector2
{
public:
    /**
     * Constructs a Vector2 with magnitude and direction (0, 0).
     */
    Vector2();

    /**
     * Constructs a position Vector2 with magnitude and direction (x, y).
     *
     * @param x The x value.
     * @param y The y value.
     */
    Vector2(T const& x, T const& y);

    /**
     * Constructs a Vector2 with magnitude and direction (arr[0], arr[1]).
     *
     * @param arr std::array<T, 2> to be copied from.
     */
    Vector2(std::array<T, 2> const& arr);

    /**
     * Constructs a Vector2 with magnitude and direction (arr[0], arr[1]).
     * If the length of arr != 2, the results are undefined.
     *
     * @param vec std::vector<T> to be copied from.
     */
    Vector2(std::vector<T> const& vec);
    
    /**
     * Copy constructor.
     *
     * @param vec Vector2 to be copied from.
     */
    Vector2(Vector2<T> const& vec);

    /**
     * Destructor
     */
    ~Vector2();

    /**
     * Assignment operator. Assigns the supplied Vector2 to this.
     *
     * @param rhs Vector2 to be assigned from.
     * @return A reference to this.
     */
    Vector2<T>& operator=(Vector2<T> const& vec);

    /**
     * Assignment operator. Assigns the supplied std::array to this. The first and
     * second elements of the array are assigned to the x and y values of this.
     *
     * @param arr std::array<T, 2> to be copied from.
     * @return A reference to this.
     */
    Vector2<T>& operator=(std::array<T, 2> const& arr);

    /**
     * Assignment operator. Assigns the supplied std::vector to this. The first
     * and second elements of the vector are assigned to the x andy y values
     * of this. If the vector length is less than 2, an exception is thrown. If
     * the vector length is greater than 2, only the first two values are copied.
     *
     * @param vec std::vector<T> to be copied from.
     * @return A reference to this.
     */
    Vector2<T>& operator=(std::vector<T> const& vec);

    /**
     * Assigns x and y to this.x and this.y
     *
     * @param x The x value.
     * @param y The y value.
     * @return A reference to this.
     */
    Vector2<T>& assign(T const& x, T const& y);

    /**
     * Addition assignment operator. Piecewise addition of vec.x and vec.y to
     * this.x and this.y
     *
     * @param vec Vector2<T> to be added.
     * @return A reference to this.
     */
    Vector2<T>& operator+=(Vector2<T> const& vec);

    /**
     * Addition assignment operator. Adds a scalar to both x and y.
     *
     * @param scalar The value to be added.
     * @return A reference to this.
     */
    Vector2<T>& operator+=(T scalar);

    /**
     * Subtraction assignment operator. Piecewise subtraction of vec.x and
     * vec.y from this.x and this.y.
     *
     * @param vec Vector2<T> to be subtracted.
     * @return A reference to this.
     */
    Vector2<T>& operator-=(Vector2<T> const& vec);

    /**
     * Subtraction assignment operator. Subtracts a scalar from both x and y.
     *
     * @param scalar The value to be subtracted.
     * @return A reference to this.
     */
    Vector2<T>& operator-=(T scalar);

    /**
     * Multiplication assignment operator. Multiplies both x and y by a scalar.
     *
     * @param scalar The value to be multiplied
     * @return A reference to this.
     */
    Vector2<T>& operator*=(T scalar);

    /**
     * Division assignment operator. Divides both x and y by scalar.
     *
     * @param scalar The value to be divided by.
     * @return A reference to this.
     */
    Vector2<T>& operator/=(T scalar);

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
     * Gets a const reference to an array representation of the x and y
     * values, where arr[0] is x and arr[1] is y.
     *
     * @return The array
     */
    T const* const arr() const;

    /**
     * Returns the geometric length of the Vector2<T> which equates to the
     * formula: sqrt(x^2 + y^2)
     *
     * @return The geometric length of the Vector2<T>
     */
    double length() const;

    /**
     * Returns the squared value of the geometric length of the Vector2<T>, 
     * which equates to the formula x^2 + y^2.
     *
     * @return The squared geometric length of the Vector2<T>.
     */
    double lengthSquared() const;

    /**
     * Normalizes the Vector2<T> to a unit vector (i.e. length() == 1).
     */
    void normalize();
        
private:
    union {
        T m_arr[2];
        struct {
            T m_x;
            T m_y;
        };
    };
};

/**
 * Equality operator. Returns true if the Vectors are equal, false otherwise.
 *
 * @param vec1 Vector2 on the left side of the equation.
 * @param vec2 Vector2 on the right side of the equation.
 * @return true if equal, or false if not equal
 */
template<typename T>
bool operator==(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Inequality operator. Returns true if the Vectors are not equal, false otherwise.
 *
 * @param vec1 Vector2 on the left side of the equation.
 * @param vec2 Vector2 on the right side of the euqation.
 * @return true if not equal, or false if equal
 */
template<typename T>
bool operator!=(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Unary negation operator. Returns a Vector2 that contains the negated
 * x and y of the original Vector2.
 *
 * @param vec The Vector2 to negate.
 * @return A Vector2.
 */
template<typename T>
Vector2<T> operator-(Vector2<T> const& vec);

/**
 * Addition operator. Piecewise addition of vec1 with vec2.
 *
 * @param vec1 A Vector2
 * @param vec2 A Vector2
 * @return A Vector2
 */
template<typename T>
Vector2<T> operator+(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Addition operator. Piecewise addition of vec with scalar.
 *
 * @param vec A Vector2
 * @param scalar Scalar value
 * @return A Vector2
 */
template<typename T>
Vector2<T> operator+(Vector2<T> const& vec, T const& scalar);

/**
 * Subtraction operator. Piecewise subtraction of vec2 from vec1.
 */
template<typename T>
Vector2<T> operator-(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Subtraction operator. Piecewise subtaction of scalar from vec.
 */
template<typename T>
Vector2<T> operator-(Vector2<T>const& vec, T const& scalar);

/**
 * Multiplication operator. Scales the x and y components of vec by scalar.
 */
template<typename T>
Vector2<T> operator*(Vector2<T> const& vec, T const& scalar);

/**
 * Division operator. Inverse scales the x and y components of vec by scalar.
 */
template<typename T>
Vector2<T> operator/(Vector2<T> const& vec, T const& scalar);

/**
 * Stream operator. Prints the Vector2 vec to the ostream os.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>::Vector2()
: m_x(T()),
  m_y(T())
{}

template<typename T>
inline Vector2<T>::Vector2(T const& x, T const& y)
: m_x(x),
  m_y(y)
{}

template<typename T>
inline Vector2<T>::Vector2(std::array<T, 2> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);
};

template<typename T>
inline Vector2<T>::Vector2(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 2);
    std::copy(vec.begin(), vec.end(), m_arr);
}

template<typename T>
inline Vector2<T>::Vector2(Vector2<T> const& vec)
: m_x(vec.m_x),
  m_y(vec.m_y)
{}

template<typename T>
Vector2<T>::~Vector2()
{}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(Vector2<T> const& vec)
{
    m_x = vec.m_x;
    m_y = vec.m_y;
    
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(std::array<T, 2> const& arr)
{
    std::copy(arr.begin(), arr.end(), m_arr);

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(std::vector<T> const& vec)
{
    AFTS_ASSERT_DEBUG(vec.size() == 2);
    std::copy(vec.begin(), vec.end(), m_arr);

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::assign(T const& x, T const& y)
{
    m_x = x;
    m_y = y;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(Vector2<T> const& vec)
{
    m_x += vec.m_x;
    m_y += vec.m_y;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(T scalar)
{
    m_x += scalar;
    m_y += scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& vec)
{
    m_x -= vec.m_x;
    m_y -= vec.m_y;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(T scalar)
{
    m_x -= scalar;
    m_y -= scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    
    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    
    return *this;
}

template<typename T>
inline T const& Vector2<T>::x() const
{
    return m_x;
}
    
template<typename T>
inline T const& Vector2<T>::y() const
{
    return m_y;
}

template<typename T>
inline T const* const Vector2<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline double Vector2<T>::length() const
{
    return std::sqrt((m_x * m_x) + (m_y * m_y));
}

template<typename T>
inline double Vector2<T>::lengthSquared() const
{
    return (m_x * m_x) + (m_y * m_y);
}

template<typename T>
inline void Vector2<T>::normalize()
{
    T len = length();
    
    m_x /= len;
    m_y /= len;
}

template<typename T>
inline bool operator==(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        && afts::ComparisonUtil::equal(vec1.y(), vec2.y());
}

template<typename T>
inline bool operator!=(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return !afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        || !afts::ComparisonUtil::equal(vec1.y(), vec2.y());
}

template<typename T>
inline Vector2<T> operator-(Vector2<T> const& vec)
{
    return Vector2<T>(-vec.x(), -vec.y());
}

template<typename T>
inline Vector2<T> operator+(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return Vector2<T>(
        vec1.x() + vec2.x(),
        vec1.y() + vec2.y());
}

template<typename T>
inline Vector2<T> operator+(Vector2<T> const& vec, T const& scalar)
{
    return Vector2<T>(
        vec.x() + scalar,
        vec.y() + scalar);
}

template<typename T>
inline Vector2<T> operator-(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return Vector2<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y());
}

template<typename T>
inline Vector2<T> operator-(Vector2<T>const& vec, T const& scalar)
{
    return Vector2<T>(
        vec.x() - scalar,
        vec.y() - scalar);
}

template<typename T>
inline Vector2<T> operator*(Vector2<T> const& vec, T const& scalar)
{
    return Vector2<T>(
        vec.x() * scalar,
        vec.y() * scalar);
}

template<typename T>
inline Vector2<T> operator/(Vector2<T> const& vec, T const& scalar)
{
    return Vector2<T>(
        vec.x() / scalar,
        vec.y() / scalar);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& vec)
{
    os << "[" << vec.x() << " " << vec.y() << "]";

    return os;
}

} // namespace

#endif // INCLUDED
