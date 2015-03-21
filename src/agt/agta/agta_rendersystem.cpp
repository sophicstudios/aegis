#include <agta_rendersystem.h>

namespace agta {

RenderSystem::RenderSystem(int updatePriority)
: agta::System(updatePriority)
{}

RenderSystem::~RenderSystem()
{}

void RenderSystem::update()
{
    // get the list of renderable entities

    // sort by render states (should this already be sorted?)

    // for each render state

        // set the render state

        // for each entity in the render state

            // get the entity transform

            // get the entity renderable

            // apply the transform

            // draw the renderable
}

} // namespace
