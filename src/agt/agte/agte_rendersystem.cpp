#include <agte_rendersystem.h>
#include <agte_platform.h>
//#include <agta_sprite2dmaterial.h>
#include <agtc_transformcomponent.h>
#include <agtc_visual2dcomponent.h>
#include <agtr_image.h>
#include <agtr_imageloaderpng.h>
#include <agtg_renderingcontext.h>
#include <agtg_gl.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
#include <aftu_url.h>
#include <aftl_logger.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace agte {

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
        AFTL_LOG_ERROR << "glError [" << context << "]: " << translateGLenum(error) << " (" << error << ")" << AFTL_LOG_END;
    }
}

RenderSystem::RenderSystem(std::shared_ptr<agte::Platform> platform, int updatePriority)
: agte::System(updatePriority)
{
    m_componentSet.set(agte::ComponentPool<agtc::TransformComponent>::type());
    m_componentSet.set(agte::ComponentPool<agtc::Visual2dComponent>::type());

    //aftu::URL imageUrl("images/antsprites.png");
    //agtr::ImageLoaderPNG pngLoader;
    //std::shared_ptr<agtr::Image> image = pngLoader.load(filesystem, imageUrl);

    //m_texture = std::shared_ptr<agtg::Texture>(new agtg::Texture(image));
}

RenderSystem::~RenderSystem()
{}

void RenderSystem::addCamera(SpacePtr space, CameraPtr camera)
{
    SpaceCameraMap::iterator it = m_spaceCameraMap.find(space->id());
    if (it == m_spaceCameraMap.end())
    {
        it = m_spaceCameraMap.insert(std::make_pair(space->id(), CameraList())).first;
    }

    it->second.push_back(camera);
}

void RenderSystem::removeCamera(SpacePtr space, CameraPtr camera)
{
    SpaceCameraMap::iterator it = m_spaceCameraMap.find(space->id());
    if (it != m_spaceCameraMap.end())
    {
        CameraList::iterator camIter, camEnd = it->second.end();
        for (camIter = it->second.begin(); camIter != camEnd; ++camIter)
        {
            if ((*camIter)->id() == camera->id())
            {
                it->second.erase(camIter);
                break;
            }
        }
    }
}

void RenderSystem::addTransformComponents(SpacePtr space, TransformComponentPoolPtr components)
{
    m_spaceTransformComponentsMap.insert(std::make_pair(space->id(), components));
}

void RenderSystem::addVisual2dComponents(SpacePtr space, Visual2dComponentPoolPtr components)
{
    m_spaceVisual2dComponentsMap.insert(std::make_pair(space->id(), components));
}

void RenderSystem::addShaderAssets(SpacePtr space, ShaderAssetPoolPtr assets)
{
    m_spaceShaderAssetsMap.insert(std::make_pair(space->id(), assets));
}

void RenderSystem::addMaterialAssets(SpacePtr space, MaterialAssetPoolPtr assets)
{
    m_spaceMaterialAssetsMap.insert(std::make_pair(space->id(), assets));
}

void RenderSystem::addMeshAssets(SpacePtr space, MeshAssetPoolPtr assets)
{
    m_spaceMeshAssetsMap.insert(std::make_pair(space->id(), assets));
}

void RenderSystem::doPreUpdate(agte::Engine::Context& context)
{
}

void RenderSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    AFTL_LOG_TRACE << "RenderSystem::doUpdate" << AFTL_LOG_END;

    // get the camera for the space
    SpaceCameraMap::iterator spaceCameraIter = m_spaceCameraMap.find(space->id());
    if (spaceCameraIter == m_spaceCameraMap.end())
    {
        // if no camera, skip this update
        return;
    }

    // get the transform components for the space
    SpaceTransformComponentsMap::iterator transformIter = m_spaceTransformComponentsMap.find(space->id());
    if (transformIter == m_spaceTransformComponentsMap.end())
    {
        return;
    }
    TransformComponentPoolPtr transformComponents = transformIter->second;

    // get the visual2d components for the space
    SpaceVisual2dComponentsMap::iterator visual2dIter = m_spaceVisual2dComponentsMap.find(space->id());
    if (visual2dIter == m_spaceVisual2dComponentsMap.end())
    {
        return;
    }
    Visual2dComponentPoolPtr visual2dComponents = visual2dIter->second;

    SpaceShaderAssetsMap::iterator shaderIter = m_spaceShaderAssetsMap.find(space->id());
    if (shaderIter == m_spaceShaderAssetsMap.end())
    {
        return;
    }
    ShaderAssetPoolPtr shaderAssets = shaderIter->second;

    SpaceMaterialAssetsMap::iterator materialIter = m_spaceMaterialAssetsMap.find(space->id());
    if (materialIter == m_spaceMaterialAssetsMap.end())
    {
        return;
    }
    MaterialAssetPoolPtr materialAssets = materialIter->second;

    SpaceMeshAssetsMap::iterator meshIter = m_spaceMeshAssetsMap.find(space->id());
    if (meshIter == m_spaceMeshAssetsMap.end())
    {
        return;
    }
    MeshAssetPoolPtr meshAssets = meshIter->second;

    // update all the cameras
    CameraList::iterator cameraIter, cameraEnd = spaceCameraIter->second.end();
    for (cameraIter = spaceCameraIter->second.begin(); cameraIter != cameraEnd; ++cameraIter)
    {
        (*cameraIter)->update();
    }

    // get list of entities with visual and transform components
    Space::EntityView entityView = space->getEntitiesForComponents(m_componentSet);

    // Sort the entities according to z-order, shader, mesh and material.
    typedef std::vector<Entity> EntityList;
    typedef std::map<afth::UUID, EntityList> MaterialEntityListMap;
    MaterialEntityListMap materialEntityListMap;

    Space::EntityView::Iterator it = entityView.begin();
    Space::EntityView::Iterator end = entityView.end();
    for (; it != end; ++it)
    {
        //agtc::Visual2dComponent& visual2dComponent = visual2dComponents->componentForEntity(*it);
        //std::shared_ptr<agta::Sprite2dMaterial> material = visual2dComponent.material();

        //materialEntityListMap.insert(std::make_pair(material->id(), *it));
    }

    // rendering logic:
    //  for each material in the material entitylist map
    //    bind the material to the renderer
    //    bind the projection matrix to the material
    //    for each entity in the entity list
    //      get/create a batch drawer for the mesh
    //      add mesh to drawer
    //      add modelview matrix to drawer
    for (cameraIter = spaceCameraIter->second.begin(); cameraIter != cameraEnd; ++cameraIter)
    {
        std::shared_ptr<agtg::RenderingContext> renderingContext = context.platform()->glView()->renderingContext();
        renderingContext->preRender();
        checkError("preRender");

        // set the viewport from the camera
        agtm::Rect<float> const& rect = (*cameraIter)->viewport();
        AFTL_LOG_TRACE << "viewport: " << rect << AFTL_LOG_END;
        glViewport(rect.x(), rect.y(), rect.width(), rect.height());
        checkError("glViewport");

        glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
        checkError("glClearColor");

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        checkError("glClear");

        //glEnable(GL_CULL_FACE);
        //glEnable(GL_BLEND);

        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set the projection matrix from the camera
        agtm::Matrix4<float> projectionMatrix = (*cameraIter)->projection();
        agtm::Matrix4<float> viewMatrix = (*cameraIter)->view();

        // Loop though material-entity map to iterate through all entities, sorted
        // by material, then draw each entity
        /*
        MaterialEntityMap::iterator it = materialEntityMap.begin();
        MaterialEntityMap::iterator end = materialEntityMap.end();
        for (; it != end; ++it)
        {
            Entity& entity = it->second;

            // for each entity, get its transform and visual compoonents
            agtc::TransformComponent& transformComponent = transformComponents->componentForEntity(entity);
            agtm::Matrix4<float> modelViewMatrix = transformComponent.transform() * viewMatrix;

            agtc::Visual2dComponent& visual2dComponent = visual2dComponents->componentForEntity(entity);

            visual2dComponent.projectionMatrix(projectionMatrix);
            visual2dComponent.modelViewMatrix(modelViewMatrix);
        }
*/

        Space::EntityView::Iterator it = entityView.begin();
        Space::EntityView::Iterator end = entityView.end();

        for (; it != end; ++it)
        {
            agtc::Visual2dComponent& visual = visual2dComponents->componentForEntity(*it);
            size_t shaderId = visual.shaderId();
            agtg::ShaderProgram& shader = shaderAssets->assetForId(shaderId);

            shader.bind();

            GLint projMatrixLocation = shader.getUniformLocation("projectionMatrix");
            if (projMatrixLocation != -1)
            {
                shader.bindUniformMatrix(projMatrixLocation, projectionMatrix);
            }

            agtc::TransformComponent& transform = transformComponents->componentForEntity(*it);
            agtm::Matrix4<float> modelViewMatrix = transform.transform() * viewMatrix;

            GLint modelViewMatrixLocation = shader.getUniformLocation("modelViewMatrix");
            if (modelViewMatrixLocation != -1)
            {
                shader.bindUniformMatrix(modelViewMatrixLocation, modelViewMatrix);
            }
            
            AFTL_LOG_TRACE << "modelViewMatrix: " << modelViewMatrix << AFTL_LOG_END;

            size_t meshId = visual.meshId();
            agta::Mesh& mesh = meshAssets->assetForId(meshId);

            mesh.bind(shader);

            mesh.draw();
            mesh.unbind();

            shader.unbind();
        }

        renderingContext->postRender();
        checkError("postRender");
    }
}

void RenderSystem::doPostUpdate(agte::Engine::Context& context)
{
}

} // namespace
