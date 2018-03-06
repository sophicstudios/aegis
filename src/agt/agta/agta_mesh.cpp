#include <agta_mesh.h>
#include <aftl_logger.h>

namespace agta {

Mesh::Mesh()
: m_coordBuffer(0),
  m_normalBuffer(0),
  m_texCoordBuffer(0),
  m_indexBuffer(0),
  m_dirty(true)
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

void Mesh::coords(CoordList const& coords)
{
    if (coords.empty())
    {
        if (m_coordBuffer)
        {
            glDeleteBuffers(1, &m_coordBuffer);
            m_coordBuffer = 0;
        }

        return;
    }

    if (!m_coordBuffer)
    {
        glGenBuffers(1, &m_coordBuffer);
    }

    std::vector<float> arr;
    arr.reserve(3 * coords.size());

    CoordList::const_iterator it, end = coords.end();
    for (it = coords.begin(); it != end; ++it)
    {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_coordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_coordCount = coords.size();
}

void Mesh::normals(NormalList const& normals)
{
    if (normals.empty())
    {
        if (m_normalBuffer)
        {
            glDeleteBuffers(1, &m_normalBuffer);
            m_normalBuffer = 0;
        }

        return;
    }

    if (!m_normalBuffer)
    {
        glGenBuffers(1, &m_normalBuffer);
    }

    std::vector<float> arr;
    arr.reserve(3 * normals.size());

    NormalList::const_iterator it, end = normals.end();
    for (it = normals.begin(); it != end; ++it)
    {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::texCoords(TexCoordList const& texCoords)
{
    if (texCoords.empty())
    {
        if (m_texCoordBuffer)
        {
            glDeleteBuffers(1, &m_texCoordBuffer);
            m_texCoordBuffer = 0;
        }

        return;
    }

    if (!m_texCoordBuffer)
    {
        glGenBuffers(1, &m_texCoordBuffer);
    }

    std::vector<float> arr;
    arr.reserve(2 * texCoords.size());

    TexCoordList::const_iterator it, end = texCoords.end();
    for (it = texCoords.begin(); it != end; ++it)
    {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::indices(IndexList const& indices)
{
    if (indices.empty())
    {
        if (m_indexBuffer)
        {
            glDeleteBuffers(1, &m_indexBuffer);
            m_indexBuffer = 0;
            m_dirty = true;
        }

        return;
    }

    if (!m_indexBuffer)
    {
        glGenBuffers(1, &m_indexBuffer);
        m_dirty = true;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_indexCount = indices.size();
}

void Mesh::bind(agtg::ShaderProgram& shaderProgram)
{
    glBindVertexArray(m_vertexArray);
    if (m_dirty)
    {
        if (m_coordBuffer)
        {
            GLint coordIndex = shaderProgram.getAttributeLocation("coord");
            glEnableVertexAttribArray(coordIndex);
            glBindBuffer(GL_ARRAY_BUFFER, m_coordBuffer);
            glVertexAttribPointer(coordIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (m_normalBuffer)
        {
            GLint normalIndex = shaderProgram.getAttributeLocation("normal");
            glEnableVertexAttribArray(normalIndex);
            glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
            glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (m_texCoordBuffer)
        {
            GLint texCoordIndex = shaderProgram.getAttributeLocation("texCoord");
            glEnableVertexAttribArray(texCoordIndex);
            glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
            glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (m_indexBuffer)
        {
            GLint indexIndex = shaderProgram.getAttributeLocation("index");
            glEnableVertexAttribArray(indexIndex);
            glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
            glVertexAttribPointer(indexIndex, 1, GL_INT, GL_FALSE, 0, 0);
        }

        m_dirty = false;
    }
}

void Mesh::draw()
{
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_coordCount);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        AFTL_LOG_ERROR << "glDrawArrays error: " << error << AFTL_LOG_END;
    }
}

void Mesh::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


} // namespace
