#ifndef INCLUDED_AEGIS_AGTM_VECTOR2UTIL_H
#define INCLUDED_AEGIS_AGTM_VECTOR2UTIL_H

#include <agtm_vector2.h>

namespace agtm {

/**
 * Provides a number of common methods performed on Vectors, including
 * calculating cross and dot products, Vector lengths and normalization.
 */
struct Vector2Util
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
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline T Vector2Util::magnitude(Vector2<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "magnitude only supports floating point types");
    return std::sqrt((vec.x() * vec.x()) + (vec.y() * vec.y()));
}

template<typename T>
inline Vector2<T> Vector2Util::normalize(Vector2<T> const& vec)
{
    static_assert(std::is_floating_point<T>::value, "normalize only supports floating point types");
    T len = Vector2Util::magnitude(vec);
    T x = vec.x() / len;
    T y = vec.y() / len;
    return Vector2<T>(x, y);
}

template<typename T>
inline T Vector2Util::dot(Vector2<T> const& vec1, Vector2<T> const& vec2)
{
    return (vec1.x() * vec2.x()) + (vec1.y() * vec2.y());
}

} // namespace

#endif // INCLUDED
