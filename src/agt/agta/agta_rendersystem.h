#ifndef INCLUDED_AGTA_RENDERSYSTEM_H
#define INCLUDED_AGTA_RENDERSYSTEM_H

#include <agta_entity.h>
#include <agta_system.h>
#include <agta_glwindow.h>
#include <agta_componentpool.h>
#include <agta_space.h>
#include <agta_transformcomponent.h>
#include <agtg_camera.h>
#include <agtg_gl.h>
#include <agtg_texture.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
#include <agtm_matrix4.h>
#include <actp_mutex.h>
#include <atomic>
#include <memory>
#include <bitset>

namespace agta {

class RenderSystem : public System
{
public:
    typedef std::shared_ptr<agta::Platform> PlatformPtr;
    typedef std::shared_ptr<agta::Space> SpacePtr;
    typedef std::shared_ptr<agtg::Camera> CameraPtr;
    typedef std::shared_ptr<ComponentPool<TransformComponent> > TransformComponentManagerPtr;

    RenderSystem(PlatformPtr platform, int updatePriority = 0);

    virtual ~RenderSystem();

    void addCamera(SpacePtr space, CameraPtr camera);

    void removeCamera(SpacePtr space, CameraPtr camera);

    void addTransformComponents(SpacePtr space, TransformComponentManagerPtr components);

protected:
    virtual void doPreUpdate(agta::Engine::Context& context);

    virtual void doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context);

    virtual void doPostUpdate(agta::Engine::Context& context);

private:
    void render(agtg::RenderingContext& renderingContext, CameraPtr camera, Space::EntityView const& entities);

    typedef std::map<afth::UUID, CameraPtr> SpaceCameraMap;
    typedef std::map<afth::UUID, TransformComponentManagerPtr> SpaceTransformComponentsMap;

    SpaceCameraMap m_spaceCameraMap;
    SpaceTransformComponentsMap m_spaceTransformComponentsMap;
    Entity::ComponentSet m_componentSet;
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
