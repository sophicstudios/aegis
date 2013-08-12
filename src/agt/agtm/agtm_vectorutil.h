#ifndef INCLUDED_AEGIS_AGTM_VECTORUTIL_H
#define INCLUDED_AEGIS_AGTM_VECTORUTIL_H

#include <agtm_vector3.h>

namespace agtm {

/**
 * TODO: Document
 */
struct VectorUtil
{
    /**
     * TODO: Document
     */
    template<typename T>
    static T dotProduct(
        agtm::Vector3<T> const& vec1,
        agtm::Vector3<T> const& vec2);

    /**
     * TODO: Document
     */
    template<typename T>
    static Vector3<T> crossProduct(
        agtm::Vector3<T> const& vec1,
        agtm::Vector3<T> const& vec2);
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template<typename T>
inline T VectorUtil::dotProduct(
    agtm::Vector3<T> const& vec1,
    agtm::Vector3<T> const& vec2)
{
    return (vec1.x() * vec2.x())
        + (vec1.y() * vec2.y())
        + (vec1.z() * vec2.z());
}

template<typename T>
inline agtm::Vector3<T> VectorUtil::crossProduct(
    agtm::Vector3<T> const& vec1,
    agtm::Vector3<T> const& vec2)
{
    return Vector3<T>(
        (vec1.y() * vec2.z()) - (vec1.z() * vec2.y()),
        (vec1.x() * vec2.z()) - (vec1.z() * vec2.x()),
        (vec1.x() * vec2.y()) - (vec1.y() * vec2.x()));
}

} // namespace

#endif // INCLUDED
