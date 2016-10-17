#ifndef INCLUDED_AGTE_RENDERSYSTEM_H
#define INCLUDED_AGTE_RENDERSYSTEM_H

#include <agte_entity.h>
#include <agte_system.h>
#include <agte_componentpool.h>
#include <agte_space.h>
#include <agtc_transformcomponent.h>
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

namespace agte {

class RenderSystem : public System
{
public:
    typedef std::shared_ptr<agte::Platform> PlatformPtr;
    typedef std::shared_ptr<agte::Space> SpacePtr;
    typedef std::shared_ptr<agte::Camera> CameraPtr;
    typedef std::shared_ptr<ComponentPool<agtc::TransformComponent> > TransformComponentManagerPtr;

    RenderSystem(PlatformPtr platform, int updatePriority = 0);

    virtual ~RenderSystem();

    void addCamera(SpacePtr space, CameraPtr camera);

    void removeCamera(SpacePtr space, CameraPtr camera);

    void addTransformComponents(SpacePtr space, TransformComponentManagerPtr components);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

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
