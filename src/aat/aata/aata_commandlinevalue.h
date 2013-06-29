#ifndef INCLUDE_AEGIS_AATA_COMMANDLINEVALUE_H
#define INCLUDE_AEGIS_AATA_COMMANDLINEVALUE_H

#include <aftt_date.h>
#include <aftt_time.h>
#include <aftt_datetime.h>
#include <aftu_nullable.h>
#include <boost/lexical_cast.hpp>

namespace aegis {
namespace aata {

class CommandLineValue
{
public:
    enum Type
    {
        Type_CHAR,
        Type_INT,
        Type_DOUBLE,
        Type_STRING,
        Type_DATE,
        Type_TIME,
        Type_DATETIME
    };
    
    typedef boost::function<bool (char)> CharValidationFunc;
    typedef boost::function<bool (int)> IntValidationFunc;
    typedef boost::function<bool (double)> DoubleValidationFunc;
    typedef boost::function<bool (std::string const&)> StringValidationFunc;
    typedef boost::function<bool (aftt::Date const&)> DateValidationFunc;
    typedef boost::function<bool (aftt::Time const&)> TimeValidationFunc;
    typedef boost::function<bool (aftt::Datetime const&)> DatetimeValidationFunc;

    CommandLineValue(Type type);

    CommandLineValue(char* linkedVariable, CharValidationFunc const& func = CharValidationFunc());

    CommandLineValue(int* linkedVariable, IntValidationFunc const& func = IntValidationFunc());

    CommandLineValue(double* linkedVariable, DoubleValidationFunc const& func = DoubleValidationFunc());
    
    CommandLineValue(std::string* linkedVariable, StringValidationFunc const& func = StringValidationFunc());
    
    bool parse(std::string const& input); 
    
    template<typename T>
    bool getValue(T& output) const;
    
private:
    T* m_linkedValue;
    aftu::Nullable<T> m_defaultValue;
    ValidationFunc m_validationFunc;
};

template<typename T>
CommandLineValue::CommandLineValue(T const& defaultValue)
: m_defaultValue(defaultValue), m_value(&m_defaultValue)
{}

template<typename T>
CommandLineValue::CommandLineValue(T* valuePtr, ValidationFunc const& validationFunc)
: m_valuePtr(valuePtr), m_validationFunc(func)
{
    if (!m_valuePtr) {
        throw std::exception("CommandLineValue: null valuePtr given");
    }
}

template<typename T>
CommandLineValue::CommandLineValue(T* valuePtr, T const& defaultValue, ValidationFunc const& validationFunc)
: m_valuePtr(valuePtr), m_defaultValue(defaultValue), m_validationFunc(validationFunc)
{
    if (!m_valuePtr) {
        throw std::exception("CommandLineValue: null valuePtr given");
    }
}

template<typename T>
void validateAndSet(T const& value)
{
    if (!m_validationFunc || m_validationFunc(value)) {
        *m_valuePtr = value;
    }
}

template<typename T>
bool get(T& value) const
{
    return *m_valuePtr;
}

} // namespace
} // namespace

#endif // INCLUDE
