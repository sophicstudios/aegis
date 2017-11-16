#ifndef INCLUDED_AEGIS_AGTM_VECTORUTIL_H
#define INCLUDED_AEGIS_AGTM_VECTORUTIL_H

#include <agtm_vector2.h>
#include <agtm_vector3.h>
#include <agtm_vector4.h>

namespace agtm {

/**
 * Provides a number of common methods performed on Vectors, including
 * calculating cross and dot products, Vector lengths and normalization.
 */
struct VectorUtil
{
    /**
     * Returns the geometric length of a Vector2, which is equal to sqrt(x^2 + y^2)
     *
     * @param vec The input Vector2.
     * @return The geometric length of the supplied Vector2.
     */
    template<typename T>
    static T magnitude(Vector2<T> const& vec);

    /**
     * Creates a new Vector2, which is the normalized version of the supplied
     * Vector2. This is calculated by dividing the x and y components of the
     * supplied Vector2 by the length of the Vector2.
     *
     * @param vec The input Vector2.
     * @return A normalized Vector2.
     */
    template<typename T>
    static Vector2<T> normalize(Vector2<T> const& vec);

    /**
     * Calculates the dot product of two Vector2s.
     *
     * @param vec1 A Vector2.
     * @param vec2 A Vector2.
     * @return The dot product of the two Vector2s.
     */
    template<typename T>
    static T dot(Vector2<T> const& vec1, Vector2<T> const& vec2);

    /**
     * Returns the geometric length of a Vector3, which equates to the
     * formula: sqrt(x^2 + y^2 + z^2)
     *
     * @param vec The input Vector3
     * @return The geometric length of the input Vector3
     */
    template<typename T>
    static T magnitude(Vector3<T> const& vec);

    /**
     * Creates a new Vector3, which is the normalized version of the input
     * Vector3. This is calculated by dividing the x, y and z components of the
     * input Vector3 by the length of the Vector3.
     *
     * @param vec The input Vector3
     * @return A normalized Vector3
     */
    template<typename T>
    static Vector3<T> normalize(Vector3<T> const& vec);

    /**
     * Calculates the dot product of two Vector3s.
     *
     * @param vec1 A Vector3.
     * @param vec2 A Vector3.
     * @return The dot product of the two Vector3s.
     */
    template<typename T>
    static T dot(Vector3<T> const& vec1, Vector3<T> const& vec2);

    /**
     * Calculates the cross product of two Vector3s.
     *
     * @param vec1 A Vector3.
     * @param vec2 A Vector3.
     * @return A Vector3 which is perpendicular to the two input Vector3s.
     */
    template<typename T>
    static Vector3<T> cross(Vector3<T> const& vec1, Vector3<T> const& vec2);
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline T VectorUtil::magnitude(Vector2<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "magnitude only supports floating point types");
    return std::sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()));
}

template<typename T>
inline Vector2<T> VectorUtil::normalize(Vector2<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "normalize only supports floating point types");
    T len = VectorUtil::magnitude(vec);
    T x = vec.x() / len;
    T y = vec.y() / len;
    return Vector2<T>(x, y);
}

template<typename T>
inline T VectorUtil::dot(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return (vec1.x() * vec2.x()) + (vec1.y() * vec2.y());
}

template<typename T>
inline T VectorUtil::magnitude(Vector3<T> const& vec)
{
    return std::sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()) + (vec.z() * vec.z()));
}

template<typename T>
inline Vector3<T> VectorUtil::normalize(Vector3<T> const& vec)
{
    T len = VectorUtil::magnitude(vec);
    return Vector3<T>(vec.x() / len, vec.y() / len, vec.z() / len);
}

template<typename T>
inline T VectorUtil::dot(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return (vec1.x() * vec2.x()) + (vec1.y() * vec2.y()) + (vec1.z() * vec2.z());
}

template<typename T>
inline Vector3<T> VectorUtil::cross(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return Vector3<T>(
        (vec1.y() * vec2.z()) - (vec1.z() * vec2.y()),
        (vec1.z() * vec2.x()) - (vec1.x() * vec2.z()),
        (vec1.x() * vec2.y()) - (vec1.y() * vec2.x()));
}

} // namespace

#endif // INCLUDED
