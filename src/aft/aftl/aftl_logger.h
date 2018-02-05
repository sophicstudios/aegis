#ifndef INCLUDED_AEGIS_AFTL_LOGGER_H
#define INCLUDED_AEGIS_AFTL_LOGGER_H

#include <aftl_loglevel.h>
#include <aftl_logobserver.h>
#include <aftt_datetimetz.h>
#include <aftt_systemtime.h>
#include <aftthr_mutex.h>
#include <string>
#include <vector>
#include <sstream>

namespace aftl {

#define AFTL_LOG(level) { \
    aftl::Logger& l = aftl::Logger::instance(); \
    if ((level) <= l.logLevel()) { \
        aftl::LogLevel lev = (level); \
        aftt::DatetimeTz d = aftt::SystemTime::nowAsDatetimeLocal(); \
        std::stringstream s; s 

#define AFTL_LOG_END \
        ""; l.log(lev, d, s); \
    } \
}

#define AFTL_LOG_TRACE AFTL_LOG(aftl::LogLevel_TRACE)
#define AFTL_LOG_DEBUG AFTL_LOG(aftl::LogLevel_DEBUG)
#define AFTL_LOG_INFO AFTL_LOG(aftl::LogLevel_INFO)
#define AFTL_LOG_WARN AFTL_LOG(aftl::LogLevel_WARN)
#define AFTL_LOG_ERROR AFTL_LOG(aftl::LogLevel_ERROR)

class Logger
{
public:
    typedef std::shared_ptr<LogObserver> LogObserverPtr;

    static Logger& instance();

    ~Logger();

    void addObserver(LogObserverPtr observer);

    void removeObserver(LogObserverPtr observer);

    void log(LogLevel level, aftt::DatetimeTz const& timestamp, std::stringstream const& message);

    void logLevel(LogLevel level);

    LogLevel logLevel() const;

private:
    Logger();
    Logger(Logger const&);
    Logger& operator=(Logger const&);

    static Logger* m_instance;
    LogLevel m_level;
    std::vector<LogObserverPtr> m_observers;
    aftthr::Mutex m_mutex;
};

inline LogLevel Logger::logLevel() const
{
    return m_level;
}

inline void Logger::logLevel(LogLevel level)
{
    m_level = level;
}

} // namespace

#endif // INCLUDED
