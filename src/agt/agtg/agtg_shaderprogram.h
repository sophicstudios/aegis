#ifndef INCLUDED_AGTG_SHADERPROGRAM_H
#define INCLUDED_AGTG_SHADERPROGRAM_H

#include <agtg_gl.h>
#include <memory>
#include <vector>

namespace agtg {

class ShaderProgram
{
public:
    ShaderProgram();

    ~ShaderProgram();

    bool addVertexShader(std::string const& source);

    bool addFragmentShader(std::string const& source);

    void bindAttributeLocation(std::string const& name, GLuint location);

    GLuint getUniformLocation(std::string const& name);
    
    bool link();
    
private:
    GLuint m_program;
    std::vector<GLuint> m_attachedShaders;
};

} // namespace

#endif // INCLUDED
