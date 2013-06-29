#include <aftio_outputstream.h>

namespace aegis {
namespace aftio {

OutputStream::OutputStream()
{}

OutputStream::~OutputStream()
{}

size_t OutputStream::write(int8_t byte)
{
    return writeImpl(byte);
}

size_t OutputStream::write(int8_t const* const buffer, size_t count)
{
    return writeImpl(buffer, count);
}

size_t OutputStream::write(std::vector<int8_t> const& buffer, size_t count)
{
    return writeImpl(buffer, count);
}

} // namespace
} // namespace
