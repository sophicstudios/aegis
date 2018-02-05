#include <agta_mesh.h>

namespace agta {

Mesh::Mesh()
: m_vertexBuffer(0)
{
    glGenVertexArrays(1, &m_vertexArray);

    //glGenBuffers(1, &m_vertexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), arr, GL_STATIC_DRAW);

    //glBindVertexArray(m_vertexArray);

    //GLint positionIndex = glGetAttribLocation(glProgramUniform1, "position");
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    //delete [] arr;
}

Mesh::~Mesh()
{
}

void Mesh::vertices(VertexList const& vertices)
{
    m_vertices = vertices;

    if (!m_vertexBuffer)
    {
        glGenBuffers(1, &m_vertexBuffer);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), arr, GL_STATIC_DRAW);
}

void Mesh::indices(IndexList const& indices)
{
    m_indices = indices;
}

void Mesh::bind(agtg::ShaderProgram& shaderProgram)
{
    glBindVertexArray(m_vertexArray);
    GLint positionIndex = shaderProgram.getAttributeLocation("position");
    glEnableVertexAttribArray(positionIndex);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

} // namespace
