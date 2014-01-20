#ifndef INCLUDED_AEGIS_AFTU_STRINGREF_H
#define INCLUDED_AEGIS_AFTU_STRINGREF_H

#include <algorithm>
#include <string>

namespace aftu {

/**
 * \class StringRef
 *
 * \description A class for holding a reference to a string or part of
 * a string. The original string is never copied, so this allows for
 * efficient storage of a source string and references to its substrings.
 * The life of the source string must outlive any StringRef instances that
 * refer to it, otherwise the behavior is undefined.
 *
 * Example:
 *     char cstr[50] = "The dog is blue";
 *     StringRef<char> the_ref(cstr, 0, 3); // "The"
 *     StringRef<char> dog_ref(cstr, 4, 3); // "dog"
 *     StringRef<char> is_ref(cstr, 8, 2); // "is"
 *     StringRef<char> blue_ref(cstr, 11, 4); // "blue";
 *
 * std::basic_string types can also be used with a StringRef and comparisons
 * between StringRefs of basic_string and null-terminated C strings are
 * allowed. Example:
 *
 *     std::string str("The dog is blue");
 *     StringRef<std::string> the_ref_1(str, 0, 3);
 *
 *     assert(the_ref == the_ref_1);
 */
template<typename T>
class StringRef
{
public:
    typedef T const* const_iterator;
    typedef T* iterator;
    
    StringRef();
    
    StringRef(T const* const orig);
    
    StringRef(const_iterator beg, const_iterator end);
        
    StringRef(T const* const orig, size_t offset, size_t length);

    StringRef(StringRef<T> const& orig);

    ~StringRef();
    
    StringRef<T>& operator=(StringRef<T> const& rhs);
    
    StringRef<T>& operator=(T const* const rhs);

    StringRef<T>& assign(const_iterator begin, const_iterator end);
    
    StringRef<T>& assign(T const* const orig, size_t offset, size_t length);
            
    operator std::basic_string<T>() const;
    
    std::basic_string<T> str() const;
    
    const_iterator begin() const;
    
    const_iterator end() const;
    
    size_t size() const;
    
    bool isEmpty() const;

private:
    const_iterator m_beg;
    const_iterator m_end;
};

////////////////////////////////////////////////////////////
// Specialization of StringRef for std::basic_string
////////////////////////////////////////////////////////////

template<typename CharT>
class StringRef<std::basic_string<CharT> >
{
public:
    typedef typename std::basic_string<CharT>::const_iterator const_iterator;
    typedef typename std::basic_string<CharT>::iterator iterator;
    
    StringRef();
    
    StringRef(std::basic_string<CharT> const& orig);
    
    StringRef(const_iterator beg, const_iterator end);
        
    StringRef(std::basic_string<CharT> const& orig, size_t offset, size_t length);

    StringRef(StringRef<std::basic_string<CharT> > const& orig);

    ~StringRef();
    
    StringRef<std::basic_string<CharT> >& operator=(StringRef<std::basic_string<CharT> > const& rhs);

    StringRef<std::basic_string<CharT> >& operator=(std::basic_string<CharT> const& rhs);

    StringRef<std::basic_string<CharT> >& assign(const_iterator begin, const_iterator end);
    
    StringRef<std::basic_string<CharT> >& assign(std::basic_string<CharT> const& orig, size_t offset, size_t length);
            
    operator std::basic_string<CharT>() const;
    
    std::basic_string<CharT>  str() const;
    
    const_iterator begin() const;
    
    const_iterator end() const;
    
    size_t size() const;
    
    bool isEmpty() const;

private:
    const_iterator m_beg;
    const_iterator m_end;
};

////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////

template<typename T>
bool operator==(StringRef<T> const& lhs, StringRef<T> const& rhs);

template<typename T>
bool operator==(StringRef<T> const& lhs, T const* const rhs);

template<typename T>
bool operator==(T const* const lhs, StringRef<T> const& rhs);

template<typename CharT>
bool operator==(StringRef<std::basic_string<CharT> > const& lhs, std::basic_string<CharT> const& rhs);

template<typename CharT>
bool operator==(std::basic_string<CharT> const& lhs, StringRef<std::basic_string<CharT> > const& rhs);

template<typename CharT>
bool operator==(StringRef<std::basic_string<CharT> > const& lhs, CharT const* const rhs);

template<typename CharT>
bool operator==(CharT const* const lhs, StringRef<std::basic_string<CharT> > const& rhs);

template<typename CharT>
bool operator==(StringRef<CharT> const& lhs, std::basic_string<CharT> const& rhs);

template<typename CharT>
bool operator==(std::basic_string<CharT> const& lhs, StringRef<CharT> const& rhs);

template<typename T>
bool operator!=(StringRef<T> const& lhs, StringRef<T> const& rhs);

template<typename T>
bool operator!=(StringRef<T> const& lhs, T const* const rhs);

template<typename T>
bool operator!=(T const* const lhs, StringRef<T> const& rhs);

template<typename CharT>
bool operator!=(StringRef<std::basic_string<CharT> > const& lhs, CharT const* const rhs);

template<typename CharT>
bool operator!=(CharT const* const lhs, StringRef<std::basic_string<CharT> > const& rhs);

template<typename CharT>
bool operator!=(StringRef<CharT> const& lhs, std::basic_string<CharT> const& rhs);

template<typename CharT>
bool operator!=(std::basic_string<CharT> const& lhs, StringRef<CharT> const& rhs);

////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////

template<typename T>
StringRef<T>::StringRef()
: m_beg(0),
  m_end(0)
{}

template<typename T>
StringRef<T>::StringRef(T const* const orig)
: m_beg(orig),
  m_end(orig + std::char_traits<T>::length(orig))
{}

template<typename T>
StringRef<T>::StringRef(const_iterator beg, const_iterator end)
: m_beg(beg),
  m_end(end)
{}

template<typename T>
StringRef<T>::StringRef(T const* const orig, size_t offset, size_t length)
: m_beg(orig + offset),
  m_end(orig + offset + length)
{}

template<typename T>
StringRef<T>::StringRef(StringRef<T> const& orig)
: m_beg(orig.m_beg),
  m_end(orig.m_end)
{}

template<typename T>
StringRef<T>::~StringRef()
{}

template<typename T>
StringRef<T>& StringRef<T>::operator=(StringRef<T> const& rhs)
{
    m_beg = rhs.m_beg;
    m_end = rhs.m_end;
    
    return *this;
}

template<typename T>
StringRef<T>& StringRef<T>::operator=(T const* const rhs)
{
    m_beg = rhs;
    m_end = rhs + std::char_traits<char>::length(rhs);
    
    return *this;
}

template<typename T>
StringRef<T>& StringRef<T>::assign(const_iterator begin, const_iterator end)
{
    m_beg = begin;
    m_end = end;
}

template<typename T>
StringRef<T>& StringRef<T>::assign(T const* const orig, size_t offset, size_t length)
{
    m_beg = orig + offset;
    m_end = m_beg + length;
}
        
template<typename T>
StringRef<T>::operator std::basic_string<T>() const
{
    return str();
}

template<typename T>
std::basic_string<T> StringRef<T>::str() const
{
    return std::basic_string<T>(m_beg, m_end);
}

template<typename T>
typename StringRef<T>::const_iterator StringRef<T>::begin() const
{
    return m_beg;
}

template<typename T>
typename StringRef<T>::const_iterator StringRef<T>::end() const
{
    return m_end;
}

template<typename T>
size_t StringRef<T>::size() const
{
    return m_end - m_beg;
}

template<typename T>
bool StringRef<T>::isEmpty() const
{
    return m_beg == m_end;
}

////////////////////////////////////////////////////////////
// Implementation for basic_string specialization
////////////////////////////////////////////////////////////

template<typename CharT>
StringRef<std::basic_string<CharT> >::StringRef()
: m_beg(0),
  m_end(0)
{}

template<typename CharT>
StringRef<std::basic_string<CharT> >::StringRef(std::basic_string<CharT> const& orig)
: m_beg(orig.begin()),
  m_end(orig.end())
{}

template<typename CharT>
StringRef<std::basic_string<CharT> >::StringRef(const_iterator beg, const_iterator end)
: m_beg(beg),
  m_end(end)
{}
    
template<typename CharT>
StringRef<std::basic_string<CharT> >::StringRef(std::basic_string<CharT> const& orig, size_t offset, size_t length)
: m_beg(orig.begin() + offset),
  m_end(orig.begin() + offset + length)
{}

template<typename CharT>
StringRef<std::basic_string<CharT> >::StringRef(StringRef<std::basic_string<CharT> > const& orig)
: m_beg(orig.m_beg),
  m_end(orig.m_end)
{}

template<typename CharT>
StringRef<std::basic_string<CharT> >::~StringRef()
{}

template<typename CharT>
StringRef<std::basic_string<CharT> >& StringRef<std::basic_string<CharT> >::operator=(StringRef<std::basic_string<CharT> > const& rhs)
{
    m_beg = rhs.m_beg;
    m_end = rhs.m_end;
    
    return *this;
}

template<typename CharT>
StringRef<std::basic_string<CharT> >& StringRef<std::basic_string<CharT> >::operator=(std::basic_string<CharT> const& rhs)
{
    m_beg = rhs.begin();
    m_end = rhs.end();
    
    return *this;
}

template<typename CharT>
StringRef<std::basic_string<CharT> >& StringRef<std::basic_string<CharT> >::assign(const_iterator begin, const_iterator end)
{
    m_beg = begin;
    m_end = end;
    
    return *this;
}

template<typename CharT>
StringRef<std::basic_string<CharT> >& StringRef<std::basic_string<CharT> >::assign(std::basic_string<CharT> const& orig, size_t offset, size_t length)
{
    m_beg = orig.begin() + offset;
    m_end = m_beg + length;
    
    return *this;
}
        
template<typename CharT>
StringRef<std::basic_string<CharT> >::operator std::basic_string<CharT>() const
{
    return str();
}

template<typename CharT>
std::basic_string<CharT> StringRef<std::basic_string<CharT> >::str() const
{
    return std::basic_string<CharT>(m_beg, m_end);
}

template<typename CharT>
typename StringRef<std::basic_string<CharT> >::const_iterator StringRef<std::basic_string<CharT> >::begin() const
{
    return m_beg;
}

template<typename CharT>
typename StringRef<std::basic_string<CharT> >::const_iterator StringRef<std::basic_string<CharT> >::end() const
{
    return m_end;
}

template<typename CharT>
size_t StringRef<std::basic_string<CharT> >::size() const
{
    return m_end - m_beg;
}

template<typename CharT>
bool StringRef<std::basic_string<CharT> >::isEmpty() const
{
    return m_beg == m_end;
}

////////////////////////////////////////////////////////////
// Implementation for Operators
////////////////////////////////////////////////////////////

template<typename T>
bool operator==(StringRef<T> const& lhs, StringRef<T> const& rhs)
{
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T>
bool operator==(StringRef<T> const& lhs, T const* const rhs)
{
    return lhs.size() == std::char_traits<T>::length(rhs)
        && std::equal(lhs.begin(), lhs.end(), rhs);
}

template<typename T>
bool operator==(T const* const lhs, StringRef<T> const& rhs)
{
    return std::char_traits<T>::length(lhs) == rhs.size()
        && std::equal(rhs.begin(), rhs.end(), lhs);
}

template<typename CharT>
bool operator==(StringRef<std::basic_string<CharT> > const& lhs, std::basic_string<CharT> const& rhs)
{
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator==(std::basic_string<CharT> const& lhs, StringRef<std::basic_string<CharT> > const& rhs)
{
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator==(StringRef<std::basic_string<CharT> > const& lhs, CharT const* const rhs)
{
    return lhs.size() == std::char_traits<CharT>::length(rhs)
        && std::equal(lhs.begin(), lhs.end(), rhs);
}

template<typename CharT>
bool operator==(CharT const* const lhs, StringRef<std::basic_string<CharT> > const& rhs)
{
    return std::char_traits<CharT>::length(lhs) == rhs.size()
        && std::equal(rhs.begin(), rhs.end(), lhs);
}

template<typename CharT>
bool operator==(StringRef<CharT> const& lhs, std::basic_string<CharT> const& rhs)
{
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator==(std::basic_string<CharT> const& lhs, StringRef<CharT> const& rhs)
{
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T>
bool operator!=(StringRef<T> const& lhs, StringRef<T> const& rhs)
{
    return lhs.size() != rhs.size()
        || !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T>
bool operator!=(StringRef<T> const& lhs, T const* const rhs)
{
    return lhs.size() != std::char_traits<T>::length(rhs)
        || !std::equal(lhs.begin(), lhs.end(), rhs);
}

template<typename T>
bool operator!=(T const* const lhs, StringRef<T> const& rhs)
{
    return std::char_traits<T>::length(lhs) != rhs.size()
        || !std::equal(rhs.begin(), rhs.end(), lhs);
}

template<typename CharT>
bool operator!=(StringRef<std::basic_string<CharT> > const& lhs, std::basic_string<CharT> const& rhs)
{
    return lhs.size() != rhs.size()
        || !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator!=(std::basic_string<CharT> const& lhs, StringRef<std::basic_string<CharT> > const& rhs)
{
    return lhs.size() != rhs.size()
        || !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator!=(StringRef<std::basic_string<CharT> > const& lhs, CharT const* const rhs)
{
    return lhs.size() != std::char_traits<CharT>::length(rhs)
        || !std::equal(lhs.begin(), lhs.end(), rhs);
}

template<typename CharT>
bool operator!=(CharT const* const lhs, StringRef<std::basic_string<CharT> > const& rhs)
{
    return std::char_traits<CharT>::length(lhs) != rhs.size()
        || !std::equal(rhs.begin(), rhs.end(), lhs);
}

template<typename CharT>
bool operator!=(StringRef<CharT> const& lhs, std::basic_string<CharT> const& rhs)
{
    return lhs.size() != rhs.size()
        || !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename CharT>
bool operator!=(std::basic_string<CharT> const& lhs, StringRef<CharT> const& rhs)
{
    return lhs.size() != rhs.size()
        || !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

} // namespace

#endif // INCLUDED
