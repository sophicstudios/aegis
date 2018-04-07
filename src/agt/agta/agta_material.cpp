#include <agta_material.h>
#include <agtg_gl.h>

namespace agta {

Material::Material()
: m_texture(0),
  m_currentTextureUnit(GL_TEXTURE0)
{
}

Material::~Material()
{}

void Material::texture(agtr::Image const& image)
{
    if (!m_texture)
    {
        glGenTextures(1, &m_texture);
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size().width(), image.size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &((*image.data())[0]));
}

void Material::bind(size_t textureUnit)
{
    m_currentTextureUnit = textureUnit;
    glActiveTexture(GL_TEXTURE0 + m_currentTextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Material::unbind()
{
    glActiveTexture(GL_TEXTURE0 + m_currentTextureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_currentTextureUnit = GL_TEXTURE0;
}

} // namespace
