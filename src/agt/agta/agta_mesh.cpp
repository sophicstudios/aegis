#include <agta_mesh.h>
#include <aftl_logger.h>

namespace agta {

namespace {

char const* const translateGLenum(GLenum value)
{
    switch (value) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_ENUM: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_FRAMEBUFFER_UNDEFINED: return "GL_FRAMEBUFFER_UNDEFINED";
    default: return "Unhandled GLenum";
    }
}

void checkError(char const* const context)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::stringstream s;
        s << "glError [" << context << "]: " << translateGLenum(error) << " (" << error << ")";

        if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
            GLenum stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            s << " framebuffer status: " << translateGLenum(stat) << " (" << stat << ")";
        }

        AFTL_LOG_ERROR << s.str() << AFTL_LOG_END;
    }
}

} // namespace

Mesh::Mesh()
: m_vertexArray(0),
  m_vertexArrayInitialized(false),
  m_coordBuffer(0),
  m_coordDirty(false),
  m_normalBuffer(0),
  m_normalDirty(false),
  m_texCoordBuffer(0),
  m_texCoordDirty(false),
  m_indexBuffer(0),
  m_indexDirty(false),
  m_texOffsetBuffer(0),
  m_texOffsetDirty(false),
  m_coordCount(0),
  m_indexCount(0),
  m_instanceCount(0)
{
    memset(m_modelMatrixBuffer, 0, sizeof(GLuint) * 4);
}

Mesh::~Mesh()
{
}

void Mesh::coords(CoordList const& coords)
{
    checkError("before coords");
    m_coordDirty = true;
    m_coordCount = coords.size();

    if (m_coordBuffer) {
        glDeleteBuffers(1, &m_coordBuffer);
        m_coordBuffer = 0;
    }

    if (coords.empty()) {
        return;
    }

    if (!m_coordBuffer) {
        glGenBuffers(1, &m_coordBuffer);
    }

    std::vector<float> arr;
    arr.reserve(3 * coords.size());

    CoordList::const_iterator it, end = coords.end();
    for (it = coords.begin(); it != end; ++it) {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_coordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::normals(NormalList const& normals)
{
    m_normalDirty = true;

    if (m_normalBuffer) {
        glDeleteBuffers(1, &m_normalBuffer);
        m_normalBuffer = 0;
    }

    if (normals.empty()) {
        return;
    }

    if (!m_normalBuffer) {
        glGenBuffers(1, &m_normalBuffer);
    }

    std::vector<float> arr;
    arr.reserve(3 * normals.size());

    NormalList::const_iterator it, end = normals.end();
    for (it = normals.begin(); it != end; ++it) {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::texCoords(TexCoordList const& texCoords)
{
    checkError("before textCoords");
    m_texCoordDirty = true;

    if (m_texCoordBuffer) {
        glDeleteBuffers(1, &m_texCoordBuffer);
        m_texCoordBuffer = 0;
    }

    if (texCoords.empty()) {
        return;
    }

    if (!m_texCoordBuffer) {
        glGenBuffers(1, &m_texCoordBuffer);
    }

    std::vector<float> arr;
    arr.reserve(2 * texCoords.size());

    TexCoordList::const_iterator it, end = texCoords.end();
    for (it = texCoords.begin(); it != end; ++it) {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::indices(IndexList const& indices)
{
    m_indexDirty = true;
    m_indexCount = indices.size();

    if (m_indexBuffer) {
        glDeleteBuffers(1, &m_indexBuffer);
        m_indexBuffer = 0;
    }

    if (indices.empty()) {
        return;
    }

    if (!m_indexBuffer) {
        glGenBuffers(1, &m_indexBuffer);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::texOffsets(TexOffsetList const& texOffsets)
{
    checkError("before texOffsets");
    m_texOffsetDirty = true;

    if (texOffsets.empty()) {
        glDeleteBuffers(1, &m_texOffsetBuffer);
        m_texOffsetBuffer = 0;
    }

    if (!m_texOffsetBuffer) {
        glGenBuffers(1, &m_texOffsetBuffer);
    }

    std::vector<float> arr;
    arr.reserve(2 * texOffsets.size());

    TexOffsetList::const_iterator it, end = texOffsets.end();
    for (it = texOffsets.begin(); it != end; ++it) {
        std::copy(it->arr().begin(), it->arr().end(), std::back_inserter(arr));
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_texOffsetBuffer);
    checkError("glBindBuffer texOffsets");
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
    checkError("glBufferData texOffsets");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkError("glBindBuffer(0) texOffsets");
}

void Mesh::modelMatrices(ModelMatrixList const& matrices)
{
    checkError("before modelMatrices");
    m_modelMatrixDirty = true;
    m_instanceCount = matrices.size();

    if (m_modelMatrixBuffer[0]) {
        glDeleteBuffers(4, m_modelMatrixBuffer);
        memset(m_modelMatrixBuffer, 0, sizeof(GLuint) * 4);
    }

    if (matrices.empty()) {
        return;
    }

    if (!m_modelMatrixBuffer[0]) {
        glGenBuffers(4, m_modelMatrixBuffer);
    }

    for (size_t i = 0; i < 4; ++i) {
        std::vector<float> arr;
        arr.reserve(4 * matrices.size());

        ModelMatrixList::const_iterator it, end = matrices.end();
        for (it = matrices.begin(); it != end; ++it) {
            agtm::Vector4<float> col = it->col(i);
            std::copy(col.arr().begin(), col.arr().end(), std::back_inserter(arr));
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_modelMatrixBuffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arr.size(), arr.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Mesh::bind(agtg::ShaderProgram& shaderProgram)
{
    checkError("before glGenVertexArrays");
    if (!m_vertexArrayInitialized) {
        glGenVertexArrays(1, &m_vertexArray);
        checkError("glGenVertexArrays");
        m_vertexArrayInitialized = true;
    }

    glBindVertexArray(m_vertexArray);
    checkError("glBindVertexArray");

    if (m_coordDirty && m_coordBuffer) {
        m_coordDirty = false;
        GLint coordIndex = shaderProgram.getAttributeLocation("coord");
        glEnableVertexAttribArray(coordIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_coordBuffer);
        glVertexAttribPointer(coordIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (m_normalDirty && m_normalBuffer) {
        m_normalDirty = false;
        GLint normalIndex = shaderProgram.getAttributeLocation("normal");
        glEnableVertexAttribArray(normalIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
        glVertexAttribPointer(normalIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (m_texCoordDirty && m_texCoordBuffer) {
        m_texCoordDirty = false;
        GLint texCoordIndex = shaderProgram.getAttributeLocation("texCoord");
        glEnableVertexAttribArray(texCoordIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
        glVertexAttribPointer(texCoordIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (m_indexDirty && m_indexBuffer) {
        m_indexDirty = false;
        GLint indexIndex = shaderProgram.getAttributeLocation("index");
        glEnableVertexAttribArray(indexIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_indexBuffer);
        glVertexAttribPointer(indexIndex, 1, GL_INT, GL_FALSE, 0, 0);
    }

    if (m_texOffsetDirty && m_texOffsetBuffer) {
        m_texOffsetDirty = false;
        GLint texOffsetIndex = shaderProgram.getAttributeLocation("texOffset");
        glEnableVertexAttribArray(texOffsetIndex);
        glBindBuffer(GL_ARRAY_BUFFER, m_texOffsetBuffer);
        glVertexAttribPointer(texOffsetIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribDivisor(texOffsetIndex, 1);
    }

    if (m_modelMatrixDirty && m_modelMatrixBuffer[0]) {
        m_modelMatrixDirty = false;
        GLint modelMatrixIndex = shaderProgram.getAttributeLocation("modelMatrix");
        for (GLint i = 0; i < 4; ++i) {
            glEnableVertexAttribArray(modelMatrixIndex + i);
            glBindBuffer(GL_ARRAY_BUFFER, m_modelMatrixBuffer[i]);
            glVertexAttribPointer(modelMatrixIndex + i, 4, GL_FLOAT, GL_FALSE, 0, 0);
            glVertexAttribDivisor(modelMatrixIndex + i, 1);
        }
    }

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    checkError("after mesh bind");
}

void Mesh::draw()
{
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_coordCount);
    checkError("glDrawArrays");
}

void Mesh::drawInstanced()
{
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m_coordCount, m_instanceCount);
    checkError("glDrawArraysInstanced");
}

void Mesh::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


} // namespace
