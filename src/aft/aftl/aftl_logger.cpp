#include <aftl_logger.h>
#include <aftthr_scopedlock.h>

namespace aftl {

aftthr::Mutex s_mutex;

Logger* Logger::m_instance = nullptr;

Logger& Logger::instance()
{
    if (!m_instance)
    {
        aftthr::ScopedLock<aftthr::Mutex> l(s_mutex);
        if (!m_instance)
        {
            m_instance = new Logger();
        }
    }

    return *m_instance;
}

Logger::Logger()
: m_level(LogLevel_INFO)
{
}

Logger::~Logger()
{
}

void Logger::addObserver(Logger::LogObserverPtr observer)
{
    aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);
    m_observers.push_back(observer);
}

void Logger::removeObserver(Logger::LogObserverPtr observer)
{
    aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);
    for (std::vector<LogObserverPtr>::iterator it = m_observers.begin(), end = m_observers.end(); it != end; ++it)
    {
        if (*it == observer)
        {
            m_observers.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel level, aftt::DatetimeTz const& timestamp, std::stringstream const& message)
{
    aftthr::ScopedLock<aftthr::Mutex> l(m_mutex);
    for (std::vector<LogObserverPtr>::iterator it = m_observers.begin(), end = m_observers.end(); it != end; ++it)
    {
        (*it)->log(level, timestamp, message);
    }
}

} // namespace
