#include <agtg_shaderprogram.h>
#include <agtm_matrix4.h>
#include <agtm_matrix4util.h>
#include <aftfs_filesystem.h> 
#include <aftl_logger.h>

namespace agtg {

std::string loadShaderSource(aftfs::FileSystem& fileSystem, std::string const& path)
{
    // Create a url of the shader source file location for use in the Filesystem calls
    aftu::URL shaderURL(path);

    // Create filesystem entry and reader to read the file contents
    aftfs::FileSystem::DirectoryEntryPtr entry = fileSystem.directoryEntry(shaderURL);
    aftfs::FileSystem::FileReaderPtr fileReader = fileSystem.openFileReader(shaderURL);

    // Read the file contents into a character buffer
    char* buffer = new char[entry->size()];
    size_t bytesRead = 0;
    fileReader->read(buffer, entry->size(), &bytesRead);
    buffer[bytesRead] = 0;

    return std::string(buffer);
}

bool createShader(std::vector<GLuint>& attachedShaders, std::string const& source, GLenum shaderType, GLuint program)
{
    // Create a shader object
    GLuint shader = glCreateShader(shaderType);

    // Assign the shader source to the shader object
    GLchar* buffer = new GLchar[source.length() + 1];
    memcpy(buffer, source.c_str(), source.length());
    buffer[source.length() - 1] = '\0';
    AFTL_LOG_TRACE << "Compiling shader source [" << buffer << "]" << AFTL_LOG_END;
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

            AFTL_LOG_ERROR << "Shader compiler error ["
                << " error: " << log
                << " source: '" << source << "'"
                << " ]" << AFTL_LOG_END;

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
{
    m_program = glCreateProgram();
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

bool ShaderProgram::addVertexShader(aftfs::FileSystem &fileSystem, const std::string &path)
{
    std::string source = loadShaderSource(fileSystem, path);
    if (source.empty())
    {
        return false;
    }

    return createShader(m_attachedShaders, source, GL_VERTEX_SHADER, m_program);
}

bool ShaderProgram::addFragmentShader(std::string const& source)
{
    return createShader(m_attachedShaders, source, GL_FRAGMENT_SHADER, m_program);
}

bool ShaderProgram::addFragmentShader(aftfs::FileSystem &fileSystem, const std::string &path)
{
    std::string source = loadShaderSource(fileSystem, path);
    if (source.empty())
    {
        return false;
    }

    return createShader(m_attachedShaders, source, GL_FRAGMENT_SHADER, m_program);
}

bool ShaderProgram::link()
{
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

            AFTL_LOG_ERROR << "Shader program link error ["
                << " log: " << log
                << " ]" << AFTL_LOG_END;

            delete [] log;
            
            return false;
        }
    }

    // Detach shaders as we don't need them anymore after successful link
    std::vector<GLuint>::iterator it, end = m_attachedShaders.end();
    for (it = m_attachedShaders.begin(); it != end; ++it)
    {
        glDetachShader(m_program, *it);
        glDeleteShader(*it);
    }

    m_attachedShaders.clear();

    // Shader program is ready to use!
    return true;
}

GLint ShaderProgram::getUniformLocation(std::string const& name)
{
    return glGetUniformLocation(m_program, name.c_str());
}

GLint ShaderProgram::getAttributeLocation(std::string const& name)
{
    return glGetAttribLocation(m_program, name.c_str());
}

void ShaderProgram::bindUniform(GLint location, agtm::Matrix4<float> const& matrix)
{
    glUniformMatrix4fv(location, 1 /*count*/, GL_FALSE /*transpose*/, agtm::Matrix4Util::toColMajor(matrix).data());
}

void ShaderProgram::bindUniform(GLint location, agtm::Vector3<float> const& vector)
{
    glUniform3fv(location, 1 /*count*/, vector.arr().data());
}

void ShaderProgram::bindUniform(GLint location, agtm::Vector2<float> const& vector)
{
    glUniform2fv(location, 1 /*count*/, vector.arr().data());
}

void ShaderProgram::bindUniform(GLint location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::bind()
{
    glUseProgram(m_program);
}

void ShaderProgram::unbind()
{
    glUseProgram(0);
}

} // namespace
