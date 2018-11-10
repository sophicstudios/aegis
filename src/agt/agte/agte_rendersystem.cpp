#include <agte_rendersystem.h>
#include <agte_platform.h>
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

namespace {

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

void initComponentSet(Entity::ComponentSet& componentSet)
{
    //componentSet.set(agte::ComponentPool<agtc::TransformComponent>::type());
    //componentSet.set(agte::ComponentPool<agtc::Visual2dComponent>::type());
}

} // namespace

RenderSystem::RenderSystem()
{
    initComponentSet(m_componentSet);
}

RenderSystem::RenderSystem(int updatePriority)
: agte::System(updatePriority)
{
    initComponentSet(m_componentSet);
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
    Space::EntityView entityView = space->entitiesForComponents(m_componentSet);

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
    //   for each camera in the space
    //     initialize the view (viewport, background, blending, etc.)
    //     for each entity
    //       bind its shader
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
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        size_t prevShaderId = 0;
        size_t currentShaderId = 0;
        GLint projectionMatrixLocation;
        GLint modelViewMatrixLocation;
        GLint texOffsetLocation;
        agtg::ShaderProgram* shader = nullptr;

        for (; it != end; ++it)
        {
            //agtc::Visual2dComponent& visual = visual2dComponents->componentForEntity(*it);
            //currentShaderId = visual.shaderId();

            if (currentShaderId != prevShaderId)
            {
                if (shader)
                {
                    shader->unbind();
                }

                shader = &(shaderAssets->assetForId(currentShaderId));

                prevShaderId = currentShaderId;
                shader->bind();

                projectionMatrixLocation = shader->getUniformLocation("projectionMatrix");
                modelViewMatrixLocation = shader->getUniformLocation("modelViewMatrix");
                texOffsetLocation = shader->getUniformLocation("texOffset");

                shader->bindUniform(projectionMatrixLocation, projectionMatrix);
            }

            //shader->bindUniform(texOffsetLocation, visual.spriteOffset());

            //agtc::TransformComponent& transform = transformComponents->componentForEntity(*it);
            //agtm::Matrix4<float> modelViewMatrix = transform.transform() * viewMatrix;

            //shader->bindUniform(modelViewMatrixLocation, modelViewMatrix);

            //AFTL_LOG_TRACE << "modelViewMatrix: " << modelViewMatrix << AFTL_LOG_END;

            //size_t meshId = visual.meshId();
            //agta::Mesh& mesh = meshAssets->assetForId(meshId);

            //mesh.bind(*shader);

            //size_t materialId = visual.materialId();
            //agta::Material& material = materialAssets->assetForId(materialId);
            //material.bind(0);

            //mesh.draw();

            //mesh.unbind();
            //material.unbind();
        }

        if (shader)
        {
            shader->unbind();
        }

        renderingContext->postRender();
        checkError("postRender");
    }
}

void RenderSystem::doPostUpdate(agte::Engine::Context& context)
{
}

} // namespace
