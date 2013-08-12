#ifndef INCLUDED_AEGIS_AGTR_IMAGE_H
#define INCLUDED_AEGIS_AGTR_IMAGE_H

namespace agtr {

class Image
{
public:
    enum Format {
        Format_RGB8,
        Format_RGBA8,
        Format_RGB16,
        Format_RGBA16
    };

    Image();
    
    Image(Format format, std::vector<uint8_t> const& data, Extent const& size);

    ~Image();

    Extent const& size() const;
    
    std::vector<uint8_t> const& data() const;

private:
    
};

} // namespace

#endif // INCLUDED
