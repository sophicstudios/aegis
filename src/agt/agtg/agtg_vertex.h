#ifndef INCLUDED_AEGIS_AGTG_VERTEX_H
#define INCLUDED_AEGIS_AGTG_VERTEX_H

#include <agtm_vector2.h>
#include <agtm_vector3.h>
#include <agtg_colorrgba.h>

namespace aegis {
namespace agtg {

template<typename T>
class Vertex
{
public:
    Vertex(agtm::Vector3<T> const& coordinates);
    
    Vertex(
        agtm::Vector2<T> const& coordinates,
        agtg::ColorRGBA<T> const& color);

    Vertex(Vertex<T> const& rhs);
    
    ~Vertex();
    
    Vertex& operator=(Vertex<T> const& rhs);
    
    agtm::Vector3<T> coordinates() const;
    
private:
    agtm::Vector3<T> m_coordinates;
    //agtm::Vector3<T> m_normalVector;
    //agtm::Vector2<T> m_textureCoordinates;
    agtg::ColorRGBA<T> m_color;
    //bool m_hasNormalVector;
    //bool m_hasTextureCoordinates;
    bool m_hasColor;
};

} // namespace
} // namespace

#endif // INCLUDED
