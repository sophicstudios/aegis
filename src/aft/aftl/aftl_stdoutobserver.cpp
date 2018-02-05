#include <aftl_stdoutobserver.h>
#include <iostream>

namespace aftl {

namespace {

}

StdoutObserver::StdoutObserver()
{
}

StdoutObserver::~StdoutObserver()
{
}

void StdoutObserver::log(aftl::LogLevel level, aftt::DatetimeTz const& timestamp, std::stringstream const& message)
{
    switch (level)
    {
        case LogLevel_ERROR:
            std::cerr << timestamp << "|ERROR|" << message.str() << std::endl;
            break;
        case LogLevel_WARN:
            std::cerr << timestamp << "|WARN|" << message.str() << std::endl;
            break;
        case LogLevel_INFO:
            std::cout << timestamp << "|INFO|" << message.str() << std::endl;
            break;
        case LogLevel_DEBUG:
            std::cout << timestamp << "|DEBUG|" << message.str() << std::endl;
            break;
        case LogLevel_TRACE:
            std::cout << timestamp << "|TRACE|" << message.str() << std::endl;
            break;
        case LogLevel_OFF:
        default:
            break;
    }
}

} // namespace

