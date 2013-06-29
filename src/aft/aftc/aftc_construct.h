#ifndef INCLUDED_AEGIS_AFTC_CONSTRUCT_H
#define INCLUDED_AEGIS_AFTC_CONSTRUCT_H

#include <boost/type_traits/is_pod.hpp>
#include <iterator>

namespace aegis {
namespace aftc {

namespace {

template<typename T>
void destroy(T* ptr, boost::true_type const&)
{}

template<typename T>
void destroy(T* ptr, boost::false_type const&)
{
    ptr->~T();
}

} // namespace

template<typename T>
void construct(T* ptr)
{
    ::new(ptr) T();
}

template<typename T1, typename T2>
void construct(T1* ptr, T2 const& value)
{
    ::new(ptr) T1(value);
}

template<typename T>
void destroy(T* ptr)
{
    destroy(ptr, boost::is_pod<T>());
}

template<typename ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    boost::is_pod<value_type> isPod;
    for (; first != last; ++first)
    {
        destroy(&*first, isPod);
    }
}

} // namespace
} // namespace

#endif // INCLUDED
