#ifndef INCLUDED_AEGIS_AGTM_SIZE2D_H
#define INCLUDED_AEGIS_AGTM_SIZE2D_H

#include <ostream>

namespace agtm {

template<typename T>
class Size2d
{
public:
    Size2d();
    
    Size2d(T const& width, T const& height);
    
    ~Size2d();
    
    T const& width() const;
    
    T const& height() const;
    
private:
    T m_width;
    T m_height;
};

template<typename T>
Size2d<T> make_size(T const& width, T const& height);

template<typename T>
std::ostream& operator<<(std::ostream& os, Size2d<T> const& size);

template<typename T>
Size2d<T>::Size2d()
: m_width(static_cast<T>(0)),
  m_height(static_cast<T>(0))
{}

template<typename T>
Size2d<T>::Size2d(T const& width, T const& height)
: m_width(width),
  m_height(height)
{}

template<typename T>
Size2d<T>::~Size2d()
{}

template<typename T>
T const& Size2d<T>::width() const
{
    return m_width;
}

template<typename T>
T const& Size2d<T>::height() const
{
    return m_height;
}

template<typename T>
Size2d<T> make_size(T const& width, T const& height)
{
    return Size2d<T>(width, height);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Size2d<T> const& size)
{
    os << "[" << size.width() << " " << size.height() << "]";
    return os;
}

} // namespace

#endif // INCLUDED
