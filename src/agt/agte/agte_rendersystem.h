#ifndef INCLUDED_AEGIS_AGTE_RENDERSYSTEM_H
#define INCLUDED_AEGIS_AGTE_RENDERSYSTEM_H

#include <agta_assetpool.h>
#include <agta_material.h>
#include <agta_mesh.h>
#include <agte_system.h>
#include <agte_engine.h>
#include <agte_camera.h>
#include <agtg_renderingcontext.h>
#include <agtg_shaderprogram.h>
#include <agtg_texture.h>
#include <afth_uuid.h>
#include <memory>

namespace agte {

class RenderSystem : public System
{
public:
    typedef std::shared_ptr<agte::Camera> CameraPtr;
    typedef std::shared_ptr<agta::AssetPool<agta::Mesh> > MeshAssetPoolPtr;
    typedef std::shared_ptr<agta::AssetPool<agta::Material> > MaterialAssetPoolPtr;
    typedef std::shared_ptr<agta::AssetPool<agtg::ShaderProgram> > ShaderAssetPoolPtr;

    RenderSystem();

    RenderSystem(int updatePriority);

    virtual ~RenderSystem();

    void addCamera(agte::Engine::SpacePtr space, CameraPtr camera);

    void removeCamera(agte::Engine::SpacePtr space, CameraPtr camera);

    void addShaderAssets(agte::Engine::SpacePtr space, ShaderAssetPoolPtr assets);

    void addMeshAssets(agte::Engine::SpacePtr space, MeshAssetPoolPtr assets);

    void addMaterialAssets(agte::Engine::SpacePtr space, MaterialAssetPoolPtr assets);

protected:
    virtual void doPreUpdate(agte::Engine::Context& context);

    virtual void doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context);

    virtual void doPostUpdate(agte::Engine::Context& context);

private:
    typedef std::vector<CameraPtr> CameraList;
    typedef std::map<afth::UUID, CameraList> SpaceCameraMap;
    typedef std::map<afth::UUID, ShaderAssetPoolPtr> SpaceShaderAssetsMap;
    typedef std::map<afth::UUID, MaterialAssetPoolPtr> SpaceMaterialAssetsMap;
    typedef std::map<afth::UUID, MeshAssetPoolPtr> SpaceMeshAssetsMap;

    Space::Entity::ComponentSet m_componentSet;
    SpaceCameraMap m_spaceCameraMap;
    SpaceShaderAssetsMap m_spaceShaderAssetsMap;
    SpaceMaterialAssetsMap m_spaceMaterialAssetsMap;
    SpaceMeshAssetsMap m_spaceMeshAssetsMap;
};

} // namespace

#endif // INCLUDED
