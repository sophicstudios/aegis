#include <agtg_texture.h>
#include <agtg_gl.h>

namespace agtg {

Texture::Texture(std::shared_ptr<agtr::Image> image)
: m_width(image && image->size().width()),
  m_height(image && image->size().height())
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &((*image->data())[0]));
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureId);
}

GLuint Texture::id() const
{
    return m_textureId;
}

GLsizei Texture::width() const
{
    return m_width;
}

GLsizei Texture::height() const
{
    return m_height;
}

} // namespace
