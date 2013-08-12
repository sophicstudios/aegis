#include <actp_conditionresult.h>
#include <iostream>

namespace actp {

std::ostream& operator<<(std::ostream& os, ConditionResult const& result)
{
    switch (result) {
        case ConditionResult_OK:
            os << "ConditionResult_OK";
            break;
        case ConditionResult_INVALID_MUTEX:
            os << "ConditionResult_INVALID_MUTEX";
            break;
        case ConditionResult_UNKNOWN:
        default:
            os << "ConditionResult_UNKNOWN";
            break;
    }
    
    return os;
}

} // namespace
