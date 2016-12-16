#include <agta_mesh.h>

namespace agta {

Mesh::Mesh(VertexList const& vertices)
: m_id(afth::UUID::v4())
{
    size_t size = vertices.size() * 3;
    float* arr = new float[size];
    VertexList::const_iterator it = vertices.begin(), end = vertices.end();
    for (size_t i = 0; it != end; ++it, i += 3)
    {
        std::memcpy(arr + i, (*it).coordinates().arr(), 3);
    }

    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, arr, GL_STATIC_DRAW);

    glBindVertexArray(m_vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(VertexList const& vertices, IndexList const& indices)
: m_id(afth::UUID::v4())
{
}

Mesh::~Mesh()
{
}

afth::UUID const& Mesh::id() const
{
    return m_id;
}

void Mesh::bind()
{
    glBindVertexArray(m_vertexArray);
}

} // namespace
