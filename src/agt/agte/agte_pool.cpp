#include <afts_assert.h>
#include <agte_pool.h>
#include <stdexcept>

namespace agte {

BasePool::BasePool(size_t elementSize, size_t batchSize)
: _elementSize(elementSize)
, _batchSize(batchSize)
, _capacity(0)
, _size(0)
{
}

BasePool::~BasePool()
{
    for (auto pool : _pools) {
        delete[] pool;
    }
}

const size_t BasePool::size() const
{
    return _size;
}

const size_t BasePool::capacity() const
{
    return _capacity;
}

void BasePool::reserve(size_t count)
{
    while (_capacity < count) {
        char* pool = new char[_batchSize * _elementSize];
        _pools.push_back(pool);
        _capacity += _batchSize;
    }
}

void BasePool::resize(size_t count)
{
    if (_size < count) {
        if (_capacity < count) {
            reserve(count);
        }
        _size = count;
    }
}

void* BasePool::operator[](size_t i)
{
    AFTS_ASSERT_DEBUG(i < _size);
    return _pools[i / _batchSize] + ((i % _batchSize) * _elementSize);
}

void* BasePool::at(size_t i)
{
    if (_size < i) {
        throw std::out_of_range("BasePool::_size < i");
    }

    return (*this)[i];
}

} // namespace agte
