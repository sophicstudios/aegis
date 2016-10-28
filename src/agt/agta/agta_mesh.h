#ifndef INCLUDED_AEGIS_AGTA_MESH_H
#define INCLUDED_AEGIS_AGTA_MESH_H

#include <agtg_vertex.h>
#include <afth_uuid.h>
#include <vector>

namespace agta {

class Mesh
{
public:
    typedef std::vector<agtg::Vertex<float> > VertexList;
    typedef std::vector<int> IndexList;

    Mesh(VertexList const& vertices, IndexList const& indices);
    
    ~Mesh();

    afth::UUID const& id() const;
    
    VertexList const& vertices() const;
    
    IndexList const& indices() const;
    
private:
    afth::UUID m_id;
    VertexList m_vertices;
    IndexList m_indices;
};

} // namespace 

#endif // INCLUDED
