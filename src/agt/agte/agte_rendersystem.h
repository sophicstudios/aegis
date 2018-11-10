#ifndef INCLUDED_AEGIS_AGTE_RENDERSYSTEM_H
#define INCLUDED_AEGIS_AGTE_RENDERSYSTEM_H

#include <agta_assetpool.h>
#include <agta_material.h>
#include <agta_mesh.h>
#include <agte_entity.h>
#include <agte_system.h>
#include <agte_pool.h>
#include <agte_space.h>
#include <agte_camera.h>
#include <agtc_transformcomponent.h>
#include <agtc_visual2dcomponent.h>
#include <agtg_gl.h>
#include <agtg_renderingcontext.h>
#include <agtg_shaderprogram.h>
#include <agtg_texture.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
#include <agtm_matrix4.h>
#include <memory>

namespace agte {

class RenderSystem : public System
{
public:
    typedef std::shared_ptr<agte::Platform> PlatformPtr;
    typedef std::shared_ptr<agte::Space> SpacePtr;
    typedef std::shared_ptr<agte::Camera> CameraPtr;
    typedef std::shared_ptr<Pool<agtc::TransformComponent> > TransformComponentPoolPtr;
    typedef std::shared_ptr<Pool<agtc::Visual2dComponent> > Visual2dComponentPoolPtr;
    typedef std::shared_ptr<agta::AssetPool<agta::Mesh> > MeshAssetPoolPtr;
    typedef std::shared_ptr<agta::AssetPool<agta::Material> > MaterialAssetPoolPtr;
    typedef std::shared_ptr<agta::AssetPool<agtg::ShaderProgram> > ShaderAssetPoolPtr;

    RenderSystem();

    RenderSystem(int updatePriority);

    virtual ~RenderSystem();

    void addCamera(SpacePtr space, CameraPtr camera);

    void removeCamera(SpacePtr space, CameraPtr camera);

    void addTransformComponents(SpacePtr space, TransformComponentPoolPtr components);

    void addVisual2dComponents(SpacePtr space, Visual2dComponentPoolPtr components);

    void addShaderAssets(SpacePtr space, ShaderAssetPoolPtr assets);

    void addMeshAssets(SpacePtr space, MeshAssetPoolPtr assets);

    void addMaterialAssets(SpacePtr space, MaterialAssetPoolPtr assets);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    typedef std::vector<CameraPtr> CameraList;
    typedef std::map<afth::UUID, CameraList> SpaceCameraMap;
    typedef std::map<afth::UUID, TransformComponentPoolPtr> SpaceTransformComponentsMap;
    typedef std::map<afth::UUID, Visual2dComponentPoolPtr> SpaceVisual2dComponentsMap;
    typedef std::map<afth::UUID, ShaderAssetPoolPtr> SpaceShaderAssetsMap;
    typedef std::map<afth::UUID, MaterialAssetPoolPtr> SpaceMaterialAssetsMap;
    typedef std::map<afth::UUID, MeshAssetPoolPtr> SpaceMeshAssetsMap;

    Entity::ComponentSet m_componentSet;
    SpaceCameraMap m_spaceCameraMap;
    SpaceTransformComponentsMap m_spaceTransformComponentsMap;
    SpaceVisual2dComponentsMap m_spaceVisual2dComponentsMap;
    SpaceShaderAssetsMap m_spaceShaderAssetsMap;
    SpaceMaterialAssetsMap m_spaceMaterialAssetsMap;
    SpaceMeshAssetsMap m_spaceMeshAssetsMap;
};

} // namespace

#endif // INCLUDED
