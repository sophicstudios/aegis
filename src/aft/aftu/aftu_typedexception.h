#ifndef INCLUDED_AEGIS_AFTU_TYPEDEXCEPTION_H
#define INCLUDED_AEGIS_AFTU_TYPEDEXCEPTION_H

#include <aftu_exception.h>
#include <string>

namespace aftu {

/**
 * Provides a way to easily declare new exceptions that follow a standard
 * interface within the library and applications
 *
 * To declare a new exception type, you would add this line:
 *
 * @code
 * AFTU_DECLARE_EXCEPTION(MyException)
 * @endcode
 *
 * Then you would be able to throw and catch the exception like this:
 *
 * @code
 * try
 * {
 *   throw MyException("My error message");
 * }
 * catch (MyException const& e) // or catch (std::exception const& e)
 * {
 *   // prints "MyException: My error message"
 *   std::cout << e.what() << std::endl;
 * }
 * @endcode
 */
template<typename T>
class TypedException
    : public aftu::Exception
{
public:
    TypedException();

    TypedException(const std::string& message);

    virtual ~TypedException() throw();
};

template<typename T>
TypedException<T>::TypedException()
: aftu::Exception(T::name())
{}

template<typename T>
TypedException<T>::TypedException(const std::string& message)
: aftu::Exception(std::string(T::name()).append(": ").append(message))
{}

template<typename T>
TypedException<T>::~TypedException() throw()
{}

} // namespace

#endif // INCLUDED
