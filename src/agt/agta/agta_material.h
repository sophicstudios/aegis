#ifndef INCLUDED_AEGIS_AGTA_MATERIAL_H
#define INCLUDED_AEGIS_AGTA_MATERIAL_H

#include <agtr_image.h>
#include <agtg_gl.h>
#include <afth_uuid.h>
#include <memory>

namespace agta {

class Material
{
public:
    Material();

    ~Material();

    void texture(agtr::Image const& image);

    void bind(size_t textureUnit);

    void unbind();

private:
    GLuint m_texture;
    GLenum m_currentTextureUnit;
};

} // namespace

#endif // INCLUDED
