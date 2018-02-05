#ifndef INCLUDED_AEGIS_AFTL_LOGLEVEL_H
#define INCLUDED_AEGIS_AFTL_LOGLEVEL_H

namespace aftl {

enum LogLevel {
    LogLevel_OFF = 0,
    LogLevel_ERROR = 1,
    LogLevel_WARN = 2,
    LogLevel_INFO = 3,
    LogLevel_DEBUG = 4,
    LogLevel_TRACE = 5
};

} // namespace

#endif // INCLUDED
