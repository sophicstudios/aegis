#include <agta_system.h>

namespace agta {

System::System(int updatePriority)
: m_priority(updatePriority)
{}

System::~System()
{}

void System::preUpdate(agta::Engine::Context& context)
{
    doPreUpdate(context);
}

void System::update(agta::Engine::Context& context)
{
    doUpdate(context);
}

void System::postUpdate(agta::Engine::Context& context)
{
    doPostUpdate(context);
}

void System::updatePriority(int priority)
{
    m_priority = priority;
}

int System::updatePriority() const
{
    return m_priority;
}

} // namespace
