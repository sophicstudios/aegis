#ifndef INCLUDED_AGTA_RENDERSYSTEM_H
#define INCLUDED_AGTA_RENDERSYSTEM_H

#include <agta_system.h>
#include <list>
#include <map>
#include <memory>

namespace agta {

class RenderSystem : public System
{
public:
    RenderSystem();

    virtual ~RenderSystem();

    virtual void update();

private:
};

} // namespace

#endif // INCLUDED
