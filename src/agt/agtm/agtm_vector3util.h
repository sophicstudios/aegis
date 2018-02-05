#ifndef INCLUDED_AEGIS_AGTM_VECTOR3UTIL_H
#define INCLUDED_AEGIS_AGTM_VECTOR3UTIL_H

#include <agtm_vector3.h>

namespace agtm {

/**
 * Provides a number of common methods performed on Vectors, including
 * calculating cross and dot products, Vector lengths and normalization.
 */
struct Vector3Util
{
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
inline T Vector3Util::magnitude(Vector3<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "magnitude only supports floating point types");
    return std::sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()) + (vec.z() * vec.z()));
}

template<typename T>
inline Vector3<T> Vector3Util::normalize(Vector3<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "normalize only supports floating point types");
    T len = Vector3Util::magnitude(vec);
    return Vector3<T>(vec.x() / len, vec.y() / len, vec.z() / len);
}

template<typename T>
inline T Vector3Util::dot(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return (vec1.x() * vec2.x()) + (vec1.y() * vec2.y()) + (vec1.z() * vec2.z());
}

template<typename T>
inline Vector3<T> Vector3Util::cross(Vector3<T> const& vec1, Vector3<T> const& vec2)
{
    return Vector3<T>(
        (vec1.y() * vec2.z()) - (vec1.z() * vec2.y()),
        (vec1.z() * vec2.x()) - (vec1.x() * vec2.z()),
        (vec1.x() * vec2.y()) - (vec1.y() * vec2.x()));
}

} // namespace

#endif // INCLUDED
