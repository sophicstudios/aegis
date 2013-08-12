#include <aftipc_resultcode.h>
#include <ostream>
#include <cerrno>

namespace aftipc {

ResultCode ResultUtil::fromErrno(int errnoValue)
{
    switch (errnoValue)
    {
    case 0: return ResultCode_SUCCESS;
    case EACCES: return ResultCode_ACCESS_DENIED;
    case EBADF: return ResultCode_BAD_FILE;
    case EEXIST: return ResultCode_ALREADY_EXISTS;
    case EFAULT: return ResultCode_BAD_ADDRESS;
    case EINVAL: return ResultCode_INVALID_ARGUMENT;
    case EMFILE: return ResultCode_TOO_MANY_OPEN_FILES;
    case ENODEV: return ResultCode_NO_DEVICE;
    case ENOENT: return ResultCode_NO_SUCH_IDENTIFIER;
    case ENOMEM: return ResultCode_OUT_OF_MEMORY;
    case ENOSPC: return ResultCode_NO_SPACE;
    case ENXIO: return ResultCode_NON_EXISTENT_IO;
    case EOVERFLOW: return ResultCode_OVERFLOW;
    case EPERM: return ResultCode_NO_PERMISSION;
    default: return ResultCode_UNKNOWN;
    }
}

std::ostream& operator<<(std::ostream& os, ResultCode resultCode)
{
    switch (resultCode) {
    case ResultCode_SUCCESS: os << "SUCCESS"; break;
    case ResultCode_ACCESS_DENIED: os << "ACCESS_DENIED"; break;
    case ResultCode_ALREADY_EXISTS: os << "ALREADY_EXISTS"; break;
    case ResultCode_BAD_ADDRESS: os << "BAD_ADDRESS"; break;
    case ResultCode_BAD_FILE: os << "BAD_FILE"; break;
    case ResultCode_INVALID_ARGUMENT: os << "INVALID_ARGUMENTS"; break;
    case ResultCode_NO_DEVICE: os << "NO_DEVICE"; break;
    case ResultCode_NO_PERMISSION: os << "NO_PERMISSION"; break;
    case ResultCode_NO_SPACE: os << "NO_SPACE"; break;
    case ResultCode_NO_SUCH_IDENTIFIER: os << "NO_SUCH_IDENTIFIER"; break;
    case ResultCode_NON_EXISTENT_IO: os << "NON_EXISTENT_IO"; break;
    case ResultCode_TOO_MANY_OPEN_FILES: os << "TOO_MANY_OPEN_FILES"; break;
    case ResultCode_OUT_OF_MEMORY: os << "OUT_OF_MEMORY"; break;
    case ResultCode_OVERFLOW: os << "OVERFLOW"; break;
    default: os << "UNKNOWN"; break;
    }
    
    return os;
}

} // namespace
