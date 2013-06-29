#include <aftio_inputstream.h>

namespace aegis {
namespace aftio {

InputStream::InputStream()
{}

InputStream::~InputStream()
{}

size_t InputStream::read(int8_t byte)
{
    return readImpl(byte);
}

size_t InputStream::read(int8_t* buffer, size_t count)
{
    return readImpl(buffer, count);
}

size_t InputStream::read(std::vector<int8_t>& buffer, size_t count)
{
    return readImpl(buffer, count);
}

void InputStream::seek(size_t location)
{
    seekImpl(location);
}

} // namespace
} // namespace
