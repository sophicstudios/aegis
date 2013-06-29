#ifndef INCLUDED_AEGIS_AFTC_CIRCULARBUFFER_H
#define INCLUDED_AEGIS_AFTC_CIRCULARBUFFER_H

#include <aftc_uninitialized.h>
#include <aftc_construct.h>
#include <memory>
#include <iterator>
#include <cassert>

namespace aegis {
namespace aftc {

/**
  * class cirque_base
  * All allocation is done here to make exception safety easier to manage
  */
template<typename T, class Alloc>
struct CircularBufferBase
{
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::difference_type difference_type;
    typedef CircularBufferIterator<value_type, reference, pointer, difference_type, allocator_type> iterator;
    typedef CircularBufferIterator<value_type, const_reference, const_pointer, difference_type, allocator_type> const_iterator;
    typedef size_t size_type;
    
    CircularBufferBase(Alloc const& alloc)
    : impl_(alloc)
    {}
    
    CircularBufferBase(Alloc const& alloc, size_t n)
    : impl_(alloc)
    {
        impl_.storageBegin = allocate(n);
        impl_.storageEnd = impl_.storageBegin + n;
    }

    ~CircularBufferBase()
    {
        if (impl_.storageBegin)
        {
            deallocate(impl_.storageBegin, impl_.storageEnd - impl_.storageBegin);
        }
    }
    
    pointer allocate(size_type n)
    {
        return impl_.allocate(n);
    }
    
    void deallocate(pointer p, size_type n)
    {
        impl_.deallocate(p, n);
    }

    // This struct is used for Empty Base Optimization (EBO), so that
    // allocator objects that don't actually contain any members don't
    // take up any space in the class.
    struct ebo_impl : public allocator_type
    {
        ebo_impl(allocator_type const& alloc)
        : allocator_type(alloc), storageBegin(0), storageEnd(0)
        {}

        pointer storageBegin;
        pointer storageEnd;
    };

    ebo_impl impl_;
};

/**
 * CircularBuffer
 */
template<typename T, class Alloc = std::allocator<T> >
class CircularBuffer : public CircularBufferBase<T, Alloc>
{
public:
    typedef CircularBufferBase<T, Alloc> parent_type;
    typedef typename parent_type::value_type value_type;
    typedef typename parent_type::allocator_type allocator_type;
    typedef typename parent_type::allocator_type::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;
    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::difference_type difference_type;
    typedef CircularBufferIterator<value_type, reference, pointer, difference_type, allocator_type> iterator;
    typedef CircularBufferIterator<value_type, const_reference, const_pointer, difference_type, allocator_type> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;

	template<typename T1, typename R, typename P, typename D, typename A> friend struct CircularBufferIterator;

	template<typename T1, typename RL, typename PL, typename RR, typename PR, typename D, typename A>
	friend bool operator<(CircularBufferIterator<T1, RL, PL, D, A> const& lhs, CircularBufferIterator<T1, RR, PR, D, A> const& rhs);

	template<typename T1, typename RL, typename PL, typename RR, typename PR, typename D, typename A>
	friend D operator-(CircularBufferIterator<T1, RL, PL, D, A> const& lhs, CircularBufferIterator<T1, RR, PR, D, A> const& rhs);

	explicit CircularBuffer(allocator_type const& alloc = allocator_type());

    CircularBuffer(CircularBuffer const& rhs);

    template<typename InputIterator>
    CircularBuffer(InputIterator first, InputIterator last, allocator_type const& alloc = allocator_type());

    ~CircularBuffer();

    CircularBuffer& operator=(CircularBuffer const& q);

    void assign(size_type n, const_reference v);

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    allocator_type get_allocator() const;

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    size_type size() const;

    size_type capacity() const;

    void reserve(size_type n);

    bool empty() const;

    reference operator[](size_type n);

    const_reference operator[](size_type n) const;

    reference at(size_type n);

    const_reference at(size_type n) const;

    reference front();

    const_reference front() const;

    reference back();

    const_reference back() const;

    void push_front(value_type const& v);

    void push_back(value_type const& value);

    void pop_front();

    void pop_back();

    iterator insert(iterator p, value_type const& v);

    iterator insert(iterator p, size_type n, value_type const& v);

    template<typename InputIterator>
    iterator insert(iterator p, InputIterator first, InputIterator last);

    iterator erase(iterator p);

    iterator erase(iterator first, iterator last);

    void swap(CircularBuffer& q);

    void clear();

private:
	template<typename InputIterator>
	pointer allocateAndCopy(size_t n, InputIterator first, InputIterator last);

    value_type* storageBegin();

    value_type* storageEnd();

    iterator dataBegin_; // points to the first data element
    iterator dataEnd_; // points to one past the last element of data
    size_type size_; // can't calculate size very quickly, so just store it separately
};


////////////////////////////////////////////////////////////////////////////////
// CircularBuffer implementation
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(allocator_type const& alloc)
: parent_type(alloc), size_(0)
{
    dataBegin_ = iterator(this, 0);
    dataEnd_ = iterator(this, 0);
}

template<typename T, typename Alloc>
CircularBuffer<T, Alloc>::CircularBuffer(CircularBuffer const& rhs)
: parent_type(rhs.impl_, rhs.size_), size_(rhs.size_)
{
    sslib::util::uninitialized_copy(rhs.begin(), rhs.end(), impl_.storageBegin);
    dataBegin_ = iterator(this, impl_.storageBegin);
	dataEnd_ = dataBegin_ + size_;
}

template<typename T, typename Alloc>
template<typename InputIterator>
CircularBuffer<T, Alloc>::CircularBuffer(InputIterator first, InputIterator last, Alloc const& alloc)
: parent_type(alloc, last - first), size_(last - first)
{
    sslib::util::uninitialized_copy(first, last, impl_.storageBegin);
    dataBegin_ = iterator(this, impl_.storageBegin);
	dataEnd_ = dataBegin_ + size_;
}

template<typename T, typename Alloc>
CircularBuffer<T, Alloc>::~CircularBuffer()
{
    if (!empty())
    {
		sslib::util::destroy(begin(), end());
    }
}

template<typename T, typename Alloc>
CircularBuffer<T, Alloc>& CircularBuffer<T, Alloc>::operator=(CircularBuffer const& rhs)
{
    if (this != &rhs)
    {
        size_t rhsSize = rhs.size();
        if (rhsSize > capacity())
        {
            pointer temp = allocateAndCopy(rhsSize, rhs.begin(), rhs.end());
			sslib::util::destroy(begin(), end());
			this->deallocate(impl_.storageBegin, size());
			size_ = rhsSize;
			impl_.storageBegin = temp;
			impl_.storageEnd = impl_.storageBegin + size();
			dataBegin_ = iterator(this, impl_.storageBegin);
			dataEnd_ = iterator(this, impl_.storageEnd);
        }
        else if (size() >= rhsSize)
        {
			iterator i = std::copy(rhs.begin(), rhs.end(), begin());
			sslib::util::destroy(i, end());
			size_ = rhsSize;
			dataEnd_ = begin() + size_;
        }
        else
        {
			std::copy(rhs.begin(), rhs.begin() + size(), begin());
			sslib::util::uninitialized_copy(rhs.begin() + size(), rhs.end(), end());
			size_ = rhsSize;
			dataEnd_ = begin() + size_;
        }
    }

    return *this;
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::assign(size_type n, const_reference value)
{
}

template<typename T, typename Alloc>
template<typename InputIterator>
void CircularBuffer<T, Alloc>::assign(InputIterator first, InputIterator last)
{
}

template<typename T, typename Alloc>
Alloc CircularBuffer<T, Alloc>::get_allocator() const
{
    return alloc_;
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iterator CircularBuffer<T, Alloc>::begin()
{
    return dataBegin_;
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_iterator CircularBuffer<T, Alloc>::begin() const
{
    return const_iterator(this, dataBegin_.curr_);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iterator CircularBuffer<T, Alloc>::end()
{
    return dataEnd_;
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_iterator CircularBuffer<T, Alloc>::end() const
{
    return const_iterator(this, dataEnd_.curr_);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reverse_iterator CircularBuffer<T, Alloc>::rbegin()
{
    return reverse_iterator(end());
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reverse_iterator CircularBuffer<T, Alloc>::rbegin() const
{
    return const_reverse_iterator(end());
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reverse_iterator CircularBuffer<T, Alloc>::rend()
{
    return reverse_iterator(begin());
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reverse_iterator CircularBuffer<T, Alloc>::rend() const
{
    return const_reverse_iterator(begin());
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::size_type CircularBuffer<T, Alloc>::size() const
{
    return size_;
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::size_type CircularBuffer<T, Alloc>::capacity() const
{
    return (impl_.storageEnd - impl_.storageBegin);
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::reserve(size_type n)
{
    if (n > capacity())
    {
        pointer temp = allocateAndCopy(n, begin(), end());
        sslib::util::destroy(begin(), end());
        deallocate(impl_.storageBegin, impl_.storageEnd - impl_.storageBegin);
        impl_.storageBegin = temp;
        impl_.storageEnd = temp + n;
        dataBegin_ = iterator(this, impl_.storageBegin);
        dataEnd_ = dataBegin_ + size_;
    }
}

template<typename T, typename Alloc>
bool CircularBuffer<T, Alloc>::empty() const
{
    return size_ == 0;
}
template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reference CircularBuffer<T, Alloc>::operator[](size_type n)
{
	return *(begin() + n);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reference CircularBuffer<T, Alloc>::operator[](size_type n) const
{
	return *(begin() + n);
}


template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reference CircularBuffer<T, Alloc>::at(typename CircularBuffer<T, Alloc>::size_type n)
{
	if (n >= size())
	{
		throw std::out_of_range("CircularBuffer at()");
	}
	return *(begin() + n);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reference CircularBuffer<T, Alloc>::at(typename CircularBuffer<T, Alloc>::size_type n) const
{
	if (n >= size())
	{
		throw std::out_of_range();
	}
	return *(begin() + n);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reference CircularBuffer<T, Alloc>::front()
{
	return *begin();
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reference CircularBuffer<T, Alloc>::front() const
{
	return *begin();
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::reference CircularBuffer<T, Alloc>::back()
{
	return *(end() - 1);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::const_reference CircularBuffer<T, Alloc>::back() const
{
	return *(end() - 1);
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::push_front(typename CircularBuffer<T, Alloc>::value_type const& v)
{
    insert(begin(), v);
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::push_back(typename CircularBuffer<T, Alloc>::value_type const& v)
{
    insert(end(), v);
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::pop_front()
{
    erase(begin());
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::pop_back()
{
    erase(end() - 1);
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iterator CircularBuffer<T, Alloc>::insert(
    typename CircularBuffer<T, Alloc>::iterator p,
    typename CircularBuffer<T, Alloc>::value_type const& v)
{
    size_type n = p - begin();
    if (dataEnd_.curr_ != impl_.storageEnd && p == end())
    {
        sslib::util::construct(dataEnd_.curr_, v);
        ++dataEnd_;
    }
    else
    {

    }
    return begin() + n;
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iteratorvoid CircularBuffer<T, Alloc>::insert(
    typename CircularBuffer<T, Alloc>::iterator p,
    typename CircularBuffer<T, Alloc>::size_type n,
    typename CircularBuffer<T, Alloc>::value_type const& v)
{
    return end();
}

template<typename T, typename Alloc>
template<typename InputIterator>
typename CircularBuffer<T, Alloc>::iteratorvoid CircularBuffer<T, Alloc>::insert(typename CircularBuffer<T, Alloc>::iterator p, InputIterator first, InputIterator last)
{
	size_type finalSize = size() + (last - first);
	if (finalSize > capacity())
	{
        pointer temp = this->allocate(finalSize);
        pointer it = sslib::util::uninitialized_copy(begin(), p, temp);
        it = sslib::util::uninitialized_copy(first, last, it);
        it = sslib::util::uninitialized_copy(p, end(), it);
        destroy(begin(), end());
        this->deallocate(impl_.storageBegin, size());
        
        size_ = finalSize;
        impl_.storageBegin = temp;
        impl_.storageEnd = impl_.storageBegin + size_;
        dataBegin_ = iterator(this, impl_.storageBegin);
        dataEnd_ = dataBegin_ + size_;
	}
	else
	{
	    // TODO
	    // copy from p to end to p + (last - first)
	    // copy first to last to p
	}

    return end();
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iterator CircularBuffer<T, Alloc>::erase(typename CircularBuffer<T, Alloc>::iterator p)
{
	return end();
}

template<typename T, typename Alloc>
typename CircularBuffer<T, Alloc>::iterator CircularBuffer<T, Alloc>::erase(
    typename CircularBuffer<T, Alloc>::iterator first,
    typename CircularBuffer<T, Alloc>::iterator last)
{
	return end();
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::swap(CircularBuffer& q)
{
}

template<typename T, typename Alloc>
void CircularBuffer<T, Alloc>::clear()
{
}

template<typename T, typename Alloc>
template<typename InputIterator>
typename CircularBuffer<T, Alloc>::pointer CircularBuffer<T, Alloc>::allocateAndCopy(
    typename CircularBuffer<T, Alloc>::size_type n,
    InputIterator first,
    InputIterator last)
{
	pointer buffer = this->allocate(n);
	try
	{
	    sslib::util::uninitialized_copy(first, last, buffer);
		return buffer;
	}
	catch (...)
	{
		this->deallocate(buffer, n);
		throw;
	}
}

} // namespace
} // namespace

#endif // INCLUDED
