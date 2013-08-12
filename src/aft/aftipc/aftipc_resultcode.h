#ifndef INCLUDED_AEGIS_AFTIPC_RESULTCODE_H
#define INCLUDED_AEGIS_AFTIPC_RESULTCODE_H

#include <iosfwd>

namespace aftipc {

enum ResultCode {
    ResultCode_SUCCESS,
    ResultCode_ACCESS_DENIED,
    ResultCode_NON_EXISTENT_IO,
    ResultCode_ALREADY_EXISTS,
    ResultCode_BAD_ADDRESS,
    ResultCode_BAD_FILE,
    ResultCode_INVALID_ARGUMENT,
    ResultCode_NO_DEVICE,
    ResultCode_NO_PERMISSION,
    ResultCode_NO_SPACE,
    ResultCode_NO_SUCH_IDENTIFIER,
    ResultCode_TOO_MANY_OPEN_FILES,
    ResultCode_OUT_OF_MEMORY,
    ResultCode_OVERFLOW,
    ResultCode_UNKNOWN
};

struct ResultUtil
{
    static ResultCode fromErrno(int errnoValue);
};

std::ostream& operator<<(std::ostream& os, ResultCode resultCode);

} // namespace

#endif // INCLUDED
