#include <aftu_exception.h>

namespace aegis {
namespace aftu {

Exception::Exception()
{}

Exception::Exception(std::string const& message)
: m_message(message)
{}

Exception::~Exception() throw()
{}

char const* Exception::what() const throw()
{
    return m_message.c_str();
}

} // namespace
} // namespace
