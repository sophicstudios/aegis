#ifndef INCLUDED_AGTG_SHADERPROGRAM_H
#define INCLUDED_AGTG_SHADERPROGRAM_H

#include <agtg_gl.h>
#include <agtm_matrix4.h>
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

    void bind();
    
    void bindProjectionMatrix(agtm::Matrix4<float> const& matrix);

    void bindModelViewMatrix(agtm::Matrix4<float> const& matrix);
    
    void bindAttributeLocation(std::string const& name, GLuint location);

    GLuint getUniformLocation(std::string const& name);
    
    bool link();
    
private:
    GLuint m_program;
    std::vector<GLuint> m_attachedShaders;
    GLint m_modelViewMatrixLoc;
    GLint m_projectionMatrixLoc;    
};

} // namespace

#endif // INCLUDED
