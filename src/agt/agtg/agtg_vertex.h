#ifndef INCLUDED_AEGIS_AGTG_VERTEX_H
#define INCLUDED_AEGIS_AGTG_VERTEX_H

#include <agtm_vector2.h>
#include <agtm_vector3.h>
#include <agtg_colorrgba.h>

namespace agtg {

template<typename T>
class Vertex
{
public:
    Vertex(agtm::Vector3<T> const& position);
    
    Vertex(
        agtm::Vector3<T> const& position,
        agtg::ColorRGBA<T> const& color);

    Vertex(Vertex<T> const& rhs);
    
    ~Vertex();
    
    Vertex& operator=(Vertex<T> const& rhs);
    
    agtm::Vector3<T> const& coordinates() const;
    
private:
    agtm::Vector3<T> m_coordinates;
    //agtm::Vector3<T> m_normalVector;
    //agtm::Vector2<T> m_textureCoordinates;
    agtg::ColorRGBA<T> m_color;
    //bool m_hasNormalVector;
    //bool m_hasTextureCoordinates;
    bool m_hasColor;
};

template<typename T>
Vertex<T>::Vertex(agtm::Vector3<T> const& coordinates)
: m_coordinates(coordinates)
{
}

template<typename T>
Vertex<T>::Vertex(agtm::Vector3<T> const& coordinates,
                  agtg::ColorRGBA<T> const& color)
: m_coordinates(coordinates),
  m_color(color)
{
}

template<typename T>
Vertex<T>::Vertex(Vertex<T> const& rhs)
: m_coordinates(rhs.m_coordinates),
  m_color(rhs.m_color)

{
}

template<typename T>
Vertex<T>::~Vertex()
{
}

template<typename T>
Vertex<T>& Vertex<T>::operator=(Vertex<T> const& rhs)
{
    m_coordinates = rhs.m_coordinates;
    m_color = rhs.m_color;
    return *this;
}

template<typename T>
agtm::Vector3<T> const& Vertex<T>::coordinates() const
{
    return m_coordinates;
}

} // namespace

#endif // INCLUDED
