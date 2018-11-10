#ifndef INCLUDED_AEGIS_AGTA_MATERIAL_H
#define INCLUDED_AEGIS_AGTA_MATERIAL_H

#include <agtr_image.h>
#include <agtg_gl.h>
#include <agtm_size2d.h>
#include <memory>

namespace agta {

class Material
{
public:
    Material();

    ~Material();

    void texture(agtr::Image const& image);

    agtm::Size2d<float> size() const;

    void bind(size_t textureUnit);

    void unbind();

private:
    GLuint m_texture;
    GLenum m_currentTextureUnit;
    agtm::Size2d<float> m_size;
};

} // namespace

#endif // INCLUDED
