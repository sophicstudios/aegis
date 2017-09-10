#ifndef INCLUDED_AGTG_TEXTURE_H
#define INCLUDED_AGTG_TEXTURE_H

#include <agtg_gl.h>
#include <agtr_image.h>
#include <memory>

namespace agtg {

class Texture
{
public:
    Texture(std::shared_ptr<agtr::Image> image);
    
    ~Texture();

    GLuint id() const;

    GLsizei width() const;

    GLsizei height() const;
    
private:
    GLuint m_textureId;
    GLsizei m_width;
    GLsizei m_height;
    //GLfloat m_frameWidth;
};

} // namespace

#endif // INCLUDED
