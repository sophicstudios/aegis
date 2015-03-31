#ifndef INCLUDED_AGTA_RENDERSYSTEM_H
#define INCLUDED_AGTA_RENDERSYSTEM_H

#include <agta_system.h>

namespace agta {

class RenderSystem : public System
{
public:
    RenderSystem(int updatePriority = 0);

    virtual ~RenderSystem();

protected:
    virtual void doPreUpdate(agta::Engine::Context& context);

    virtual void doUpdate(agta::Engine::Context& context);

    virtual void doPostUpdate(agta::Engine::Context& context);

private:

};

} // namespace

#endif // INCLUDED
