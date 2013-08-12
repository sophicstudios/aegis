#ifndef INCLUDED_AEGIS_AGTRU_IMAGELOADERPNG_H
#define INCLUDED_AEGIS_AGTRU_IMAGELOADERPNG_H

#include <agtru_imageloader.h>
#include <agtr_image.h>
#include <aftfs_filesystem.h>
#include <aftu_url.h>
#include <tr1/memory>

namespace agtru {

class ImageLoaderPng
{
public:
    ImageLoaderPng();

    ImageLoaderPng(std::tr1::shared_ptr<aftfs::FileSystem> const& fileSystem);
    
    ~ImageLoaderPng();

    virtual std::tr1::shared_ptr<Image> load(aftu::Url const& url);

private:
    std::tr1::shared_ptr<aftfs::FileSystem> fileSystem;
};

} // namespace

#endif // INCLUDED
