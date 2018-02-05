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
#include <iomanip>

namespace agtm {

/**
 * @class Vector3
 *
 * Represents a 3-dimensional Vector with magnitude and direction (x, y, z).
 *
 * Example code:
 *
 * @code
 * // Create a Vector with (x=0, y=0, z=0)
 * Vector3<float> v1;
 *
 * // Create a Vector with (x=3, y=4, z=5)
 * Vector3<float> v2(3, 4, 5);
 *
 * // Add two Vectors
 * Vector3<float> v3 = v1 + v2;
 *
 * // Normalize a Vector so length == 1
 * Vector3<float> v4 = normalize(v2);
 * @endcode
 */
template<typename T>
class Vector3
{
public:
    /**
     * Constructs a Vector with magnitude and direction (0, 0, 0).
     */
    Vector3();
    
    /**
     * Constructs a Vector with magnitude and direction (x, y, z).
     *
     * @param x The x component of the Vector.
     * @param y The y component of the Vector.
     * @param z The z component of the Vector.
     */
    Vector3(T x, T y, T z);
    
    /**
     * Constructs a Vector with magnitude and direction (vec.x(), vec.y(), z).
     *
     * @param vec A Vector containing the x and y components.
     * @param z The z position.
     */
    explicit Vector3(Vector2<T> const& vec, T z);
    
    /**
     * Constructs a Vector with magnitude and direction (arr[0], arr[1], arr[2]).
     *
     * @param arr A std::array with three elements specifying the x, y and z components.
     */
    Vector3(std::array<T, 3> const& arr);

    /**
     * Copy constructor.
     *
     * @param vec The input Vector.
     */
    Vector3(Vector3<T> const& vec);
    
    /**
     * Destructor.
     */
    ~Vector3();

    /**
     * Assignment operator.
     *
     * @param rhs The input Vector.
     * @return A reference to this.
     */
    Vector3<T>& operator=(Vector3<T> const& vec);

    /**
     * Assignment operator.
     * Assigns the input std::array to this, where the x, y and z components
     * are assigned from arr[0], arr[1] and arr[2], respectively.
     *
     * @param arr A std::array with three elements specifying the x, y and z components.
     * @return A reference to this.
     */
    Vector3<T>& operator=(std::array<T, 3> const& arr);

    /**
     * Addition assignment operator.
     * Performs a geometric addition of this Vector with the input Vector in 3D
     * space. This Vector then has magnitude and direction
     * (this.x() + vec.x(), this.y() + vec.y(), this.z() + vec.z()).
     *
     * @param vec The Vector to add to this.
     * @return A reference to this.
     */
    Vector3<T>& operator+=(Vector3<T> const& vec);
    
    /**
     * Subtraction assignment operator.
     * Performs a geometric subtraction of this Vector with the input Vector in
     * 3D space. This Vector then has magnitude and direction
     * (this.x() - vec.x(), this.y() - vec.y(), this.z() - vec.z()).
     *
     * @param vec The Vector to be subtracted from this.
     * @return A reference to this.
     */
    Vector3<T>& operator-=(Vector3<T> const& vec);
    
    /**
     * Multiplication assignment operator.
     * Performs a geometric scaling of this Vector. This Vector then has
     * magnitude and direction
     * (vec.x() * scalar, vec.y() * scalar, vec.z() * scalar).
     *
     * @param scalar The scalar value to multiply with the x, y and z components.
     * @return A reference to this.
     */
    Vector3<T>& operator*=(T scalar);
    
    /**
     * Division assignment operator.
     * Performs an inverse geometric scaling of this Vector. This Vector then
     * has magnitude and direction
     * (vec.x() / scalar, vec.y() / scalar, vec.z() / scalar).
     *
     * @param scalar The scalar value to divide with the x, y and z components.
     * @return A reference to this.
     */
    Vector3<T>& operator/=(T scalar);
    
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
    Vector3<T>& x(T value);

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
    Vector3<T>& y(T value);

    /**
     * Gets the z component of the Vector.
     *
     * @return The z component.
     */
    T z() const;

    /**
     * Sets the z component of the Vector.
     *
     * @param value The value to assign to the z component.
     * @return A reference to this.
     */
    Vector3<T>& z(T value);

    /**
     * Gets a const reference to an array representation of the x, y and z
     * components, where arr[0] is x, arr[1] is y, and arr[2] is z.
     *
     * @return A C-array containing the x, y and z components.
     */
    std::array<T, 3> const& arr() const;
    
private:
    std::array<T, 3> m_arr;
};

/**
 * Equality operator.
 * Returns true if the Vectors are equal, false otherwise.
 *
 * @param vec1 A Vector3.
 * @param vec2 A Vector3.
 * @return true if equal, or false if not equal.
 */
template<typename T>
bool operator==(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 * Inequality operator.
 * Returns true if the Vectors are not equal, false otherwise.
 *
 * @param vec1 A Vector3.
 * @param vec2 A Vector3.
 * @return true if not equal, or false if equal.
 */
template<typename T>
bool operator!=(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 * Unary negation operator.
 * Returns a Vector that contains the negated x, y and z of the input Vector.
 *
 * @param vec The Vector to negate.
 * @return A Vector which is the negated input Vector.
 */
template<typename T>
Vector3<T> operator-(Vector3<T> const& vec);

/**
 * Addition operator.
 * Performs a geometric addition of two Vectors in 3D
 * space. The result Vector has magnitude and direction
 * (vec1.x() + vec2.x(), vec1.y() + vec2.y(), vec1.z() + vec2.z()).
 *
 * @param vec1 A Vector3.
 * @param vec2 A Vector3.
 * @return A Vector3 which is the sum of the two input Vectors.
 */
template<typename T>
Vector3<T> operator+(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 * Subtraction operator.
 * Performs a geometric subtraction of two Vectors in 3D
 * space. The result Vector has magnitude and direction
 * (vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z()).
 *
 * @param vec1 A Vector3.
 * @param vec2 A Vector3.
 * @return A Vector3 with is the difference of the two input Vectors.
 */
template<typename T>
Vector3<T> operator-(Vector3<T> const& vec1, Vector3<T> const& vec2);

/**
 * Multiplication operator.
 * Performs a geometric scaling of a Vector where
 * the result Vector has magnitude and direction
 * (vec.x() * scalar, vec.y() * scalar, vec.z() * scalar).
 *
 * @param vec A Vector3.
 * @param scalar A scalar value to multiply with vec.
 * @return A Vector2 which has been scaled by scalar.
 */
template<typename T>
Vector3<T> operator*(Vector3<T> const& vec, T const& scalar);

/**
 * Division operator.
 * Performs a geometric inverse scaling of a Vector where
 * the result Vector has magnitude and direction
 * (vec.x() / scalar, vec.y() / scalar, vec.z() / scalar).
 *
 * @param vec A Vector3.
 * @param scalar A scalar value to divide with vec.
 * @return A Vector2 which has been inverse scaled by scalar.
 */
template<typename T>
Vector3<T> operator/(Vector3<T> const& vec, T const& scalar);

/**
 * Stream operator.
 * Prints the Vector to the ostream os.
 *
 * @param os The output stream.
 * @param vec The Vector3 to stream.
 * @return A reference to the output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

template<typename T>
inline Vector3<T>::Vector3()
: m_arr{{ T(), T(), T() }}
{
    static_assert(std::is_floating_point<T>::value, "Vector3 only supports floating point types");
}

template<typename T>
inline Vector3<T>::Vector3(T x, T y, T z)
: m_arr{{ x, y, z }}
{
    static_assert(std::is_floating_point<T>::value, "Vector3 only supports floating point types");
}

template<typename T>
inline Vector3<T>::Vector3(Vector2<T> const& vec, T z)
: m_arr{vec.x(), vec.y(), z}
{
    static_assert(std::is_floating_point<T>::value, "Vector3 only supports floating point types");
}

template<typename T>
inline Vector3<T>::Vector3(std::array<T, 3> const& arr)
: m_arr(arr)
{
    static_assert(std::is_floating_point<T>::value, "Vector3 only supports floating point types");
}

template<typename T>
inline Vector3<T>::Vector3(Vector3<T> const& vec)
: m_arr(vec.m_arr)
{}

template<typename T>
Vector3<T>::~Vector3()
{}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(Vector3<T> const& vec)
{
    m_arr = vec.m_arr;

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(std::array<T, 3> const& arr)
{
    m_arr = arr;

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(Vector3<T> const& vec)
{
    m_arr[0] += vec.m_arr[0];
    m_arr[1] += vec.m_arr[1];
    m_arr[2] += vec.m_arr[2];

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(Vector3<T> const& vec)
{
    m_arr[0] -= vec.m_arr[0];
    m_arr[1] -= vec.m_arr[1];
    m_arr[2] -= vec.m_arr[2];

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(T scalar)
{
    m_arr[0] *= scalar;
    m_arr[1] *= scalar;
    m_arr[2] *= scalar;

    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(T scalar)
{
    m_arr[0] /= scalar;
    m_arr[1] /= scalar;
    m_arr[2] /= scalar;

    return *this;
}

template<typename T>
inline T Vector3<T>::x() const
{
    return m_arr[0];
}

template<typename T>
inline Vector3<T>& Vector3<T>::x(T value)
{
    m_arr[0] = value;

    return *this;
}

template<typename T>
inline T Vector3<T>::y() const
{
    return m_arr[1];
}

template<typename T>
inline Vector3<T>& Vector3<T>::y(T value)
{
    m_arr[1] = value;

    return *this;
}

template<typename T>
inline T Vector3<T>::z() const
{
    return m_arr[2];
}

template<typename T>
inline Vector3<T>& Vector3<T>::z(T value)
{
    m_arr[2] = value;

    return *this;
}

template<typename T>
inline std::array<T, 3> const& Vector3<T>::arr() const
{
    return m_arr;
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
inline Vector3<T> operator-(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return Vector3<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y(),
        vec1.z() - vec2.z());
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
    std::streamsize w = os.width();

    os << std::setw(0) << "[" << std::setw(w) << vec.x() << " " << std::setw(w) << vec.y() << " " << std::setw(w) << vec.z() << "]";

    return os;
}

} // namespace

#endif // INCLUDED
