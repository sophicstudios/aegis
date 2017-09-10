#include <agte_engine.h>
#include <agte_platform.h>
#include <agte_system.h>
#include <actp_scopedlock.h>
#include <aftu_exception.h>
#include <functional>
#include <iostream>
#include <cassert>

namespace agte {

Engine::Context::Context(Engine::PlatformPtr platform, actp::Mutex& mutex, actp::Condition& condition)
: m_shouldUpdate(false),
  m_platform(platform),
  m_mutex(mutex),
  m_condition(condition)
{
}

Engine::Context::~Context()
{
}

void Engine::Context::resetShouldUpdate()
{
    std::cout << "resetShouldUpdate" << std::endl;

    m_shouldUpdate = false;
}

void Engine::Context::flagUpdate()
{
    std::cout << "flagUpdate" << std::endl;

    if (m_shouldUpdate)
    {
        return;
    }
    
    m_shouldUpdate = true;

    m_mutex.lock();
    m_condition.signalOne();
    m_mutex.unlock();
}

bool Engine::Context::shouldUpdate() const
{
    std::cout << "shouldUpdate: " << m_shouldUpdate << std::endl;
    return m_shouldUpdate;
}

Engine::PlatformPtr Engine::Context::platform() const
{
    return m_platform;
}

Engine::Engine(PlatformPtr platform)
: m_running(true),
  m_context(platform, m_mutex, m_condition),
  m_platform(platform)
{
    std::cout << "Engine::Engine starting thread" << std::endl;
    m_thread = std::make_shared<actp::Thread>(std::bind(&Engine::threadFunc, this));
}

Engine::~Engine()
{
    m_running = false;

    m_mutex.lock();
    m_condition.signalOne();
    m_mutex.unlock();

    std::cout << "Engine::~Engine joining thread" << std::endl;
    m_thread->join();
}

void Engine::addSpace(std::string const& id, SpacePtr space)
{
    SpaceMap::iterator it = m_spaceMap.find(id);
    if (it != m_spaceMap.end())
    {
        // space already exists with this id!
        throw aftu::Exception("Space already exists with id: ") << id;
    }

    // add space to Space list
    m_spaces.push_back(space);
    m_spaceMap.insert(std::make_pair(id, space));
}

void Engine::removeSpace(std::string const& id)
{
    SpaceMap::size_type count = m_spaceMap.erase(id);
    assert(count != 0);
}

void Engine::registerSystem(SystemPtr system)
{
    bool inserted = false;

    SystemList::iterator it = m_systems.begin(), end = m_systems.end();
    while (it != end)
    {
        if ((*it)->updatePriority() > system->updatePriority())
        {
            m_systems.insert(it, system);
            inserted = true;
        }

        ++it;
    }

    if (!inserted)
    {
        m_systems.push_back(system);
    }
}

void Engine::update()
{
    m_context.flagUpdate();
}

void Engine::threadFunc()
{
    actp::ScopedLock<actp::Mutex> lock(m_mutex);

    while (true)
    {
        std::cout << "Engine::threadFunc waiting..." << std::endl;
        m_condition.wait(m_mutex);
        std::cout << "Engine::threadFunc running" << std::endl;

        if (!m_running)
        {
            std::cout << "Engine::threadFunc done" << std::endl;
            break;
        }

        SpaceList::iterator spaceIter, spaceEnd = m_spaces.end();

        for (spaceIter = m_spaces.begin(); spaceIter != spaceEnd; ++spaceIter)
        {
            SystemList::iterator systemIter = m_systems.begin();
            SystemList::iterator systemEnd = m_systems.end();

            for (; systemIter != systemEnd; ++systemIter)
            {
                (*systemIter)->update(*spaceIter, m_context);
            }
        }

        m_context.resetShouldUpdate();
    }
}

} // namespace
