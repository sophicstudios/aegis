#ifndef INCLUDED_AEGIS_AFTC_CIRCULARBUFFERITERATOR_H
#define INCLUDED_AEGIS_AFTC_CIRCULARBUFFERITERATOR_H

#include <iterator>

namespace aegis {
namespace aftc {

// Forward declaration used by the iterator class
template<typename T, typename Alloc>
class CircularBuffer;

/**
 * CircularBufferIterator
 */
template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
class CircularBufferIterator
    : public std::iterator<std::random_access_iterator_tag, T, Diff, Ptr, Ref>
{
public:
    typedef T value_type;
    typedef Diff difference_type;
    typedef Ptr pointer;
    typedef Ref reference;

    CircularBufferIterator();

    CircularBufferIterator(CircularBuffer<T, Alloc> const* buffer, pointer curr);

    CircularBufferIterator(CircularBufferIterator const& x);

    ~CircularBufferIterator();

    CircularBufferIterator& operator=(CircularBufferIterator const& x);

    reference operator*() const;

    pointer operator->() const;

    CircularBufferIterator& operator++(); // prefix++

    CircularBufferIterator operator++(int); // postfix++

    CircularBufferIterator& operator--(); // prefix--

    CircularBufferIterator operator--(int);// postfix--

    CircularBufferIterator& operator+=(difference_type n);

    CircularBufferIterator& operator-=(difference_type n);

    CircularBufferIterator operator+(difference_type n);

    CircularBufferIterator operator-(difference_type n);

    CircularBuffer<T, Alloc> const* m_circularBuffer;
    pointer m_current;
};

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator==(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator!=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator<(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator>(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator<=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator>=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
Diff operator-(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs);

////////////////////////////////////////////////////////////////////////////////
// CircularBufferIterator implementation
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::CircularBufferIterator()
: cirque_(0), curr_(0)
{}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::CircularBufferIterator(cirque<T, Alloc> const* que, Ptr curr)
: cirque_(que), curr_(curr)
{}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::CircularBufferIterator(CircularBufferIterator const& iter)
: cirque_(iter.cirque_), curr_(iter.curr_)
{}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::~CircularBufferIterator()
{}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>& CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator=(CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> const& iter)
{
    cirque_ = iter.cirque_;
    curr_ = iter.curr_;

    return *this;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
inline Ref CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator*() const
{
    return *curr_;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
inline Ptr CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator->() const
{
    return curr_;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>& CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator++() // prefix++
{
    ++curr_;
    if (curr_ == cirque_->impl_.storageEnd && curr_ != cirque_->dataEnd_.curr_)
    {
        curr_ = cirque_->impl_.storageBegin;
    }

    return *this;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator++(int) // postfix++
{
    CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> temp(*this);
    ++(*this);
    return temp;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>& CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator--() // prefix--
{
    curr_ = (curr_ == cirque_->impl_.storageBegin ? cirque_->impl_.storageEnd - 1 : curr_ - 1);
    return *this;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator--(int) // postfix--
{
    CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> temp(*this);
    --(*this);
    return temp;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>& CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator+=(Diff n)
{
    Diff distanceToStorageEnd = cirque_->impl_.storageEnd - curr_;
    curr_ = (n <= distanceToStorageEnd ? curr_ + n : cirque_->impl_.storageBegin + (n - distanceToStorageEnd));
    return *this;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>& CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator-=(Diff n)
{
    Diff distanceToStorageBegin = curr_ - cirque_->impl_.storageBegin;
    curr_ = (n <= distanceToStorageBegin ? curr_ - n : cirque_->impl_.storageEnd - (n - distanceToStorageBegin));
    return *this;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator+(Diff n)
{
    CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> temp(*this);
    temp += n;
    return temp;
}

template<typename T, typename Ref, typename Ptr, typename Diff, typename Alloc>
CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> CircularBufferIterator<T, Ref, Ptr, Diff, Alloc>::operator-(Diff n)
{
    CircularBufferIterator<T, Ref, Ptr, Diff, Alloc> temp(*this);
    temp -= n;
    return temp;
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator==(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    return lhs.curr_ == rhs.curr_;
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator!=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    return lhs.curr_ != rhs.curr_;
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator<(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    if (lhs.cirque_->dataBegin_.curr_ < lhs.cirque_->dataEnd_.curr_)
    {
        return lhs.curr_ < rhs.curr_;
    }
    else if (lhs.cirque_->dataBegin_.curr_ >= lhs.cirque_->dataEnd_.curr_)
    {
        bool rhsBeforeEnd = rhs.curr_ < rhs.cirque_->dataEnd_.curr_;
        bool lhsAfterEqualsBegin = lhs.curr_ >= lhs.cirque_->dataBegin_.curr_;
        if ((lhsAfterEqualsBegin && rhs.curr_ > rhs.cirque_->dataBegin_.curr_)
            || (lhs.curr_ < lhs.cirque_->dataEnd_.curr_ && rhsBeforeEnd))
        {
            return lhs.curr_ < rhs.curr_;
        }
        else if (lhsAfterEqualsBegin && rhsBeforeEnd)
        {
            return true;
        }
    }

    return false;
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator>(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    return (rhs < lhs);
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator<=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
bool operator>=(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename RefL, typename PtrL, typename RefR, typename PtrR, typename Diff, typename Alloc>
Diff operator-(CircularBufferIterator<T, RefL, PtrL, Diff, Alloc> const& lhs, CircularBufferIterator<T, RefR, PtrR, Diff, Alloc> const& rhs)
{
    if (lhs.cirque_->dataBegin_ < lhs.cirque_->dataEnd_)
    {
        return lhs.curr_ - rhs.curr_;
    }
    else if (lhs.cirque_->dataBegin_ >= lhs.cirque_->dataEnd_)
    {
        bool lhsBeforeEnd = lhs < lhs.cirque_->dataEnd_;
        bool rhsBeforeEnd = rhs < rhs.cirque_->dataEnd_;
        bool lhsAfterEqualsBegin = lhs >= lhs.cirque_->dataBegin_;
        bool rhsAfterEqualsBegin = rhs >= rhs.cirque_->dataBegin_;
        if ((lhsAfterEqualsBegin && rhsAfterEqualsBegin)
            || (lhsBeforeEnd && rhsBeforeEnd))
        {
            return lhs.curr_ - rhs.curr_;
        }
        else if (rhsAfterEqualsBegin && lhsBeforeEnd)
        {
            return (lhs.curr_ - lhs.cirque_->impl_.storageBegin) + (rhs.cirque_->impl_.storageEnd - rhs.curr_);
        }
        else if (lhsAfterEqualsBegin && rhsBeforeEnd)
        {
            return -((lhs.cirque_->impl_.storageEnd - lhs.curr_) + (rhs.curr_ - rhs.cirque_->impl_.storageBegin));
        }
    }

    return 0;
}

} // namespace
} // namespace

#endif // INCLUDED
