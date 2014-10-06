#ifndef INCLUDED_AEGIS_AGTR_IMAGE_H
#define INCLUDED_AEGIS_AGTR_IMAGE_H

#include <agtm_size2d.h>

namespace agtr {

class Image
{
public:
    enum ColorType {
        ColorType_RGB,
        ColorType_RGBA,
        ColorType_GRAY,
        ColorType_GRAY_ALPHA,
        ColorType_PALETTE
    };

    Image();
    
    ~Image();

    virtual ColorType colorType() const = 0;
    
    virtual uint32_t bitDepth() const = 0;
    
    virtual agtm::Size2d const& size() const = 0;
    
    virtual std::vector<uint8_t> const& data() const = 0;

private:
    
};

} // namespace

#endif // INCLUDED
