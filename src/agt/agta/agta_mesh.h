#ifndef INCLUDED_AEGIS_AGTA_MESH_H
#define INCLUDED_AEGIS_AGTA_MESH_H

#include <agtg_vertex.h>
#include <agtg_gl.h>
#include <agtg_shaderprogram.h>
#include <afth_uuid.h>
#include <vector>

namespace agta {

class Mesh
{
public:
    typedef std::vector<agtg::Vertex<float> > VertexList;
    typedef std::vector<int> IndexList;

    Mesh();
    
    ~Mesh();

    void vertices(VertexList const& vertices);

    VertexList const& vertices() const;

    void indices(IndexList const& indices);

    IndexList const& indices() const;

    void bind(agtg::ShaderProgram& shaderProgram);

private:
    VertexList m_vertices;
    IndexList m_indices;
    GLuint m_vertexBuffer;
    GLuint m_vertexArray;
};

} // namespace 

#endif // INCLUDED
