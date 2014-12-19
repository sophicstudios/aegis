#ifndef INCLUDED_AEGIS_AGTR_IMAGE_H
#define INCLUDED_AEGIS_AGTR_IMAGE_H

#include <agtm_size2d.h>
#include <memory>
#include <vector>

namespace agtr {

class Image
{
public:
    typedef std::vector<uint8_t> Data;
    typedef std::shared_ptr<Data> DataPtr;
    
    enum Format {
        Format_RGB,
        Format_RGBA,
        Format_GRAY,
        Format_GRAY_ALPHA,
        Format_PALETTE
    };

    Image(Format format,
          uint32_t bitDepth,
          agtm::Size2d<unsigned int> const& size,
          DataPtr const& data);
    
    ~Image();

    Format format();
    
    uint32_t bitDepth() const;
    
    agtm::Size2d<unsigned int> const& size() const;
    
    DataPtr const& data() const;

private:
    Format m_format;
    uint32_t m_bitDepth;
    agtm::Size2d<unsigned int> m_size;
    DataPtr m_data;
};

} // namespace

#endif // INCLUDED
