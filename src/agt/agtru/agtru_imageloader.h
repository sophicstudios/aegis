#ifndef INCLUDED_AEGIS_AGTRU_IMAGELOADER_H
#define INCLUDED_AEGIS_AGTRU_IMAGELOADER_H

#include <agtr_image.h>
#include <aftu_url.h>
#include <tr1/memory>

namespace agtru {

class ImageLoader
{
public:
    ImageLoader();
    
    virtual ~ImageLoader() = 0;
    
    virtual std::tr1::shared_ptr<Image> load(aftu::Url const& url) = 0;
};

} // namespace

#endif // INCLUDES
