#include <afts_errorutil.h>
#include <afts_compiler.h>
#include <sstream>
#include <cstring>

namespace aegis {
namespace afts {

namespace {
const unsigned short MAX_ERROR_SIZE = 512;
}

#if defined(AFTS_COMPILER_MSVC)

std::string ErrorUtil::translateErrno(int errnum)
{
    char buffer[MAX_ERROR_SIZE];

    errno_t result = strerror_s(buffer, MAX_ERROR_SIZE, errnum);

    if (result != 0) {
        std::stringstream s;

        s << "strerror_s failed ["
            << " error: " << result
            << " ]";

        return s.str();
    }

    return std::string(buffer);
}

#else

std::string ErrorUtil::translateErrno(int errnum)
{
    char buffer[MAX_ERROR_SIZE];

    int result = strerror_r(errnum, buffer, MAX_ERROR_SIZE);
    if (result != 0) {
        std::stringstream s;
        
        s << "strerror_r failed ["
            << " result: " << result
            << " ]";
        
        return s.str();
    }
    
    return std::string(buffer);
}

#endif // AFTS_COMPILER

} // namespace
} // namespace
