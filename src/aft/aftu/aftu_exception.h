#ifndef INCLUDED_AEGIS_AFTU_EXCEPTION_H
#define INCLUDED_AEGIS_AFTU_EXCEPTION_H

#include <exception>
#include <sstream>
#include <string>

#define AFTU_DECLARE_EXCEPTION(Name)                                     \
    struct ExceptionType##Name                                          \
    {                                                                   \
        static const char* const name() { return #Name; }               \
    };                                                                  \
    typedef aftu::TypedException<ExceptionType##Name> Name;

namespace aegis {
namespace aftu {

/**
 * This base class for exceptions, which also derives from std::exception
 * to allow for standard exception handling, adds a few useful features
 * beyond what the std::exception class provides. It provides the ability
 * to specify a string message during construction as well as to append
 * more data to the message with a stream operator.
 *
 * @code
 * try
 * {
 *     throw Exception("MyException") << " data ["
 *         << " int: " << 5
 *         << " float: " << 6.1f
 *         << " ]";
 * }
 * catch (std::exception const& e)
 * {
 *     // prints:
 *     // "MyException data [ int: 5 float: 6.1 ]"
 *     std::cout << e.what() << std::endl;
 * }
 * @endcode
 */ 
class Exception
: public std::exception
{
public:
    /**
     * Constructs a default Exception object without any
     * message string
     */
    Exception();

    /**
     * Constructs an Exception object with the specified
     * string as a message
     */
    Exception(std::string const& message);
    
    /**
     * Destructor
     */
    virtual ~Exception() throw();

    /**
     * Following the interface of the std exception class, returns a const char
     * pointer to the stored message string.
     */
    virtual char const* what() const throw();

    /**
     * Allows a user to append values to the message string with an
     * easy to use ostream interface
     */
    template<typename T>
    Exception& operator<<(T const& value);

private:
    std::string m_message;
};

////////////////////////////////////////////////////////////
// IMPLEMENTATION
////////////////////////////////////////////////////////////
template<typename T>
Exception& Exception::operator<<(T const& value)
{
    std::stringstream s;
    s << value;
    m_message += s.str();

    return *this;
}

} // namespace
} // namespace

#endif // INCLUDED
