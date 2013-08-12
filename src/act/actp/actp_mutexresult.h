#ifndef INCLUDE_AEGIS_ACTP_MUTEXRESULT_H
#define INCLUDE_AEGIS_ACTP_MUTEXRESULT_H

#include <iosfwd>

namespace actp {

enum MutexResult {
    MutexResult_OK,
    MutexResult_NOT_LOCK_OWNER,
    MutexResult_WAIT_ABANDONED,
    MutexResult_UNKNOWN
};

std::ostream& operator<<(std::ostream& os, MutexResult const& result);

} // namespace

#endif // INCLUDE
