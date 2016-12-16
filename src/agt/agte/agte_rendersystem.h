#ifndef INCLUDED_AGTE_RENDERSYSTEM_H
#define INCLUDED_AGTE_RENDERSYSTEM_H

#include <agte_entity.h>
#include <agte_system.h>
#include <agte_componentpool.h>
#include <agte_space.h>
#include <agte_camera.h>
#include <agtc_transformcomponent.h>
#include <agtc_visual2dcomponent.h>
#include <agtg_gl.h>
#include <agtg_renderingcontext.h>
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
    typedef std::shared_ptr<ComponentPool<agtc::TransformComponent> > TransformComponentPoolPtr;
    typedef std::shared_ptr<ComponentPool<agtc::Visual2dComponent> > Visual2dComponentPoolPtr;

    RenderSystem(PlatformPtr platform, int updatePriority = 0);

    virtual ~RenderSystem();

    void addCamera(SpacePtr space, CameraPtr camera);

    void removeCamera(SpacePtr space, CameraPtr camera);

    void addTransformComponents(SpacePtr space, TransformComponentPoolPtr components);

    void addVisual2dComponents(SpacePtr space, Visual2dComponentPoolPtr components);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    typedef std::vector<CameraPtr> CameraList;
    typedef std::map<afth::UUID, CameraList> SpaceCameraMap;
    typedef std::map<afth::UUID, TransformComponentPoolPtr> SpaceTransformComponentsMap;
    typedef std::map<afth::UUID, Visual2dComponentPoolPtr> SpaceVisual2dComponentsMap;

    SpaceCameraMap m_spaceCameraMap;
    SpaceTransformComponentsMap m_spaceTransformComponentsMap;
    SpaceVisual2dComponentsMap m_spaceVisual2dComponentsMap;
    Entity::ComponentSet m_componentSet;
    GLint m_modelViewMatrixLoc;
    GLint m_projectionMatrixLoc;
    agtm::Matrix4<float> m_modelViewMatrix;
    agtm::Matrix4<float> m_projectionMatrix;
    std::shared_ptr<agtg::Texture> m_texture;
};

} // namespace

#endif // INCLUDED
