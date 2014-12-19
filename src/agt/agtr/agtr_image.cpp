#include <agtr_image.h>

namespace agtr {

Image::Image(Format format,
             uint32_t bitDepth,
             agtm::Size2d<unsigned int> const& size,
             DataPtr const& data)
: m_format(format),
  m_bitDepth(bitDepth),
  m_size(size),
  m_data(data)
{}

Image::~Image()
{}

Image::Format Image::format()
{
    return m_format;
}

uint32_t Image::bitDepth() const
{
    return m_bitDepth;
}

agtm::Size2d<unsigned int> const& Image::size() const
{
    return m_size;
}

Image::DataPtr const& Image::data() const
{
    return m_data;
}

} // namespace
