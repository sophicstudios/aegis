#include <agta_engine.h>
#include <agta_displaytimer.h>
#include <agta_platform.h>
#include <agta_system.h>
#include <actp_scopedlock.h>
#include <functional>

namespace agta {

Engine::Context::Context(Engine::PlatformPtr platform)
: m_shouldUpdate(false),
  m_platform(platform)
{
}

Engine::Context::~Context()
{
}

void Engine::Context::resetShouldUpdate()
{
    m_shouldUpdate = false;
}

void Engine::Context::flagUpdate()
{
    m_shouldUpdate = true;
}

bool Engine::Context::shouldUpdate() const
{
    return m_shouldUpdate;
}

Engine::PlatformPtr Engine::Context::platform() const
{
    return m_platform;
}

Engine::Engine(PlatformPtr platform)
: m_context(platform),
  m_platform(platform),
  m_running(false)
{
    agta::DisplayTimer::Callback callback = std::bind(&Engine::onDisplayTimer, this);

    m_platform->glWindow()->displayTimer().registerCallback(callback);
}

Engine::~Engine()
{
    stop();
}

void Engine::registerSystem(std::shared_ptr<agta::System> system)
{
    bool inserted = false;
    SystemList::iterator it = m_systems.begin(), end = m_systems.end();
    while (it != end) {
        if ((*it)->updatePriority() > system->updatePriority()) {
            m_systems.insert(it, system);
            inserted = true;
        }

        ++it;
    }

    if (!inserted) {
        m_systems.push_back(system);
    }
}

void Engine::run()
{
    if (m_running) {
        return;
    }

    m_running = true;
    m_platform->glWindow()->displayTimer().start();
}

void Engine::stop()
{
    if (!m_running) {
        return;
    }

    m_running = false;
    m_platform->glWindow()->displayTimer().stop();
}

void Engine::step()
{
    if (m_running) {
        return;
    }

    m_context.flagUpdate();

    m_platform->glWindow()->displayTimer().start();
}

void Engine::onDisplayTimer()
{
    if (!m_running && !m_context.shouldUpdate()) {
        return;
    }

    m_context.resetShouldUpdate();

    SystemList::iterator it = m_systems.begin();
    SystemList::iterator end = m_systems.end();

    while (it != end) {
        (*it)->update(m_context);
        ++it;
    }

    if (!m_running || !m_context.shouldUpdate()) {
        m_platform->glWindow()->displayTimer().stop();
    }
}

} // namespace
