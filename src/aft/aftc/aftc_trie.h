#ifndef INCLUDED_AEGIS_AFTC_TRIE_H
#define INCLUDED_AEGIS_AFTC_TRIE_H

#include <aftc_packedstringmap.h>
#include <ostream>

namespace aftc {

template<typename T>
class TrieIterator;

template<typename T>
class Trie;

template<typename T>
class TrieNode
{
    friend class TrieIterator<T>;
    friend class Trie<T>;
    
public:
    TrieNode();
    TrieNode(TrieNode<T> const& rhs);
    ~TrieNode();
    TrieNode<T>& operator=(TrieNode<T> const& rhs);
    
private:
    TrieNode<T>* m_ab[256];
    PackedStringMap<T>* m_strings;
};

/**
 * @class Trie
 *
 * @brief An implementation of a burst-trie container.
 *
 * This burst-trie implementation utilizes a cache-friendly data storage
 * mechanism that reduces the number of pointers to ensure that large
 * parts of the data are stored consecutively in memory. This reduces the
 * number of cache misses on lookup which can help prevent cpu stalls
 * while data is fetched from main memory.
 *
 * The underlying data store is basically an array that holds all string
 * keys inline with their respective values. Because this is a burst-trie,
 * the actual tree structure is kept to a minimum to reduce the number of
 * nodes needed to store the trie keys.
 */
template<typename T>
class Trie
{
    friend class TrieIterator<T>;
    
public:
    typedef std::string key_type;
    typedef std::pair<std::string, T> value_type;
    typedef TrieIterator<T> iterator;
    typedef const TrieIterator<T> const_iterator;
    typedef size_t size_type;
    
    Trie();
    explicit Trie(size_t burstSize);
    Trie(Trie<T> const& rhs);
    ~Trie();
    Trie<T>& operator=(Trie<T> const& rhs);
        
    bool empty() const;
    size_type size() const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    std::pair<iterator, bool> insert(value_type const& object);
    void erase(iterator it);
    size_t erase(std::string const& key);
    void erase(iterator first, iterator last);
    
    iterator find(std::string const& key);
    const_iterator find(std::string const& key) const;  

    std::ostream& print(std::ostream& os) const;
    
private:
    size_t m_burstSize;
    TrieNode<T> m_root;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Trie<T> const& trie);

template<typename T>
class TrieIterator
{
public:        
    TrieIterator();
    
    TrieIterator(TrieIterator<T> const& rhs);
    
    ~TrieIterator();
    
    TrieIterator<T>& operator=(TrieIterator<T> const& rhs);
    
    TrieIterator& operator++();
    
    TrieIterator operator++(int);
    
    T* operator->() const;
    
    T& operator*() const;

private:
    Trie<T>* m_trie;
    TrieNode<T>* m_node;
};

template<typename T>
bool operator==(TrieIterator<T> const& lhs, TrieIterator<T> const& rhs);

template<typename T>
bool operator!=(TrieIterator<T> const& lhs, TrieIterator<T> const& rhs);

////////////////////////////////////////
// Trie Implementation
////////////////////////////////////////

template<typename T>
Trie<T>::Trie()
: m_burstSize(7)
{}

template<typename T>
Trie<T>::Trie(size_t burstSize)
: m_burstSize(burstSize)
{}

template<typename T>
Trie<T>::Trie(Trie<T> const& rhs)
{
    // iterator through all the nodes, delete any allocated
    // memory and remove the nodes
}

template<typename T>
Trie<T>::~Trie()
{}

template<typename T>
Trie<T>& Trie<T>::operator=(Trie<T> const& rhs)
{
    return *this;
}

template<typename T>
bool Trie<T>::empty() const
{
    return false;
}

template<typename T>
typename Trie<T>::size_type Trie<T>::size() const
{
    return 0;
}

template<typename T>
std::pair<typename Trie<T>::iterator, bool> Trie<T>::insert(typename Trie<T>::value_type const& object)
{
    //std::string& key = object.first;
    //T& value = object.second;
    
    typename Trie<T>::iterator it;
    std::pair<typename Trie<T>::iterator, bool> result = std::make_pair(it, false);
    return result;
}

template<typename T>        
typename Trie<T>::iterator Trie<T>::find(std::string const& key)
{
}

template<typename T>
typename Trie<T>::const_iterator Trie<T>::find(std::string const& key) const
{
}

template<typename T>
std::ostream& Trie<T>::print(std::ostream& os) const
{
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Trie<T> const& trie)
{
    return trie.print(os);
}

////////////////////////////////////////
// TrieNode implementation
////////////////////////////////////////

template<typename T>
TrieNode<T>::TrieNode()
{}

template<typename T>
TrieNode<T>::~TrieNode()
{}

////////////////////////////////////////
// TrieIterator implementation
////////////////////////////////////////

template<typename T>
TrieIterator<T>::TrieIterator()
{}

template<typename T>
TrieIterator<T>::TrieIterator(TrieIterator<T> const& rhs)
{}

template<typename T>
TrieIterator<T>::~TrieIterator()
{}

template<typename T>
TrieIterator<T>& TrieIterator<T>::operator=(TrieIterator const& rhs)
{
    return *this;
}

template<typename T>
TrieIterator<T>& TrieIterator<T>::operator++()
{
    return *this;
}

template<typename T>
TrieIterator<T> TrieIterator<T>::operator++(int)
{
    return TrieIterator<T>();
}

} // namespace

#endif // INCLUDED
