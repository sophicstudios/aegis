#ifndef INCLUDE_AEGIS_AFTU_TYPEDBUFFER_H
#define INCLUDE_AEGIS_AFTU_TYPEDBUFFER_H

#include <boost/cstdint.hpp>

namespace aegis {
namespace aftu {

template<typename T>
class TypedBuffer
{
public:
    TypedBuffer();

    TypedBuffer(T const& value);

    ~TypedBuffer();

    boost::uint8_t* data();
    
private:
    boost::uint8_t m_buffer[sizeof(T)];
};

template<typename T>
TypedBuffer<T>::TypedBuffer()
{}

template<typename T>
TypedBuffer<T>::TypedBuffer(T const& value)
{
    memcpy(m_buffer, &value, sizeof(T));
}

template<typename T>
TypedBuffer<T>::~TypedBuffer()
{}

template<typename T>
boost::uint8_t* TypedBuffer<T>::data()
{
    return m_buffer;
}

} // namespace
} // namespace

#endif // INCLUDE
