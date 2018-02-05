#ifndef INCLUDED_AEGIS_AFTL_LOGOBSERVER_H
#define INCLUDED_AEGIS_AFTL_LOGOBSERVER_H

#include <aftl_loglevel.h>
#include <aftt_datetimetz.h>
#include <string>

namespace aftl {

class LogObserver
{
public:
    LogObserver();

    virtual ~LogObserver() = 0;

    virtual void log(LogLevel level, aftt::DatetimeTz const& timestamp, std::stringstream const& message) = 0;
};

} // namespace

#endif // INCLUDED
