#ifndef INCLUDED_AEGIS_AGTM_VECTOR4_H
#define INCLUDED_AEGIS_AGTM_VECTOR4_H

#include <agtm_vector3.h>
#include <afts_comparisonutil.h>
#include <algorithm>
#include <array>
#include <ostream>
#include <vector>

namespace agtm {

/**
 * @class Vector4
 *
 * Represents a 4-dimensional Vector with components (x, y, z, w).
 *
 * Example code:
 *
 * @code
 * // Create a Vector with (x=0, y=0, z=0, w=1)
 * Vector4<float> v1;
 *
 * // Create a Vector with (x=3, y=4, z=5, w=1)
 * Vector4<float> v2(3, 4, 5, 1);
 *
 * // Add two Vectors
 * Vector4<float> v3 = v1 + v2;
 *
 * // Normalize a Vector so length == 1
 * Vector4<float> v4 = normalize(v2);
 * @endcode
 */
template<typename T>
class Vector4
{
public:
    /**
     * Constructs a Vector with components (0, 0, 0, 1). The
     * w component is set to 1 by default to indicate these are homogeneous
     * coordinates in 3D space.
     */
    Vector4();
    
    /**
     * Constructs a Vector with components (x, y, z, w).
     *
     * @param x The x component of the Vector.
     * @param y The y component of the Vector.
     * @param z The z component of the Vector.
     * @param w The w component of the Vector.
     */
    Vector4(T x, T y, T z, T w = static_cast<T>(1));

    /**
     * Constructs a Vector with components (v.x(), v.y(), v.z(), w)
     * 
     * @param v A Vector3 containing the x, y and z components
     * @param w The w component of the Vector.
     */
    explicit Vector4(Vector3<T> const& v, T w = static_cast<T>(1));

    /**
     * Constructs a Vector with components (arr[0], arr[1], arr[2], arr[3]).
     *
     * @param arr A std::array with four elements specifying the x, y, z and w components.
     */
    Vector4(std::array<T, 4> const& arr);

    /**
     * Copy constructor.
     *
     * @param vec The input Vector.
     */
    Vector4(Vector4<T> const& vec);

    /**
     * Destructor
     */
    ~Vector4();
    
    /**
     * Assignment operator.
     *
     * @param rhs The input Vector.
     * @return A reference to this.
     */
    Vector4<T>& operator=(Vector4<T> const& vec);

    /**
     * Assignment operator.
     * Assigns the input std::array to this, where the x, y, z and w components
     * are assigned from arr[0], arr[1], arr[2] and arr[3], respectively.
     *
     * @param arr A std::array with four elements specifying the x, y, z and w positions.
     * @return A reference to this.
     */
    Vector4<T>& operator=(std::array<T, 4> const& arr);

    /**
     * Addition assignment operator.
     * Performs a summation of this Vector with the input Vector. This Vector
     * then has components (this.x() + vec.x(), this.y() + vec.y(), this.z() + vec.z(), this.w() + vec.w()).
     *
     * @param vec The Vector to add to this.
     * @return A reference to this.
     */
    Vector4<T>& operator+=(Vector4<T> const& v);
    
    /**
     * Subtraction assignment operator.
     * Performs a subtraction of the input Vector from this vector. This Vector
     * then has components (this.x() - vec.x(), this.y() - vec.y(), this.z() - vec.z(), this.w() - vec.w()).
     *
     * @param vec The Vector to add to this.
     * @return A reference to this.
     *
     */
    Vector4<T>& operator-=(Vector4<T> const& v);
    
    /**
     * Multiplication assignment operator.
     * Multiplies the x, y, z and w components by a scalar. This Vector then
     * has components (this.x() * scalar, this.y() * scalar, this.z() * scalar, this.w() * scalar)
     *
     * @param scalar The scalar value to multiply with the x, y, z and w components.
     * @return A reference to this.
     */
    Vector4<T>& operator*=(T scalar);

    /**
     * Division assignment operator.
     * Divides the x, y, z and w components by a scalar. This Vector then has
     * components (this.x() / scalar, this.y() / scalar, this.z() / scalar, thie.w() / scalar)
     *
     * @param scalar The scalar value to divide with the x, y, z and w components of this.
     */
    Vector4<T>& operator/=(T scalar);
    
    /**
     * Gets the x component of the Vector.
     *
     * @return The x component.
     */
    T x() const;

    /**
     * Sets the x component of the Vector.
     *
     * @param value The value to assign to the x component
     * @return A reference to this.
     */
    Vector4<T>& x(T value);

    /**
     * Gets the y component of the Vector.
     *
     * @return The y component
     */
    T y() const;

    /**
     * Sets the y component of the Vector.
     *
     * @param value The value to assign to the y component.
     * @return A reference to this.
     */
    Vector4<T>& y(T value);

    /**
     * Gets the z component of the Vector.
     *
     * @return The z component
     */
    T z() const;

    /*
     * Sets the z component of the Vector.
     *
     * @param value The value to assign to the z component.
     * @return A reference to this.
     */
    Vector4<T>& z(T value);

    /**
     * Gets the w component of the Vector.
     */
    T w() const;

    /**
     * Sets the w component of the Vector.
     *
     * @param value The value to assign to the w component.
     * @return A reference to this.
     */
    Vector4<T>& w(T value);

    /**
     * Gets a const reference to a std::array representation of the x, y, z and w
     * components, where arr[0] is x, arr[1] is y, arr[2] is z, and arr[3] is w.
     *
     * @return A std::array containing the x, y, z and w components.
     */
    std::array<T, 4> const& arr() const;
    
private:
    std::array<T, 4> m_arr;
};

/**
 * Equality operator.
 * Returns true if the Vectors are equal, false otherwise.
 *
 * @param vec1 A Vector4.
 * @param vec2 A Vector4.
 * @return true if equal, or false if not equal.
 */
template<typename T>
bool operator==(Vector4<T> const& vec1, Vector4<T> const& vec2);

/**
 * Inequality operator.
 * Returns true if the Vectors are not equal, false otherwise.
 *
 * @param vec1 A Vector4.
 * @param vec2 A Vector4.
 * @return true if not equal, or false if equal.
 */
template<typename T>
bool operator!=(Vector4<T> const& vec1, Vector4<T> const& vec2);

/**
 * Unary negation operator.
 * Returns a Vector that contains the negated x, y, z and w of the input Vector.
 *
 * @param vec The Vector to negate.
 * @return A Vector4 which is the negated input Vector.
 */
template<typename T>
Vector4<T> operator-(Vector4<T> const& vec);

/**
 * Addition operator.
 * Performs a summation of two Vectors. The result Vector has components
 * (this.x() + vec.x(), this.y() + vec.y(), this.z() + vec.z(), this.w() + vec.w()).
 *
 * @param vec1 A Vector4.
 * @param vec2 A Vector4.
 * @return A Vector4 which is the sum of the two input Vectors.
 */
template<typename T>
Vector4<T> operator+(Vector4<T> const& vec1, Vector4<T> const& vec2);

/**
 * Addition operator.
 * Performs a subtraction of two Vectors. The result Vector has components
 * (this.x() - vec.x(), this.y() - vec.y(), this.z() - vec.z(), this.w() - vec.w()).
 *
 * @param vec1 A Vector4.
 * @param vec2 A Vector4.
 * @return A Vector4 which is the difference of the two input Vectors.
 */
template<typename T>
Vector4<T> operator-(Vector4<T> const& vec1, Vector4<T> const& vec2);

/**
 * Multiplication operator.
 * Multiplies the x, y, z and w components of a Vector by a scalar. The result Vector
 * has components (this.x() * scalar, this.y() * scalar, this.z() * scalar, this.w() * scalar)
 *
 * @param scalar The scalar value to multiply with the x, y, z and w components.
 * @return A reference to this.
 */
template<typename T>
Vector4<T> operator*(Vector4<T> const& vec, T const& scalar);

/**
 * Division operator.
 * Divides the x, y, z and w components of a Vector by a scalar. The result Vector
 * has components (this.x() / scalar, this.y() / scalar, this.z() / scalar, this.w() / scalar)
 *
 * @param scalar The scalar value to divide with the x, y, z and w components.
 * @return A reference to this.
 */
template<typename T>
Vector4<T> operator/(Vector4<T> const& vec, T const& scalar);

/**
 * Stream operator.
 * Prints the Vector to the ostream os.
 *
 * @param os The output stream.
 * @param vec The Vector4 to stream.
 * @return A reference to the output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& vec);

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////

template<typename T>
inline Vector4<T>::Vector4()
: m_arr{{T(), T(), T(), T(1)}}
{
    static_assert(std::is_floating_point<T>::value, "Vector4 only supports floating point types");
}

template<typename T>
inline Vector4<T>::Vector4(T x, T y, T z, T w)
: m_arr{{x, y, z, w}}
{
    static_assert(std::is_floating_point<T>::value, "Vector4 only supports floating point types");
}

template<typename T>
inline Vector4<T>::Vector4(Vector3<T> const& vec, T w)
: m_arr{vec.x(), vec.y(), vec.z(), w}
{
    static_assert(std::is_floating_point<T>::value, "Vector4 only supports floating point types");
}

template<typename T>
inline Vector4<T>::Vector4(std::array<T, 4> const& arr)
: m_arr(arr)
{
    static_assert(std::is_floating_point<T>::value, "Vector4 only supports floating point types");
}

template<typename T>
inline Vector4<T>::Vector4(Vector4<T> const& vec)
: m_arr(vec.m_arr)
{}

template<typename T>
Vector4<T>::~Vector4()
{}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(Vector4<T> const& vec)
{
    m_arr = vec.m_arr;

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(std::array<T, 4> const& arr)
{
    m_arr = arr;

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(Vector4<T> const& vec)
{
    m_arr[0] += vec.m_arr[0];
    m_arr[1] += vec.m_arr[1];
    m_arr[2] += vec.m_arr[2];
    m_arr[3] += vec.m_arr[3];

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(Vector4<T> const& vec)
{
    m_arr[0] -= vec.m_arr[0];
    m_arr[1] -= vec.m_arr[1];
    m_arr[2] -= vec.m_arr[2];
    m_arr[3] -= vec.m_arr[3];

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(T scalar)
{
    m_arr[0] *= scalar;
    m_arr[1] *= scalar;
    m_arr[2] *= scalar;
    m_arr[3] *= scalar;

    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(T scalar)
{
    m_arr[0] /= scalar;
    m_arr[1] /= scalar;
    m_arr[2] /= scalar;
    m_arr[3] /= scalar;

    return *this;
}

template<typename T>
inline T Vector4<T>::x() const
{
    return m_arr[0];
}

template<typename T>
inline Vector4<T>& Vector4<T>::x(T value)
{
    m_arr[0] = value;

    return *this;
}

template<typename T>
inline T Vector4<T>::y() const
{
    return m_arr[1];
}

template<typename T>
inline Vector4<T>& Vector4<T>::y(T value)
{
    m_arr[1] = value;

    return *this;
}

template<typename T>
inline T Vector4<T>::z() const
{
    return m_arr[2];
}

template<typename T>
inline Vector4<T>& Vector4<T>::z(T value)
{
    m_arr[2] = value;

    return *this;
}

template<typename T>
inline T Vector4<T>::w() const
{
    return m_arr[3];
}

template<typename T>
inline Vector4<T>& Vector4<T>::w(T value)
{
    m_arr[3] = value;

    return *this;
}

template<typename T>
inline std::array<T, 4> const& Vector4<T>::arr() const
{
    return m_arr;
}

template<typename T>
inline bool operator==(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        && afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        && afts::ComparisonUtil::equal(vec1.z(), vec2.z())
        && afts::ComparisonUtil::equal(vec1.w(), vec2.w());
}

template<typename T>
inline bool operator!=(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return !afts::ComparisonUtil::equal(vec1.x(), vec2.x())
        || !afts::ComparisonUtil::equal(vec1.y(), vec2.y())
        || !afts::ComparisonUtil::equal(vec1.z(), vec2.z())
        || !afts::ComparisonUtil::equal(vec1.w(), vec2.w());
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& vec)
{
    return Vector4<T>(
        -vec.x(),
        -vec.y(),
        -vec.z(),
        -vec.w());
}

template<typename T>
inline Vector4<T> operator+(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return Vector4<T>(
        vec1.x() + vec2.x(),
        vec1.y() + vec2.y(),
        vec1.z() + vec2.z(),
        vec1.w() + vec2.w());
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& vec1, Vector4<T> const& vec2)
{
    return Vector4<T>(
        vec1.x() - vec2.x(),
        vec1.y() - vec2.y(),
        vec1.z() - vec2.z(),
        vec1.w() - vec2.w());
}

template<typename T>
inline Vector4<T> operator*(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() * scalar,
        vec.y() * scalar,
        vec.z() * scalar,
        vec.w() * scalar);
}
template<typename T>
inline Vector4<T> operator/(Vector4<T> const& vec, T const& scalar)
{
    return Vector4<T>(
        vec.x() / scalar,
        vec.y() / scalar,
        vec.z() / scalar,
        vec.w() / scalar);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector4<T> const& vec)
{
    os << "[" << vec.x() << " " << vec.y() << " " << vec.z() << " " << vec.w() << "]";

    return os;
}

} // namespace

#endif // INCLUDED
