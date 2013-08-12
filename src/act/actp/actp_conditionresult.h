#ifndef INCLUDE_AEGIS_ACTP_CONDITIONRESULT_H
#define INCLUDE_AEGIS_ACTP_CONDITIONRESULT_H

#include <iosfwd>

namespace actp {

enum ConditionResult {
    ConditionResult_OK,
    ConditionResult_INVALID_MUTEX,
    ConditionResult_UNKNOWN
};

std::ostream& operator<<(std::ostream& os, ConditionResult const& result);

} // namespace

#endif // INCLUDE
