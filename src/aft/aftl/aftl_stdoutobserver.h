#ifndef INCLUDED_AEGIS_AFTL_STDOUTOBSERVER_H
#define INCLUDED_AEGIS_AFTL_STDOUTOBSERVER_H

#include <aftl_logobserver.h>
#include <aftt_datetimetz.h>
#include <sstream>

namespace aftl {

class StdoutObserver : public LogObserver
{
public:
    StdoutObserver();

    virtual ~StdoutObserver();

    virtual void log(LogLevel level, aftt::DatetimeTz const& timestamp, std::stringstream const& message);
};

} // namespace

#endif // INCLUDED
