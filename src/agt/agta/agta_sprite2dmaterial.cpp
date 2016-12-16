#include <agta_sprite2dmaterial.h>

namespace agta {

namespace {

std::string loadShaderSource(std::shared_ptr<aftfs::FileSystem> fileSystem, std::string const& path)
{
    // Create a url of the shader source file location for use in the Filesystem calls
    aftu::URL shaderURL(path);

    // Create filesystem entry and reader to read the file contents
    aftfs::FileSystem::DirectoryEntryPtr entry = fileSystem->directoryEntry(shaderURL);
    aftfs::FileSystem::FileReaderPtr fileReader = fileSystem->openFileReader(shaderURL);

    // Read the file contents into a character buffer
    char* buffer = new char[entry->size()];
    size_t bytesRead = 0;
    fileReader->read(buffer, entry->size(), &bytesRead);
    buffer[bytesRead] = 0;

    return std::string(buffer);
}

} // namespace

Sprite2dMaterial::Sprite2dMaterial(FileSystemPtr fileSystem)
{
    m_shaderProgram = std::shared_ptr<agtg::ShaderProgram>(new agtg::ShaderProgram());

    std::string vertexShader = loadShaderSource(fileSystem, "shaders/sprite.vsh");
    std::string fragShader = loadShaderSource(fileSystem, "shaders/sprite.fsh");

    m_shaderProgram->addVertexShader(vertexShader);
    m_shaderProgram->addFragmentShader(fragShader);

    m_shaderProgram->link();
}

Sprite2dMaterial::~Sprite2dMaterial()
{}

afth::UUID const& Sprite2dMaterial::id() const
{
    return m_id;
}

} // namespace
