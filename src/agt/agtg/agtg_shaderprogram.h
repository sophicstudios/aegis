#ifndef INCLUDED_AGTG_SHADERPROGRAM_H
#define INCLUDED_AGTG_SHADERPROGRAM_H

#include <agtg_gl.h>
#include <agtm_matrix4.h>
#include <aftfs_filesystem.h>
#include <memory>
#include <vector>

namespace agtg {

class ShaderProgram
{
public:
    ShaderProgram();

    ~ShaderProgram();

    bool addVertexShader(aftfs::Filesystem& filesystem, std::string const& path);

    bool addVertexShader(std::string const& source);

    bool addFragmentShader(aftfs::Filesystem& filesystem, std::string const& path);

    bool addFragmentShader(std::string const& source);

    bool link();

    GLint getUniformLocation(std::string const& name);

    GLint getAttributeLocation(std::string const& name);

    void bind();

    void bindUniformMatrix(GLint location, agtm::Matrix4<float> const& matrix);

private:
    GLuint m_program;
    std::vector<GLuint> m_attachedShaders;
};

} // namespace

#endif // INCLUDED
