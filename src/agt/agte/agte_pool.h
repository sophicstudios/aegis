#ifndef INCLUDED_AGTE_POOL_H
#define INCLUDED_AGTE_POOL_H

#include <memory>
#include <vector>

namespace agte {

/**
 * @class BasePool
 */
class BasePool
{
public:
    /**
     * Constructs a Pool to hold elements of a given size. The pool
     * will pre-allocate chunks of memory in _batchSize_ increments.
     * The total number of bytes per batch is _batchSize_ * _elementSize_
     */
    BasePool(size_t elementSize, size_t batchSize);

    /**
     * Destroys all memory pools. Take care that you properly
     * destroy all objects allocated from the pool before the pool
     * itself is destroyed.
     */
    virtual ~BasePool();

    /**
     * Returns the current size of the pool, which is the
     * actual number of elements in the pool.
     */
    const size_t size() const;

    /**
     * Returns the capacity of the pool, which is the
     * total number of elements it can hold.
     */
    const size_t capacity() const;

    /**
     * Reserves capacity in the pool to hold at least
     * _count_ elements. Reserving a count that is less
     * than the current capcity is a noop (i.e. the pool will
     * not shrink, only expand).
     */
    void reserve(size_t count);

    /**
     * Resizes the pool to the specified
     * count. In the course of resizing the pool,
     * the capacity may need to be increased. resizing
     * the pool to a smaller size will invalidate any
     * objects that are outside the range of the new
     * size of the pool.
     */
    void resize(size_t count);

    /**
     * Returns a pointer to the element at position _i_ in the pool. If _i_
     * is greater than the current size, this method has undefined behavior.
     */
    void* operator[](size_t i);

    /**
     * Gets a pointer to the element at position _i_ in the pool. If _i_
     * greater than the current size, this method will throw an
     * out_of_range exception.
     */
    void* at(size_t i);

    /**
     * Destroys the element at position _i_ in the pool. Derived
     * classes must implement this based on the type of object stored
     * in the pool.
     */
    virtual void destroy(size_t i) = 0;

protected:
    size_t _elementSize;
    size_t _batchSize;
    size_t _capacity;
    size_t _size;
    std::vector<char*> _pools;
};

/**
 * @class ComponentPool
 *
 * Handles the efficient containment of a specific component type for a set
 * of entities.
 */
template<typename T, size_t BatchSize = 500>
class Pool : public BasePool
{
public:
    /**
     * Constructor. Creates a Pool to hold objects of a certain type.
     */
    Pool();

    /**
     * Destructor.
     */
    virtual ~Pool();

    virtual void destroy(size_t i);
};

template<typename T, size_t BatchSize>
Pool<T, BatchSize>::Pool()
: BasePool(sizeof(T), BatchSize)
{
}

template<typename T, size_t BatchSize>
Pool<T, BatchSize>::~Pool()
{
}

template<typename T, size_t BatchSize>
void Pool<T, BatchSize>::destroy(size_t i)
{
    T* ptr = static_cast<T*>(at(i));
    ptr->~T();
}

} // namespace agte

#endif // INCLUDED
