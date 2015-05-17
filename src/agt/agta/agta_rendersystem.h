#ifndef INCLUDED_AGTA_RENDERSYSTEM_H
#define INCLUDED_AGTA_RENDERSYSTEM_H

#include <agta_system.h>
#include <agta_glwindow.h>
#include <agta_componentmanager.h>
#include <agta_transformcomponent.h>
#include <agtg_gl.h>
#include <agtg_texture.h>
#include <aftfs_filesystem.h>
#include <agtm_matrix4.h>
#include <actp_mutex.h>
#include <atomic>
#include <memory>

namespace agta {

class RenderSystem : public System
{
public:
    RenderSystem(std::shared_ptr<agta::Platform> platform, int updatePriority = 0);

    virtual ~RenderSystem();

protected:
    virtual void doPreUpdate(agta::Engine::Context& context);

    virtual void doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context);

    virtual void doPostUpdate(agta::Engine::Context& context);

private:
    void render(agtg::RenderingContext& renderingContext);

    GLuint m_vertexBuffer;
    GLuint m_vertexArray;
    GLuint m_program;
    GLint m_modelViewMatrixLoc;
    GLint m_projectionMatrixLoc;
    agtm::Matrix4<float> m_modelViewMatrix;
    agtm::Matrix4<float> m_projectionMatrix;
    std::shared_ptr<agtg::Texture> m_texture;
};

} // namespace

#endif // INCLUDED
