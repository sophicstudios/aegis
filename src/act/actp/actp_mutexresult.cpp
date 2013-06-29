#include <actp_mutexresult.h>
#include <ostream>

namespace aegis {
namespace actp {

std::ostream& operator<<(std::ostream& os, MutexResult const& result)
{
    switch (result) {
        case MutexResult_OK:
            os << "MutexResult_OK";
            break;
        case MutexResult_NOT_LOCK_OWNER:
            os << "MutexResult_NOT_LOCK_OWNER";
            break;
        case MutexResult_WAIT_ABANDONED:
            os << "MutexResult_WAIT_ABANDONED";
            break;
        case MutexResult_UNKNOWN:
        default:
            os << "MutexResult_UNKNOWN";
            break;
    }
    
    return os;
}

} // namespace
} // namespace
