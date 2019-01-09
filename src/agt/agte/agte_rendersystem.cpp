#include <agte_rendersystem.h>
#include <agte_platform.h>
#include <agtc_componenthandle.h>
#include <agtc_transformcomponent.h>
#include <agtc_visual2dcomponent.h>
#include <agtg_renderingcontext.h>
#include <agtg_gl.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
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
    case GL_FRAMEBUFFER_UNDEFINED: return "GL_FRAMEBUFFER_UNDEFINED";
    default: return "Unhandled GLenum";
    }
}

void checkError(char const* const context)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::stringstream s;
        s << "glError [" << context << "]: " << translateGLenum(error) << " (" << error << ")";

        if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
            GLenum stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            s << " framebuffer status: " << translateGLenum(stat) << " (" << stat << ")";
        }

        AFTL_LOG_ERROR << s.str() << AFTL_LOG_END;
    }
}

void initComponentSet(Space::Entity::ComponentSet& componentSet)
{
    componentSet.set(agtc::ComponentHandle<agtc::TransformComponent>::typeId());
    componentSet.set(agtc::ComponentHandle<agtc::Visual2dComponent>::typeId());
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

void RenderSystem::addCamera(agte::Engine::SpacePtr space, CameraPtr camera)
{
    SpaceCameraMap::iterator it = m_spaceCameraMap.find(space->id());
    if (it == m_spaceCameraMap.end())
    {
        it = m_spaceCameraMap.insert(std::make_pair(space->id(), CameraList())).first;
    }

    it->second.push_back(camera);
}

void RenderSystem::removeCamera(agte::Engine::SpacePtr space, CameraPtr camera)
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

void RenderSystem::addShaderAssets(agte::Engine::SpacePtr space, ShaderAssetPoolPtr assets)
{
    m_spaceShaderAssetsMap.insert(std::make_pair(space->id(), assets));
}

void RenderSystem::addMaterialAssets(agte::Engine::SpacePtr space, MaterialAssetPoolPtr assets)
{
    m_spaceMaterialAssetsMap.insert(std::make_pair(space->id(), assets));
}

void RenderSystem::addMeshAssets(agte::Engine::SpacePtr space, MeshAssetPoolPtr assets)
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
    typedef std::vector<Space::Entity> EntityList;
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
            Space::Entity& entity = it->second;

            // for each entity, get its transform and visual compoonents
            agtc::TransformComponent& transformComponent = transformComponents->componentForEntity(entity);
            agtm::Matrix4<float> modelViewMatrix = transformComponent.transform() * viewMatrix;

            agtc::Visual2dComponent& visual2dComponent = visual2dComponents->componentForEntity(entity);

            visual2dComponent.projectionMatrix(projectionMatrix);
            visual2dComponent.modelViewMatrix(modelViewMatrix);
        }
*/

        GLint projectionMatrixLocation;
        GLint viewMatrixLocation;

        size_t prevShaderId = 0;
        size_t currShaderId = 0;
        agtg::ShaderProgram* shader = nullptr;

        size_t prevMaterialId = 0;
        size_t currMaterialId = 0;
        agta::Material* material = nullptr;

        size_t prevMeshId = 0;
        size_t currMeshId = 0;
        agta::Mesh* mesh = nullptr;

        std::vector<agtm::Vector2<float> > texOffsets;
        std::vector<agtm::Matrix4<float> > modelMatrices;

        Space::EntityView::Iterator it = entityView.begin();
        Space::EntityView::Iterator end = entityView.end();
        for (; it != end; ++it) {
            agtc::Visual2dComponent& visual = it->get<agtc::Visual2dComponent>();

            // Update the shader to use for drawing
            currShaderId = visual.shaderId();
            if (!shader || currShaderId != prevShaderId) {
                if (shader)
                {
                    shader->unbind();
                }

                shader = &(shaderAssets->assetForId(currShaderId));

                prevShaderId = currShaderId;
                shader->bind();

                projectionMatrixLocation = shader->getUniformLocation("projectionMatrix");
                viewMatrixLocation = shader->getUniformLocation("viewMatrix");

                shader->bindUniform(projectionMatrixLocation, projectionMatrix);
                shader->bindUniform(viewMatrixLocation, viewMatrix);
            }

            // Update the Material used for drawing
            currMaterialId = visual.materialId();
            if (!material || currMaterialId != prevMaterialId) {
                if (material) {
                    material->unbind();
                }
    
                material = &(materialAssets->assetForId(currMaterialId));
                prevMaterialId = currMaterialId;
                material->bind(0);
            }

            // Update the Mesh used for drawing, sending the previous Mesh
            // to the GPU if it exists
            currMeshId = visual.meshId();
            if (!mesh || currMeshId != prevMeshId) {
                if (mesh) {
                    mesh->texOffsets(texOffsets);
                    mesh->modelMatrices(modelMatrices);
                    mesh->bind(*shader);
                    mesh->drawInstanced();
                    mesh->unbind();

                    texOffsets.clear();
                    modelMatrices.clear();
                }

                mesh = &(meshAssets->assetForId(currMeshId));
                prevMeshId = currMeshId;
            }

            agtc::TransformComponent& transform = it->get<agtc::TransformComponent>();
            modelMatrices.push_back(transform.transform());

            texOffsets.push_back(visual.spriteOffset());
        }

        if (mesh) {
            mesh->texOffsets(texOffsets);
            mesh->modelMatrices(modelMatrices);
            mesh->bind(*shader);
            mesh->drawInstanced();
            mesh->unbind();

            texOffsets.clear();
            modelMatrices.clear();
        }

        if (material) {
            material->unbind();
        }

        if (shader) {
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
