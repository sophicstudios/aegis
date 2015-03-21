#include <agta_engine.h>
#include <agta_system.h>
#include <actp_scopedlock.h>
#include <functional>

namespace agta {

Engine::Engine(PlatformPtr platform)
: m_platform(platform),
  m_running(false)
{
    agta::DisplayTimer::DisplayTimerCallback callback =
        std::bind(&Engine::onDisplayTimer, this);

    m_platform->displayTimer()->registerDisplayTimerCallback(<#const DisplayTimerCallback &callback#>);
}

Engine::~Engine()
{
    stop();
}

void Engine::registerSystem(std::shared_ptr<agta::System> system)
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    Systems::iterator it = m_systems.begin(), end = m_systems.end();
    while (it != end) {
        if ((*it)->updatePriority() > system->updatePriority()) {
            m_systems.insert(it, system);
        }
    }
}

void Engine::run()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    if (m_running) {
        return;
    }

    m_running = true;
    m_platform->displayTimer()->start();
}

void Engine::stop()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    if (!m_running) {
        return;
    }

    m_running = false;
    m_platform->displayTimer()->stop();
}

void Engine::step()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    if (m_running) {
        return;
    }

    m_shouldStep = true;
    m_platform->displayTimer()->start();
}

void Engine::onDisplayTimer()
{
    if (!m_running || !m_shouldStep) {
        return;
    }

    m_shouldStep = false;

    Systems::iterator it = m_systems.begin();
    System::iterator end = m_systems.end();

    while (it != end) {
        (*it)->update(*this);
        ++it;
    }

    if (!m_running || !m_shouldStep) {
        m_platform->displayTimer()->stop();
    }
}

} // namespace
