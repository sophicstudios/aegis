#ifndef INCLUDED_AEGIS_AGTA_MESH_H
#define INCLUDED_AEGIS_AGTA_MESH_H

#include <agtg_vertex.h>
#include <agtg_gl.h>
#include <agtg_shaderprogram.h>
#include <agtm_vector2.h>
#include <agtm_vector3.h>
#include <agtm_matrix4.h>
#include <afth_uuid.h>
#include <vector>

namespace agta {

class Mesh
{
public:
    typedef std::vector<agtm::Vector3<float> > CoordList;
    typedef std::vector<agtm::Vector3<float> > NormalList;
    typedef std::vector<agtm::Vector2<float> > TexCoordList;
    typedef std::vector<agtm::Vector2<float> > TexOffsetList;
    typedef std::vector<agtm::Matrix4<float> > ModelMatrixList;
    typedef std::vector<int> IndexList;

    Mesh();
    
    ~Mesh();

    void coords(CoordList const& coords);

    void normals(NormalList const& normals);

    void texCoords(TexCoordList const& texCoords);

    void indices(IndexList const& indices);

    void texOffsets(TexOffsetList const& texOffsets);

    void modelMatrices(ModelMatrixList const& matrices);

    void bind(agtg::ShaderProgram& shaderProgram);

    void draw();

    void drawInstanced();
    
    void unbind();

private:
    Mesh(Mesh const&);
    Mesh& operator=(Mesh const&);

    GLuint m_vertexArray;
    bool m_vertexArrayInitialized;
    GLuint m_coordBuffer;
    bool m_coordDirty;
    GLuint m_normalBuffer;
    bool m_normalDirty;
    GLuint m_texCoordBuffer;
    bool m_texCoordDirty;
    GLuint m_indexBuffer;
    bool m_indexDirty;
    GLuint m_texOffsetBuffer;
    bool m_texOffsetDirty;
    GLuint m_modelMatrixBuffer[4];
    bool m_modelMatrixDirty;
    GLsizei m_coordCount;
    GLsizei m_indexCount;
    GLsizei m_instanceCount;
};

} // namespace 

#endif // INCLUDED
