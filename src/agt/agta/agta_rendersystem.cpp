#include <agta_rendersystem.h>
#include <agta_platform.h>
#include <agtg_renderingcontext.h>
#include <agtg_gl.h>

namespace agta {

RenderSystem::RenderSystem(int updatePriority)
: agta::System(updatePriority)
{}

RenderSystem::~RenderSystem()
{}

void RenderSystem::doPreUpdate(agta::Engine::Context& context)
{
}

void RenderSystem::doUpdate(agta::Engine::Context& context)
{
    agtg::RenderingContext& renderingContext = context.platform()->glWindow()->context();

    renderingContext.preRender();

    glClearColor(0.9f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // initialize the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // get the list of renderable entities

    // sort by render states (should this already be sorted?)

    // for each render state

        // set the render state

        // for each entity in the render state

            // get the entity transform

            // get the entity renderable

            // apply the transform

            // draw the renderable

    renderingContext.postRender();
}

void RenderSystem::doPostUpdate(agta::Engine::Context& context)
{
}

} // namespace
