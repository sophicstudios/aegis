#include <agtg_shaderprogram.h>
#include <iostream>

namespace agtg {

bool createShader(std::vector<GLuint>& attachedShaders, std::string const& source, GLenum shaderType, GLuint program)
{
    // Create a shader object
    GLuint shader = glCreateShader(shaderType);

    // Assign the shader source to the shader object
    GLchar* buffer = new GLchar[source.length() + 1];
    memcpy(buffer, source.c_str(), source.length());
    buffer[source.length() - 1] = '\0';
    glShaderSource(shader, 1, &buffer, NULL);
    delete [] buffer;

    // Compile the shader
    glCompileShader(shader);

    // Check for compile errors
    GLint compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus != GL_TRUE)
    {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0)
        {
            char* log = new char[logLength + 1];
            glGetShaderInfoLog(shader, logLength + 1, NULL, log);

            std::cerr << "Shader compiler error ["
                << " error: " << log
                << " source: '" << source << "'"
                << " ]" << std::endl;

            delete [] log;
        }

        return false;
    }

    // Attach the compiled shader to the program
    glAttachShader(program, shader);
    attachedShaders.push_back(shader);

    return true;
}

ShaderProgram::ShaderProgram()
: m_modelViewMatrixLoc(-1),
  m_projectionMatrixLoc(-1)
{
    m_program = glCreateProgram();
    if (0 == m_program)
    {
        GLenum error = glGetError();
    }
}

ShaderProgram::~ShaderProgram()
{
    // cleanup any leftover shaders
    std::vector<GLuint>::iterator it, end = m_attachedShaders.end();
    for (it = m_attachedShaders.begin(); it != end; ++it)
    {
        glDetachShader(m_program, *it);
        glDeleteShader(*it);
    }

    glDeleteProgram(m_program);
}

bool ShaderProgram::addVertexShader(std::string const& source)
{
    return createShader(m_attachedShaders, source, GL_VERTEX_SHADER, m_program);
}

void ShaderProgram::bind()
{
    glUseProgram(m_program);
}

void ShaderProgram::bindProjectionMatrix(agtm::Matrix4<float> const& matrix)
{
    glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, matrix.arr());
}

void ShaderProgram::bindModelViewMatrix(agtm::Matrix4<float> const& matrix)
{
    glUniformMatrix4fv(m_modelViewMatrixLoc, 1, GL_FALSE, matrix.arr());
}

bool ShaderProgram::addFragmentShader(std::string const& source)
{
    return createShader(m_attachedShaders, source, GL_FRAGMENT_SHADER, m_program);
}

void ShaderProgram::bindAttributeLocation(std::string const& name, GLuint location)
{
    glBindAttribLocation(m_program, location, name.c_str());
}

bool ShaderProgram::link()
{
    bindAttributeLocation("position", 0);

    // Link the shader program
    glLinkProgram(m_program);

    // Check for link errors
    GLint linkStatus = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE)
    {
        GLint logLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0)
        {
            char* log = new char[logLength + 1];
            glGetProgramInfoLog(m_program, logLength, NULL, log);

            std::cout << "Shader program link error ["
                << " log: " << log
                << " ]" << std::endl;

            delete [] log;
            
            return false;
        }
    }

    // Detach shaders as we don't need them anymore after successful link
    std::vector<GLuint>::iterator it, end = m_attachedShaders.end();
    for (it = m_attachedShaders.begin(); it != end; ++it)
    {
        glDetachShader(m_program, *it);
    }

    m_attachedShaders.clear();

    glUseProgram(m_program);

    m_projectionMatrixLoc = glGetUniformLocation(m_program, "projectionMatrix");
    m_modelViewMatrixLoc = glGetUniformLocation(m_program, "modelViewMatrix");
    
    // Shader program is loaded and ready to use!
    return true;
}

} // namespace
