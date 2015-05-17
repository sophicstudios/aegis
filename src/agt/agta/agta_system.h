#ifndef INCLUDED_AGTA_SYSTEM_H
#define INCLUDED_AGTA_SYSTEM_H

#include <agta_engine.h>

namespace agta {

class System
{
public:
    System(int updatePriority = 0);

    virtual ~System();

    void preUpdate(agta::Engine::Context& context);

    void update(agta::Engine::SpacePtr space, agta::Engine::Context& context);

    void postUpdate(agta::Engine::Context& context);

    void updatePriority(int priority);

    int updatePriority() const;

protected:
    virtual void doPreUpdate(agta::Engine::Context& context) = 0;
    virtual void doUpdate(agta::Engine::SpacePtr space, agta::Engine::Context& context) = 0;
    virtual void doPostUpdate(agta::Engine::Context& context) = 0;

private:
    System();

    int m_priority;
};

} // namespace

#endif // INCLUDED
