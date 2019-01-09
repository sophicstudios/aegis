#include <agte_engine.h>
#include <agte_platform.h>
#include <agte_system.h>
#include <aftthr_scopedlock.h>
#include <aftu_exception.h>
#include <aftl_logger.h>
#include <functional>
#include <cassert>

namespace agte {

Engine::Context::Context(Engine::PlatformPtr platform, aftthr::Mutex& mutex, aftthr::Condition& condition)
: m_shouldUpdate(false),
  m_elapsedSeconds(0.0),
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
    AFTL_LOG_TRACE << "Engine::Context::resetShouldUpdate" << AFTL_LOG_END;

    m_shouldUpdate = false;
}

void Engine::Context::flagUpdate()
{
    AFTL_LOG_TRACE << "Engine::Context::flagUpdate" << AFTL_LOG_END;

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
    AFTL_LOG_TRACE << "Engine::Context::shouldUpdate: " << m_shouldUpdate << AFTL_LOG_END;
    return m_shouldUpdate;
}

Engine::PlatformPtr Engine::Context::platform() const
{
    return m_platform;
}

void Engine::Context::elapsedSeconds(double elapsedSeconds)
{
    m_elapsedSeconds = elapsedSeconds;
}

double Engine::Context::elapsedSeconds() const
{
    return m_elapsedSeconds;
}

Engine::Engine(PlatformPtr platform)
: m_running(true),
  m_context(platform, m_mutex, m_condition),
  m_platform(platform)
{
    AFTL_LOG_INFO << "Engine::Engine starting thread" << AFTL_LOG_END;
    m_thread = std::make_shared<aftthr::Thread>(std::bind(&Engine::threadFunc, this));
}

Engine::~Engine()
{
    m_running = false;

    m_mutex.lock();
    m_condition.signalOne();
    m_mutex.unlock();

    AFTL_LOG_INFO << "Engine::~Engine joining thread" << AFTL_LOG_END;
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
    m_spaceMap.erase(id);
}

void Engine::addSystem(SystemPtr system)
{
    bool inserted = false;

    SystemList::iterator it = m_systems.begin(), end = m_systems.end();
    while (!inserted && it != end)
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
    aftthr::ScopedLock<aftthr::Mutex> lock(m_mutex);

    m_prevTime = m_currTime = aftt::SystemTime::now();
    while (true)
    {
        AFTL_LOG_TRACE << "Engine::threadFunc waiting..." << AFTL_LOG_END;
        m_condition.wait(m_mutex);
        AFTL_LOG_TRACE << "Engine::threadFunc running" << AFTL_LOG_END;

        if (!m_running)
        {
            AFTL_LOG_INFO << "Engine::threadFunc done" << AFTL_LOG_END;
            break;
        }

        m_prevTime = m_currTime;
        m_currTime = aftt::SystemTime::now();
        aftt::DatetimeInterval elapsedTime = m_currTime - m_prevTime;
        m_context.elapsedSeconds(elapsedTime.totalSeconds());
        
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
