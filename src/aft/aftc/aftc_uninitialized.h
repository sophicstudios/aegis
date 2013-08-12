#ifndef INCLUDED_AEGIS_AFTC_UNINITIALIZED_H
#define INCLUDED_AEGIS_AFTC_UNINITIALIZED_H

#include <aftc_construct.h>
#include <boost/type_traits/is_pod.hpp>
#include <iterator>
#include <algorithm>

namespace aftc {

namespace {

template<typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value, boost::true_type const&)
{
    std::fill(first, last, value);
}

template<typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value, boost::false_type const&)
{
    ForwardIterator it = first;
    try
    {
        for (; it != last; ++it)
        {
            construct(&*it, value);
        }
    }
    catch(...)
    {
        destroy(first, it);
        throw;
    }
}

template<typename ForwardIterator, typename T>
void uninitialized_fill_n(ForwardIterator first, size_t n, T const& value, boost::true_type const&)
{
    std::fill_n(first, n, value);
}

template<typename ForwardIterator, typename T>
void uninitialized_fill_n(ForwardIterator first, size_t n, T const& value, boost::false_type const&)
{
    ForwardIterator it = first;
    try
    {
        for (; n > 0; --n, ++it)
        {
            construct(&*it, value);
        }
    }
    catch(...)
    {
        destroy(first, it);
        throw;
    }
}

template<typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, boost::true_type const&)
{
    return std::copy(first, last, result);
}

template<typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, boost::false_type const&)
{
    ForwardIterator it = result;
    try
    {
        for (; first != last; ++first, ++it)
        {
            construct(&*it, *first);
        }
        return it;
    }
    catch (...)
    {
        destroy(result, it);
        throw;
    }
}

template<typename InputIterator, typename SizeType, typename ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator result, boost::true_type const&)
{
    return std::copy(first, first + n, result);
}

template<typename InputIterator, typename SizeType, typename ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator result, boost::false_type const&)
{
    ForwardIterator it = result;
    try
    {
        for (; n > 0; --n, ++first, ++it)
        {
            construct(&*it, *first);
        }
        return it;
    }
    catch (...)
    {
        destroy(result, it);
        throw;
    }
}

} // namespace

template<typename ForwardIterator, typename T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    uninitialized_fill(first, last, value, boost::is_pod<value_type>());
}

template<typename ForwardIterator, typename SizeType, typename T>
void uninitialized_fill_n(ForwardIterator first, SizeType n, T const& value)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    uninitialized_fill_n(first, n, value, boost::is_pod<value_type>());
}

template<typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    return uninitialized_copy(first, last, result, boost::is_pod<value_type>());
}

template<typename InputIterator, typename SizeType, typename ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator result)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    return uninitialized_copy_n(first, n, result, boost::is_pod<value_type>());
}

} // namespace

#endif // INCLUDED
