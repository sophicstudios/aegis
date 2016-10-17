#include <agte_rendersystem.h>
#include <agte_platform.h>
#include <agtc_visual2dcomponent.h>
#include <agtr_image.h>
#include <agtr_imageloaderpng.h>
#include <agtg_renderingcontext.h>
#include <agtg_gl.h>
#include <actp_scopedlock.h>
#include <aftfs_filesystem.h>
#include <aftu_url.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace agte {

struct Vertex
{
    float position[3];
};

static const Vertex s_vertices[] = {
    -8.0f, -8.0f, 0.0f,
     8.0f, -8.0f, 0.0f,
    -8.0f,  8.0f, 0.0f,
     8.0f,  8.0f, 0.0f
};

bool createShaderProgram(GLuint* program,
                         agte::Platform::FilesystemPtr filesystem,
                         std::vector<std::pair<std::string, GLenum> > const& shaders,
                         std::vector<std::pair<std::string, GLuint> > const& attribLocations)
{
    if (shaders.empty()) {
        return false;
    }

    // Create the shader program object
    *program = glCreateProgram();

    std::vector<GLuint> attachedShaders;

    std::vector<std::pair<std::string, GLenum> >::const_iterator shaderIt = shaders.begin();
    std::vector<std::pair<std::string, GLenum> >::const_iterator shaderEnd = shaders.end();
    for (; shaderIt != shaderEnd; ++shaderIt) {
        // Create a url of the shader source file location for use in the Filesystem calls
        aftu::URL shaderUrl(shaderIt->first);

        // Create filesystem entry and reader to read the file contents
        aftfs::Filesystem::DirectoryEntryPtr entry = filesystem->directoryEntry(shaderUrl);
        aftfs::Filesystem::FileReaderPtr fileReader = filesystem->openFileReader(shaderUrl);

        // Read the file contents into a character buffer
        char* buffer = new char[entry->size()];
        size_t bytesRead = 0;
        fileReader->read(buffer, entry->size(), &bytesRead);
        buffer[bytesRead] = 0;

        // Create a shader object
        GLuint shader = glCreateShader(shaderIt->second);

        // Assign the shader source to the shader object
        glShaderSource(shader, 1, &buffer, NULL);

        delete [] buffer;

        // Compile the shader
        glCompileShader(shader);

        // Check for compile errors
        GLint compileStatus = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

        if (compileStatus != GL_TRUE) {
            GLint logLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0) {
                char* log = new char[logLength + 1];
                glGetShaderInfoLog(shader, logLength + 1, NULL, log);

                std::cout << "Shader compiler error ["
                    << " file: " << shaderIt->first
                    << " error: " << log
                    << " ]" << std::endl;

                delete [] log;
            }

            std::vector<GLuint>::iterator attachedShaderIt = attachedShaders.begin();
            std::vector<GLuint>::iterator attachedShaderEnd = attachedShaders.end();
            for (; attachedShaderIt != attachedShaderEnd; ++attachedShaderIt) {
                glDetachShader(*program, *attachedShaderIt);
                glDeleteShader(*attachedShaderIt);
            }

            glDeleteProgram(*program);

            return false;
        }

        // Attach the compiled shader to the program
        glAttachShader(*program, shader);

        attachedShaders.push_back(shader);
    }

    std::vector<std::pair<std::string, GLuint> >::const_iterator attribLocationsIt = attribLocations.begin();
    std::vector<std::pair<std::string, GLuint> >::const_iterator attribLocationsEnd = attribLocations.end();
    for (; attribLocationsIt != attribLocationsEnd; ++attribLocationsIt) {
        glBindAttribLocation(*program, attribLocationsIt->second, attribLocationsIt->first.c_str());
    }

    // Link the shader program
    glLinkProgram(*program);

    // Check for link errors
    GLint linkStatus = 0;
    glGetProgramiv(*program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            char* log = new char[logLength + 1];
            glGetProgramInfoLog(*program, logLength, NULL, log);

            std::cout << "Shader program link error ["
                << " log: " << log
                << " ]" << std::endl;

            std::vector<GLuint>::iterator jit = attachedShaders.begin(), jend = attachedShaders.end();
            for (; jit != jend; ++jit) {
                glDetachShader(*program, *jit);
                glDeleteShader(*jit);
            }

            glDeleteProgram(*program);

            return false;
        }
    }

    // Detach shaders as we don't need them anymore after successful link
    std::vector<GLuint>::iterator jit = attachedShaders.begin(), jend = attachedShaders.end();
    for (; jit != jend; ++jit) {
        glDetachShader(*program, *jit);
    }

    // Shader program is loaded and ready to use!
    return true;
}

char const* const translateGLenum(GLenum value)
{
    switch (value) {
    case GL_NO_ERROR: return "GL_NO_ERROR";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_ENUM: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default: return "UNKNOWN GL error";
    }
}

void checkError(char const* const context)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "glError [" << context << "]: " << translateGLenum(error) << " (" << error << ")" << std::endl;
    }
}

RenderSystem::RenderSystem(std::shared_ptr<agte::Platform> platform, int updatePriority)
: agte::System(updatePriority)
{
    m_componentSet.set(agte::ComponentPool<agtc::TransformComponent>::type());
    m_componentSet.set(agte::ComponentPool<agtc::Visual2dComponent>::type());

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    //aftu::URL imageUrl("images/antsprites.png");
    //agtr::ImageLoaderPNG pngLoader;
    //std::shared_ptr<agtr::Image> image = pngLoader.load(filesystem, imageUrl);

    //m_texture = std::shared_ptr<agtg::Texture>(new agtg::Texture(image));

    std::vector<std::pair<std::string, GLenum> > shaders;
    shaders.push_back(std::make_pair("shaders/sprite.vsh", GL_VERTEX_SHADER));
    shaders.push_back(std::make_pair("shaders/sprite.fsh", GL_FRAGMENT_SHADER));

    std::vector<std::pair<std::string, GLuint> > attribLocations;
    attribLocations.push_back(std::make_pair("position", 0));

    if (!createShaderProgram(&m_program, platform->filesystem(), shaders, attribLocations)) {
        throw aftu::Exception("Unable to load shaders");
    }

    m_modelViewMatrixLoc = glGetUniformLocation(m_program, "modelViewMatrix");
    m_projectionMatrixLoc = glGetUniformLocation(m_program, "projectionMatrix");
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::doPreUpdate(agte::Engine::Context& context)
{
}


void RenderSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    std::cout << "RenderSystem::doUpdate" << std::endl;

    std::shared_ptr<agtg::RenderingContext> renderingContext = context.platform()->glView()->renderingContext();

    renderingContext->preRender();

    
    // get the camera for the space
    SpaceCameraMap::iterator spaceCameraIter = m_spaceCameraMap.find(space->id());
    if (spaceCameraIter == m_spaceCameraMap.end())
    {
        // if no camera, skip this update
        return;
    }

    CameraPtr camera = spaceCameraIter->second;

    // get list of entities with visual and transform components
    Space::EntityView entityView = space->getEntitiesForComponents(m_componentSet);
    
    // sort entities by visual component material

    // set the viewport from the camera
    agtm::Rect<float> const& rect = camera->viewport();
    glViewport(rect.x(), rect.y(), rect.width(), rect.height());

    // for each entity, get its transform and visual compoonents
    render(*renderingContext, camera, entityView);

    renderingContext->postRender();
}

void RenderSystem::doPostUpdate(agte::Engine::Context& context)
{
}

// get the list of renderable entities
// sort by render states (should this already be sorted?)
// for each render state
    // set the render state
    // for each entity in the render state
        // get the entity transform
        // get the entity renderable
        // apply the transform
        // draw the renderable
void RenderSystem::render(agtg::RenderingContext& renderingContext, CameraPtr camera, Space::EntityView const& entities)
{
    std::cout << "RenderSystem::render" << std::endl;
    
    glClearColor(0.9f, 0.7f, 0.7f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_program);

    glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, m_projectionMatrix.arr());

    Space::EntityView::Iterator it = entities.begin();
    Space::EntityView::Iterator end = entities.end();

    agtm::Matrix4<float> viewMatrix = camera->view();
    agtm::Matrix4<float> projMatrix = camera->projection();
    agtm::Matrix4<float> modelViewMatrix;

    // set the view and projection matrices from the camera
    m_modelViewMatrix = camera->view();
    m_projectionMatrix = camera->projection();

    for (; it != end; ++it)
    {
        glBindVertexArray(m_vertexArray);

        glUniformMatrix4fv(m_modelViewMatrixLoc, 1, GL_FALSE, m_modelViewMatrix.arr());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    glUseProgram(0);
}

} // namespace
