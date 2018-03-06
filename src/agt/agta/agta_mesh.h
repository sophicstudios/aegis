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
    typedef std::vector<agtm::Vector3<float> > CoordList;
    typedef std::vector<agtm::Vector3<float> > NormalList;
    typedef std::vector<agtm::Vector2<float> > TexCoordList;
    typedef std::vector<int> IndexList;

    Mesh();
    
    ~Mesh();

    void coords(CoordList const& coords);

    void normals(NormalList const& normals);

    void texCoords(TexCoordList const& texCoords);

    void indices(IndexList const& indices);

    void bind(agtg::ShaderProgram& shaderProgram);

    void draw();
    
    void unbind();

private:
    Mesh(Mesh const&);
    Mesh& operator=(Mesh const&);

    GLuint m_coordBuffer;
    GLuint m_normalBuffer;
    GLuint m_texCoordBuffer;
    GLuint m_indexBuffer;
    GLuint m_vertexArray;
    bool m_dirty;
    GLsizei m_coordCount;
    GLsizei m_indexCount;
};

} // namespace 

#endif // INCLUDED
