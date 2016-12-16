#ifndef INCLUDED_AEGIS_AGTR_IMAGEPNG_H
#define INCLUDED_AEGIS_AGTR_IMAGEPNG_H

#include <agtr_image.h>
#include <aftfs_filesystem.h>
#include <aftu_url.h>
#include <memory>
#include <png.h>

namespace agtr {

class ImageLoaderPNG
{
public:
    typedef std::shared_ptr<agtr::Image> ImagePtr;

    ImageLoaderPNG();
    
    ~ImageLoaderPNG();
    
    ImagePtr load(aftfs::FileSystem& fileSystem, aftu::URL const& url);
};

} // namespace

#endif // INCLUDED
