#ifndef INCLUDED_AEGIS_AFTC_PACKEDSTRINGMAP_H
#define INCLUDED_AEGIS_AFTC_PACKEDSTRINGMAP_H

#include <ostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace aftc {

#define PACKEDSTRINGMAP_DEBUG 1

// Forward declaration of class PackedStringMapIterator
template<typename T>
class PackedStringMapIterator;

/**
 * @class PackedStringMap
 *
 * @brief An ordered, cache-friendly map of key-value pairs, where keys
 * are of type std::string and values are of template type T.
 *
 * This class provides a cache-friendly map of string-value pairs, by storing
 * both the string and values in-place in an array. This provides good locality
 * of data when looking up items in the map which helps maximize the
 * effectiveness of CPU caches. It is not intended that this container hold
 * a very large number of items. It is best used for small maps of string-
 * value pairs. A user of this container would most likely partition their
 * dataset into multiple sections, and create a PackedStringMap object to hold
 * the data for a particular section. One example use case is the burst-trie
 * data structure, which can utilize the PackedStringMap as part of its
 * underlying data storage for holding the string keys and their associated
 * values.
 *
 * Example Usage:
 *
 * typedef PackedStringMap<int> StringIntMap;
 * StringIntMap m;
 *
 * m.insert("key1", 1);
 * m.insert("key2", 2);
 * assert(m.size() == 2);
 *
 * StringIntMap::iterator it = m.find("key1");
 * assert(it != m.end());
 *
 * m.erase(it);
 * assert(m.size() == 1);
 *
 * it = m.find("key1");
 * assert(it == m.end());
 */
template<typename T>
class PackedStringMap
{
    friend class PackedStringMapIterator<T>;

public:
    typedef std::string key_type;
    typedef std::pair<std::string, T> value_type;
    typedef PackedStringMapIterator<T> iterator;
    typedef const PackedStringMapIterator<T> const_iterator;
    typedef size_t size_type;
    
    // construct/destroy/copy
    PackedStringMap();
    PackedStringMap(PackedStringMap<T> const& rhs);    
    ~PackedStringMap();
    PackedStringMap<T>& operator=(PackedStringMap<T> const& rhs);

    // size
    bool empty() const;
    size_type size() const;

    // iterators
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    // modifiers
    std::pair<iterator, bool> insert(value_type const& object);
    void erase(const_iterator const& position);
    size_type erase(key_type const& key);

    // lookup
    iterator find(key_type const& key);
    const_iterator find(key_type const& key) const;
    size_type count(key_type const& key) const;
    iterator lowerBound(key_type const& key);
    const_iterator lowerBound(key_type const& key) const;
    iterator upperBound(key_type const& key);
    const_iterator upperBound(key_type const& key) const;
    
    std::ostream& print(std::ostream& os) const;
    
private:
    void findPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const;
    void lowerBoundPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const;
    void upperBoundPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const;

    struct Data
    {
        Data(size_t kl, T const& val)
        : keyLength(kl), value(val)
        {}
        
        size_t keyLength;
        T value;
    };
    
    std::vector<char> m_keys;
    std::vector<Data> m_data;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, PackedStringMap<T> const& rhs);

template<typename T>
class PackedStringMapIterator
{
    friend class PackedStringMap<T>;
    template<typename U> friend bool operator==(PackedStringMapIterator<U> const&, PackedStringMapIterator<U> const&);
    template<typename U> friend bool operator!=(PackedStringMapIterator<U> const&, PackedStringMapIterator<U> const&);

public:
    /**
     * @brief Default Constructor.
     *
     * Constructs a PackedStringMapIterator that doesn't point
     * to anything. Trying to access the data on this object will result in
     * undefined behavior.
     */
    PackedStringMapIterator();

    /**
     * @brief Constructor for specific element in a PackedStringMap.
     */
    PackedStringMapIterator(PackedStringMap<T>* stringMap, size_t dataOffset, size_t keyOffset);

    /**
     * @brief Copy constructor.
     */
    PackedStringMapIterator(PackedStringMapIterator const& rhs);

    /**
     * @brief Destructor.
     */
    ~PackedStringMapIterator();

    /**
     * @brief Assignment operator.
     */
    PackedStringMapIterator& operator=(PackedStringMapIterator const& rhs);
    
    T& operator*();
    
    T const& operator*() const;
    
    T* operator->();
    
    T const* operator->() const;
    
    PackedStringMapIterator& operator++(); // prefix increment
    
    PackedStringMapIterator operator++(int); // postfix increment
    
    PackedStringMapIterator& operator--(); // prefix decrement
    
    PackedStringMapIterator operator--(int); // postfix decrement

private:
    PackedStringMap<T>* m_stringMap;
    typename PackedStringMap<T>::size_type m_dataOffset;
    typename PackedStringMap<T>::size_type m_keyOffset;
};

template<typename T>
bool operator==(PackedStringMapIterator<T> const& lhs, PackedStringMapIterator<T> const& rhs);

template<typename T>
bool operator!=(PackedStringMapIterator<T> const& lhs, PackedStringMapIterator<T> const& rhs);

////////////////////////////////////////////////////////////////////////////////
/// PackedStringMap Implementation
////////////////////////////////////////////////////////////////////////////////

template<typename T>
PackedStringMap<T>::PackedStringMap()
{}

template<typename T>
PackedStringMap<T>::PackedStringMap(PackedStringMap<T> const& rhs)
{
    m_keys.assign(rhs.m_keys.begin(), rhs.m_keys.end());
    m_data.assign(rhs.m_data.begin(), rhs.m_data.end());
}

template<typename T>
PackedStringMap<T>::~PackedStringMap()
{}

template<typename T>
PackedStringMap<T>& PackedStringMap<T>::operator=(PackedStringMap<T> const& rhs)
{
    if (&rhs == this) {
        return *this;
    }

    m_keys.assign(rhs.m_keys.begin(), rhs.m_keys.end());
    m_data.assign(rhs.m_data.begin(), rhs.m_data.end());
}

template<typename T>
bool PackedStringMap<T>::empty() const
{
    return m_data.empty();
}

template<typename T>
size_t PackedStringMap<T>::size() const
{
    return m_data.size();
}

template<typename T>
typename PackedStringMap<T>::iterator PackedStringMap<T>::begin()
{
    return iterator(this, 0, 0);
}

template<typename T>
typename PackedStringMap<T>::const_iterator PackedStringMap<T>::begin() const
{
    return const_iterator(this, 0, 0);
}

template<typename T>
typename PackedStringMap<T>::iterator PackedStringMap<T>::end()
{
    return iterator(this, m_data.size(), m_keys.size());
}

template<typename T>
typename PackedStringMap<T>::const_iterator PackedStringMap<T>::end() const
{
    return const_iterator(this, m_data.size(), m_keys.size());
}

template<typename T>
std::pair<typename PackedStringMap<T>::iterator, bool> PackedStringMap<T>::insert(value_type const& object)
{
    // first find out if we already have an entry for this
    // string and if so, replace the value.
    // If not found, find the correct insertion point to keep the array
    // sorted, then insert the new data into that place
    std::string const& key = object.first;
    T const& value = object.second;

    size_t dataOffset = 0;
    size_t keyOffset = 0;
    while (dataOffset < m_data.size()) {
        int compResult = key.compare(0, key.size(), &m_keys[keyOffset], m_data[dataOffset].keyLength);
        if (0 == compResult) {
            // key already exists, so return a pair that contains an iterator
            // to this location and false, signifying no insert was done.

            return std::make_pair(iterator(this, dataOffset, keyOffset), false);
        }
        else if (compResult < 0) {
            // insertion key is less than the current value, so insert the
            // object in the current location and move the rest of the data back
            
            // first, insert the key into the keys vector
            m_keys.insert(m_keys.begin() + keyOffset, key.begin(), key.end());
            m_data.insert(m_data.begin() + dataOffset, Data(key.size(), value));
            
            // return a pair that contains an iterator to the current location
            // of the newly inserted object and true, signifying that the
            // insert was done.
            return std::make_pair(iterator(this, dataOffset, keyOffset), true);
        }
        else {
            // insertion key is greater than the current key, so continue
            // iterating
            keyOffset += m_data[dataOffset].keyLength;
            ++dataOffset;
        }
    }
    
    // insert at the end
    m_keys.insert(m_keys.end(), key.begin(), key.end());
    m_data.insert(m_data.end(), Data(key.size(), value));

    return std::make_pair(iterator(this, dataOffset, keyOffset), true);
}
   
template<typename T>
void PackedStringMap<T>::erase(const_iterator const& it)
{
    if (this != it.m_stringMap) {
        return;
    }
    
    Data& data = m_data[it.m_dataOffset];
    m_keys.erase(m_keys.begin() + it.m_keyOffset, m_keys.begin() + it.m_keyOffset + data.keyLength);
    m_data.erase(m_data.begin() + it.m_dataOffset);
}

template<typename T>
typename PackedStringMap<T>::size_type PackedStringMap<T>::erase(key_type const& key)
{
    iterator it = find(key);
    if (it != end()) {
        erase(it);
        return 1;
    }
    
    return 0;
}

template<typename T>
typename PackedStringMap<T>::iterator PackedStringMap<T>::find(key_type const& key)
{
    size_t keyOffset = 0;
    size_t dataOffset = 0;
    findPriv(key, dataOffset, keyOffset);
    return iterator(this, dataOffset, keyOffset);
}

template<typename T>
typename PackedStringMap<T>::const_iterator PackedStringMap<T>::find(key_type const& key) const
{
    size_t keyOffset = 0;
    size_t dataOffset = 0;
    findPriv(key, dataOffset, keyOffset);
    return const_iterator(this, dataOffset, keyOffset);
}

template<typename T>
void PackedStringMap<T>::findPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const
{
    while (dataOffset < m_data.size()) {
        if (key.size() == m_data[dataOffset].keyLength) {
            int compResult = key.compare(0, key.size(), &m_keys[keyOffset], m_data[dataOffset].keyLength);
            if (0 == compResult) {
                return;
            }
            else if (compResult < 0) {
                break;
            }
        }

        keyOffset += m_data[dataOffset].keyLength;
        ++dataOffset;
    }
    
    dataOffset = m_data.size();
    keyOffset = m_keys.size();
}

template<typename T>
typename PackedStringMap<T>::size_type PackedStringMap<T>::count(key_type const& key) const
{
    return find(key) != end() ? 1 : 0;
}

template<typename T>
typename PackedStringMap<T>::iterator PackedStringMap<T>::lowerBound(key_type const& key)
{
    size_t dataOffset = 0;
    size_t keyOffset = 0;
    lowerBoundPriv(key, dataOffset, keyOffset);
    return iterator(this, dataOffset, keyOffset);
}

template<typename T>
typename PackedStringMap<T>::const_iterator PackedStringMap<T>::lowerBound(key_type const& key) const
{
    size_t dataOffset = 0;
    size_t keyOffset = 0;
    lowerBoundPriv(key, dataOffset, keyOffset);
    return const_iterator(this, dataOffset, keyOffset);
}

template<typename T>
void PackedStringMap<T>::lowerBoundPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const
{
    while (dataOffset < m_data.size()) {
        // if the supplied key >= the stored key, we've found the lower bound
        if (key.compare(0, key.size(), &m_keys[keyOffset], m_data[dataOffset].keyLength) <= 0) {
            return;
        }
        else {
            keyOffset += m_data[dataOffset].keyLength;
            ++dataOffset;
        }
    }

    dataOffset = m_data.size();
    keyOffset = m_keys.size();
}

template<typename T>
typename PackedStringMap<T>::iterator PackedStringMap<T>::upperBound(key_type const& key)
{
    size_t dataOffset = 0;
    size_t keyOffset = 0;
    upperBoundPriv(key, dataOffset, keyOffset);
    return iterator(this, dataOffset, keyOffset);
}

template<typename T>
typename PackedStringMap<T>::const_iterator PackedStringMap<T>::upperBound(key_type const& key) const
{
    size_t dataOffset = 0;
    size_t keyOffset = 0;
    upperBoundPriv(key, dataOffset, keyOffset);
    return const_iterator(this, dataOffset, keyOffset);
}

template<typename T>
void PackedStringMap<T>::upperBoundPriv(key_type const& key, size_t& dataOffset, size_t& keyOffset) const
{
    while (dataOffset < m_data.size()) {
        if (key.compare(0, key.size(), &m_keys[keyOffset], m_data[dataOffset].keyLength) < 0) {
            return;
        }
        else {
            keyOffset += m_data[dataOffset].keyLength;
            ++dataOffset;
        }
    }

    dataOffset = m_data.size();
    keyOffset = m_keys.size();
}

template<typename T>
std::ostream& PackedStringMap<T>::print(std::ostream& os) const
{
    size_t dataOffset = 0;
    size_t keyOffset = 0;
    if (m_data.empty()) {
        os << "<empty>";
    }
    
    while (dataOffset < m_data.size()) {
        os << "["
            << "'" << std::string(&m_keys[keyOffset], m_data[dataOffset].keyLength) << "':"
            << m_data[dataOffset].value
            << "]";

        keyOffset += m_data[dataOffset].keyLength;
        ++dataOffset;
    }
    
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, PackedStringMap<T> const& rhs)
{
    return rhs.print(os);
}

////////////////////////////////////////////////////////////////////////////////
/// PackedStringMap::Iterator Implementation
////////////////////////////////////////////////////////////////////////////////

template<typename T>
PackedStringMapIterator<T>::PackedStringMapIterator()
: m_stringMap(NULL),
  m_dataOffset(std::numeric_limits<size_t>::max()),
  m_keyOffset(std::numeric_limits<size_t>::max())
{}

template<typename T>
PackedStringMapIterator<T>::PackedStringMapIterator(
    PackedStringMap<T>* stringMap,
    size_t dataOffset,
    size_t keyOffset)
: m_stringMap(stringMap),
  m_dataOffset(dataOffset),
  m_keyOffset(keyOffset)
{}
        
template<typename T>
PackedStringMapIterator<T>::PackedStringMapIterator(PackedStringMapIterator<T> const& rhs)
: m_stringMap(rhs.m_stringMap),
  m_dataOffset(rhs.m_dataOffset),
  m_keyOffset(rhs.m_keyOffset)
{}
        
template<typename T>
PackedStringMapIterator<T>::~PackedStringMapIterator()
{}
        
template<typename T>
PackedStringMapIterator<T>& PackedStringMapIterator<T>::operator=(PackedStringMapIterator<T> const& rhs)
{
    if (&rhs == this) {
        return *this;
    }
    
    m_stringMap = rhs.m_stringMap;
    m_dataOffset = rhs.m_dataOffset;
    m_keyOffset = rhs.m_keyOffset;
}
        
template<typename T>
T& PackedStringMapIterator<T>::operator*()
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        throw std::out_of_range("PackedStringMap::Iterator::operator*");
    }
    
    return m_stringMap->m_data[m_dataOffset].value;
}
        
template<typename T>
T const& PackedStringMapIterator<T>::operator*() const
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        throw std::out_of_range("PackedStringMap::Iterator::operator*");
    }
    
    return m_stringMap->m_data[m_dataOffset].value;
}
        
template<typename T>
T* PackedStringMapIterator<T>::operator->()
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        return NULL;
    }
    
    return &(m_stringMap->m_data[m_dataOffset].value);
}
        
template<typename T>
T const* PackedStringMapIterator<T>::operator->() const
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        return NULL;
    }
    
    return &(m_stringMap->m_data[m_dataOffset].value);
}

template<typename T>
PackedStringMapIterator<T>& PackedStringMapIterator<T>::operator++()
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        return *this;
    }
    
    m_keyOffset += m_stringMap->m_data[m_dataOffset].keyLength;
    ++m_dataOffset;

    return *this;
}
        
template<typename T>
PackedStringMapIterator<T> PackedStringMapIterator<T>::operator++(int)
{
    if (!m_stringMap || m_dataOffset >= m_stringMap->m_data.size()) {
        return *this;
    }
    
    size_t oldDataOffset = m_dataOffset;
    size_t oldKeyOffset = m_keyOffset;

    m_keyOffset += m_stringMap->m_data[m_dataOffset].keyLength;
    ++m_dataOffset;
    
    return PackedStringMapIterator(m_stringMap, oldDataOffset, oldKeyOffset);
}
        
template<typename T>
PackedStringMapIterator<T>& PackedStringMapIterator<T>::operator--()
{
    if (!m_stringMap || m_dataOffset > m_stringMap->m_data.size()) {
        return *this;
    }
    
    --m_dataOffset;
    m_keyOffset -= m_stringMap->m_data[m_dataOffset].keyLength;

    return *this;
}
        
template<typename T>
PackedStringMapIterator<T> PackedStringMapIterator<T>::operator--(int)
{
    if (!m_stringMap || m_dataOffset > m_stringMap->m_data.size()) {
        return *this;
    }
    
    size_t oldDataOffset = m_dataOffset;
    size_t oldKeyOffset = m_keyOffset;

    --m_dataOffset;
    m_keyOffset -= m_stringMap->m_data[m_dataOffset].keyLength;
    
    return PackedStringMapIterator(m_stringMap, oldDataOffset, oldKeyOffset);
}

template<typename T>
bool operator==(PackedStringMapIterator<T> const& lhs, PackedStringMapIterator<T> const& rhs)
{
    return lhs.m_stringMap == rhs.m_stringMap
        && lhs.m_dataOffset == rhs.m_dataOffset
        && lhs.m_keyOffset == rhs.m_keyOffset;
}

template<typename T>
bool operator!=(PackedStringMapIterator<T> const& lhs, PackedStringMapIterator<T> const& rhs)
{
    return lhs.m_stringMap != rhs.m_stringMap
        || lhs.m_dataOffset != rhs.m_dataOffset
        || lhs.m_keyOffset != rhs.m_keyOffset;
}

} // namespace

#endif // INCLUDED
