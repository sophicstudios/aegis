#ifndef INCLUDED_AEGIS_AGTG_MESH_H
#define INCLUDED_AEGIS_AGTG_MESH_H

#include <agtg_vertex.h>
#include <vector>

namespace aegis {
namespace agtg {

template<typename T>
class Mesh
{
public:
    Mesh(std::vector<Vertex<T> > const& vertices,
        std::vector<int> const& indices);
    
    ~Mesh();
    
    std::vector<Vertex<T> > const& vertices() const;
    
    std::vector<int> const& indices() const;
    
private:
    std::vector<Vertex<T> > m_vertices;
    std::vector<int> m_indices;
};

} // namespace 
} // namespace

#endif // INCLUDED
