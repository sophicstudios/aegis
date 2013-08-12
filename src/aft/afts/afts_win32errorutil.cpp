#include <afts_win32errorutil.h>
#include <sstream>

#if defined(AFTS_OS_WIN32)

namespace afts {

std::string Win32ErrorUtil::translateSystemError(DWORD errorCode)
{
    LPSTR buffer = NULL;
    DWORD bufferSize = 1;

    DWORD result = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,     // Assume system error and allocate buffer
        NULL,                                   // No source
        errorCode,                              // errorCode
        0,                                      // Default language
        buffer,                                // buffer
        bufferSize,                             // minimum buffer size to allocate
        NULL);                                  // No va_list
    
    // If the FormatMessage failed, include information on that error
    // in the returned error message string.
    if (result == 0)
    {
        std::stringstream s;
        s << "FormatMessage failed! GetLastError() = " << GetLastError()
            << " (Original errorCode: " << errorCode << ")";
        return s.str();
    }
    
    // copy the error message buffer from FormatMessage into an STL string.
    std::string errorMessage(buffer);

    // Free the original buffer. If this fails, include information on that
    // failure in the returned error message string.
    if (LocalFree(buffer) != NULL)
    {
        std::stringstream s;
        s << "FormatMessage succeeded, but LocalFree failed! GetLastError() = " << GetLastError()
            << " (Original Error: " << buffer << ")";
        return s.str();
    }
    
    return errorMessage;
}

} // namespace

#endif // AFTS_OS
