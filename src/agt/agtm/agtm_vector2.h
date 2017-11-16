#ifndef INCLUDED_AEGIS_AGTM_VECTOR2_H
#define INCLUDED_AEGIS_AGTM_VECTOR2_H

#include <afts_comparisonutil.h>
#include <afts_assert.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <ostream>
#include <type_traits>
#include <vector>

namespace agtm {

/**
 * @class Vector2
 *
 * Represents a 2-dimensional Vector with magnitude and direction (x, y).
 *
 * Example code:
 *
 * @code
 * // Create a Vector with (x=0, y=0)
 * Vector2<float> v1;
 *
 * // Create a Vector with (x=3, y=4)
 * Vector2<float> v2(3, 4);
 *
 * // Add two Vectors
 * Vector2<float> v3 = v1 + v2;
 *
 * // Normalize a Vector so length == 1
 * Vector2<float> v4 = normalize(v2);
 * @endcode
 */
template<typename T>
class Vector2
{
public:
    /**
     * Constructs a Vector with magnitude and direction (0, 0).
     */
    Vector2();

    /**
     * Constructs a Vector with magnitude and direction (x, y).
     *
     * @param x The x component of the Vector.
     * @param y The y component of the Vector.
     */
    Vector2(T x, T y);

    /**
     * Constructs a Vector with magnitude and direction (arr[0], arr[1]).
     *
     * @param arr A std::array with two elements specifying the x and y components.
     */
    Vector2(std::array<T, 2> const& arr);

    /**
     * Copy constructor.
     *
     * @param vec The input Vector.
     */
    Vector2(Vector2<T> const& vec);

    /**
     * Destructor.
     */
    ~Vector2();

    /**
     * Assignment operator.
     *
     * @param rhs The input Vector.
     * @return A reference to this.
     */
    Vector2<T>& operator=(Vector2<T> const& vec);

    /**
     * Assignment operator.
     * Assigns the input std::array to this, where arr[0] and arr[1] are
     * assigned to the x and y components of this, respectively.
     *
     * @param arr A std::array with two elements specifying the x and y components.
     * @return A reference to this.
     */
    Vector2<T>& operator=(std::array<T, 2> const& arr);

    /**
     * Addition assignment operator.
     * Performs a geometric addition of this Vector with the input Vector in 2D
     * space. This Vector then has magnitude and direction
     * (this.x() + vec.x(), this.y() + vec.y()).
     *
     * @param vec The Vector2 to add to this.
     * @return A reference to this.
     */
    Vector2<T>& operator+=(Vector2<T> const& vec);

    /**
     * Subtraction assignment operator.
     * Performs a geometric subtraction of this Vector with another Vector in
     * 2D space. This Vector then has magnitude and direction
     * (this.x() - vec.x(), this.y() - vec.y()).
     *
     * @param vec The Vector to be subtracted from this.
     * @return A reference to this.
     */
    Vector2<T>& operator-=(Vector2<T> const& vec);

    /**
     * Multiplication assignment operator.
     * Performs a geometric scaling of this Vector. This Vector then has
     * magnitude and direction (this.x() * scalar, this.y() * scalar).
     *
     * @param scalar The value to multiply with the x and y components of this.
     * @return A reference to this.
     */
    Vector2<T>& operator*=(T scalar);

    /**
     * Division assignment operator.
     * Performs a geometric inverse scaling of this Vector. This Vector then
     * has magnitude and direction (this.x() / scalar, this.y() / scalar).
     *
     * @param scalar The value to divide with the x and y components of this.
     * @return A reference to this.
     */
    Vector2<T>& operator/=(T scalar);

    /**
     * Gets the x component of the Vector.
     *
     * @return The x component.
     */
    T x() const;

    /**
     * Sets the x component of the Vector.
     *
     * @param value The value to assign to the x component.
     * @return A reference to this.
     */
    Vector2<T>& x(T value);

    /**
     * Gets the y component of the Vector.
     *
     * @return The y component.
     */
    T y() const;

    /**
     * Sets the y component of the Vector.
     *
     * @param value The value to assign to the y component.
     * @return A reference to this.
     */
    Vector2<T>& y(T value);

    /**
     * Gets a const reference to an array representation of the x and y
     * components, where arr[0] is x and arr[1] is y.
     *
     * @return A C-array containing the x and y components.
     */
    std::array<T, 2> const& arr() const;

private:
    std::array<T, 2> m_arr;
};

/**
 * Equality operator.
 * Returns true if the Vectors are equal, false otherwise.
 *
 * @param vec1 A Vector2.
 * @param vec2 A Vector2.
 * @return true if equal, or false if not equal.
 */
template<typename T>
bool operator==(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Inequality operator.
 * Returns true if the Vectors are not equal, false otherwise.
 *
 * @param vec1 A Vector2.
 * @param vec2 A Vector2.
 * @return true if not equal, or false if equal.
 */
template<typename T>
bool operator!=(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Unary negation operator.
 * Returns a Vector2 that contains the negated
 * x and y of the input Vector2.
 *
 * @param vec The Vector2 to negate.
 * @return A Vector2 which is the negated input Vector2.
 */
template<typename T>
Vector2<T> operator-(Vector2<T> const& vec);

/**
 * Addition operator.
 * Performs a geometric addition of two Vector2s in 2D
 * space. The result Vector2 has magnitude and direction
 * (vec1.x() + vec2.x(), vec1.y() + vec2.y()).
 *
 * @param vec1 A Vector2.
 * @param vec2 A Vector2.
 * @return A Vector2 with is the sum of the two input Vector2s.
 */
template<typename T>
Vector2<T> operator+(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Subtraction operator.
 * Performs a geometric subtraction of two Vector2s in 2D
 * space. The result Vector2 has magnitude and direction
 * (vec1/x() - vec2.x(), vec1.y() - vec2.y()).
 *
 * @param vec1 A Vector2.
 * @param vec2 A Vector2.
 * @return A Vector2 which is the difference of the two input Vector2s.
 */
template<typename T>
Vector2<T> operator-(Vector2<T> const& vec1, Vector2<T> const& vec2);

/**
 * Multiplication operator.
 * Performs a geometric scaling of a Vector2 by a scalar value, where
 * the result Vector2 is equal to (vec.x() * scalar, vec.y() * scalar).
 *
 * @param vec A Vector2.
 * @param scalar A scalar value to multiply with vec.
 * @return A Vector2 which has been scaled by scalar.
 */
template<typename T>
Vector2<T> operator*(Vector2<T> const& vec, T const& scalar);

/**
 * Division operator.
 * Performs a geometric inverse scaling of a Vector2 by a scalar value, where
 * the result Vector2 is equal to (vec.x() / scalar, vec.y() / scalar).
 *
 * @param vec A Vector2.
 * @param scalar A scalar value to divide with vec.
 * @return A Vector2 which has been inverse scaled by scalar.
 */
template<typename T>
Vector2<T> operator/(Vector2<T> const& vec, T const& scalar);

/**
 * Stream operator.
 * Prints the Vector2 vec to the ostream os.
 *
 * @param os The output stream.
 * @param vec The Vector2 to stream.
 * @return A reference to the output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

template<typename T>
inline Vector2<T>::Vector2()
: m_arr{{ T(), T() }}
{
    static_assert(std::is_floating_point<T>::value, "Vector2 only supports floating point types");
}

template<typename T>
inline Vector2<T>::Vector2(T x, T y)
: m_arr{{ x, y }}
{
    static_assert(std::is_floating_point<T>::value, "Vector2 only supports floating point types");
}

template<typename T>
inline Vector2<T>::Vector2(std::array<T, 2> const& arr)
: m_arr(arr)
{
    static_assert(std::is_floating_point<T>::value, "Vector2 only supports floating point types");
};

template<typename T>
inline Vector2<T>::Vector2(Vector2<T> const& vec)
: m_arr(vec.m_arr)
{}

template<typename T>
Vector2<T>::~Vector2()
{}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(Vector2<T> const& vec)
{
    m_arr = vec.m_arr;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(std::array<T, 2> const& arr)
{
    m_arr = arr;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(Vector2<T> const& vec)
{
    m_arr[0] += vec.m_arr[0];
    m_arr[1] += vec.m_arr[1];

    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(Vector2<T> const& vec)
{
    m_arr[0] -= vec.m_arr[0];
    m_arr[1] -= vec.m_arr[1];

    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar)
{
    m_arr[0] *= scalar;
    m_arr[1] *= scalar;

    return *this;
}
    
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar)
{
    m_arr[0] /= scalar;
    m_arr[1] /= scalar;

    return *this;
}

template<typename T>
inline T Vector2<T>::x() const
{
    return m_arr[0];
}

template<typename T>
inline Vector2<T>& Vector2<T>::x(T value)
{
    m_arr[0] = value;

    return *this;
}

template<typename T>
inline T Vector2<T>::y() const
{
    return m_arr[1];
}

template<typename T>
inline Vector2<T>& Vector2<T>::y(T value)
{
    m_arr[1] = value;

    return *this;
}

template<typename T>
inline std::array<T, 2> const& Vector2<T>::arr() const
{
    return m_arr;
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
inline Vector2<T> operator-(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return Vector2<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y());
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
