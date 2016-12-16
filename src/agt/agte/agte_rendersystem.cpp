#include <agte_rendersystem.h>
#include <agte_platform.h>
#include <agta_sprite2dmaterial.h>
#include <agtc_transformcomponent.h>
#include <agtc_visual2dcomponent.h>
#include <agtr_image.h>
#include <agtr_imageloaderpng.h>
#include <agtg_renderingcontext.h>
#include <agtg_gl.h>
#include <actp_scopedlock.h>
#include <aftfs_filesystem.h>
#include <afth_uuid.h>
#include <aftu_url.h>
#include <iostream>
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
        std::cerr << "glError [" << context << "]: " << translateGLenum(error) << " (" << error << ")" << std::endl;
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

    //m_modelViewMatrixLoc = glGetUniformLocation(m_program, "modelViewMatrix");
    //m_projectionMatrixLoc = glGetUniformLocation(m_program, "projectionMatrix");
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

void RenderSystem::doPreUpdate(agte::Engine::Context& context)
{
}

void RenderSystem::doUpdate(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    std::cout << "RenderSystem::doUpdate" << std::endl;

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
    
    // update all the cameras
    CameraList::iterator cameraIter, cameraEnd = spaceCameraIter->second.end();
    for (cameraIter = spaceCameraIter->second.begin(); cameraIter != cameraEnd; ++cameraIter)
    {
        (*cameraIter)->update();
    }

    // get list of entities with visual and transform components
    Space::EntityView entityView = space->getEntitiesForComponents(m_componentSet);

    // Loop through the entities and sort them by visual component material. Using
    // a std::multimap gives us a weak ordering of entities by material id
    typedef std::multimap<afth::UUID, Entity> MaterialEntityMap;
    MaterialEntityMap materialEntityMap;

    Space::EntityView::Iterator it = entityView.begin();
    Space::EntityView::Iterator end = entityView.end();
    for (; it != end; ++it)
    {
        agtc::Visual2dComponent& visual2dComponent = visual2dComponents->componentForEntity(*it);
        std::shared_ptr<agta::Sprite2dMaterial> material = visual2dComponent.material();
        materialEntityMap.insert(std::make_pair(material->id(), *it));
    }

    for (cameraIter = spaceCameraIter->second.begin(); cameraIter != cameraEnd; ++cameraIter)
    {
        std::shared_ptr<agtg::RenderingContext> renderingContext = context.platform()->glView()->renderingContext();
        renderingContext->preRender();

        // set the viewport from the camera
        agtm::Rect<float> const& rect = (*cameraIter)->viewport();
        std::cout << "viewport: " << rect << std::endl;
        glViewport(rect.x(), rect.y(), rect.width(), rect.height());

        glClearColor(0.0f, 0.0f, .7f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glUseProgram(m_program);

        // set the projection matrix from the camera
        m_projectionMatrix = (*cameraIter)->projection();
        glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, m_projectionMatrix.arr());

        // Loop though material-entity map to iterate through all entities, sorted
        // by material, then draw each entity
        MaterialEntityMap::iterator it = materialEntityMap.begin();
        MaterialEntityMap::iterator end = materialEntityMap.end();
        afth::UUID prevMaterialId;
        for (; it != end; ++it)
        {
            Entity& entity = it->second;

            // for each entity, get its transform and visual compoonents
            agtc::TransformComponent& transformComponent = transformComponents->componentForEntity(entity);
            m_modelViewMatrix = transformComponent.transform() * (*cameraIter)->view();

            agtc::Visual2dComponent& visual2dComponent = visual2dComponents->componentForEntity(entity);

            // get the material
            std::shared_ptr<agta::Sprite2dMaterial> material = visual2dComponent.material();
            if (material->id() != prevMaterialId)
            {
                // bind the material if different than the previous
            }

            // get the mesh and bind the vertex array

            glUniformMatrix4fv(m_modelViewMatrixLoc, 1, GL_FALSE, m_modelViewMatrix.arr());

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        glUseProgram(0);

        renderingContext->postRender();
    }
}

void RenderSystem::doPostUpdate(agte::Engine::Context& context)
{
}

} // namespace
