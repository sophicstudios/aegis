#include <agte_system.h>

namespace agte {

System::System(int updatePriority)
: m_priority(updatePriority)
{}

System::~System()
{}

void System::preUpdate(agte::Engine::Context& context)
{
    doPreUpdate(context);
}

void System::update(agte::Engine::SpacePtr space, agte::Engine::Context& context)
{
    doUpdate(space, context);
}

void System::postUpdate(agte::Engine::Context& context)
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
