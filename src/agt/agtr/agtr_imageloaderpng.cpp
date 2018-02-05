#include <agtr_imageloaderpng.h>
#include <aftu_exception.h>
#include <aftl_logger.h>

namespace agtr {

namespace {

struct ImageHandler
{
    void infoCallback(png_structp pngData, png_infop pngInfo);
    void rowCallback(png_structp pngData, png_bytep pngRow, png_uint_32 rowNum, int pass);
    void endCallback(png_structp pngData, png_infop pngInfo);
    
    int width;
    int height;
    int colorType;
    int bitDepth;
    int channels;
    bool isInterlaced;
    int numberOfPasses;
    size_t rowbytes;
    Image::DataPtr data;
};

Image::Format pngColorTypeToImageFormat(int colorType)
{
    switch (colorType) {
    case PNG_COLOR_TYPE_GRAY:
        return Image::Format_GRAY;
        break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        return Image::Format_GRAY_ALPHA;
        break;
    case PNG_COLOR_TYPE_PALETTE:
        return Image::Format_PALETTE;
        break;
    case PNG_COLOR_TYPE_RGB:
        return Image::Format_RGB;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA: // or PNG_COLOR_TYPE_RGBA
        return Image::Format_RGBA;
        break;
    default:
        throw aftu::Exception("Unknown PNG Color Type: ") << colorType;
        break;
    }
}

void ImageHandler::infoCallback(png_structp pngData, png_infop pngInfo)
{
    width = png_get_image_width(pngData, pngInfo);
    height = png_get_image_height(pngData, pngInfo);
    colorType = static_cast<int>(png_get_color_type(pngData, pngInfo));
    bitDepth = static_cast<int>(png_get_bit_depth(pngData, pngInfo));
    channels = static_cast<int>(png_get_channels(pngData, pngInfo));
    isInterlaced = png_get_interlace_type(pngData, pngInfo) != PNG_INTERLACE_NONE;

    if (isInterlaced) {
        numberOfPasses = png_set_interlace_handling(pngData);
    } else {
        numberOfPasses = 1;
    }

    png_set_expand(pngData);
    png_set_gray_to_rgb(pngData);

    isInterlaced = png_get_interlace_type(pngData, pngInfo) != PNG_INTERLACE_NONE;

    if (isInterlaced) {
        numberOfPasses = png_set_interlace_handling(pngData);
    } else {
        numberOfPasses = 1;
    }
    
    png_read_update_info(pngData, pngInfo);
    
    colorType = static_cast<int>(png_get_color_type(pngData, pngInfo));
    bitDepth = static_cast<int>(png_get_bit_depth(pngData, pngInfo));
    channels = static_cast<int>(png_get_channels(pngData, pngInfo));
    
    rowbytes = png_get_rowbytes(pngData, pngInfo);
    data = Image::DataPtr(new Image::Data(rowbytes * height));
}

void ImageHandler::rowCallback(png_structp pngData, png_bytep pngRow, png_uint_32 rowNum, int pass)
{
    if (isInterlaced && pass != 0) {
        png_bytep oldRow = reinterpret_cast<png_bytep>(&((*data)[rowNum * rowbytes]));
        png_progressive_combine_row(pngData, oldRow, pngRow);
    }
    
    // copy the data
    std::memcpy(&((*data)[rowNum * rowbytes]), pngRow, rowbytes);
}

void ImageHandler::endCallback(png_structp pngData, png_infop pngInfo)
{
    AFTL_LOG_INFO << "ImagePNG::endCallback" << AFTL_LOG_END;
}

} // namespace

void infoCallback_c(png_structp pngData, png_infop pngInfo)
{
    ImageHandler* handler = reinterpret_cast<ImageHandler*>(png_get_progressive_ptr(pngData));
    handler->infoCallback(pngData, pngInfo);
}

void rowCallback_c(png_structp pngData, png_bytep pngRow, png_uint_32 rowNum, int pass)
{
    ImageHandler* handler = reinterpret_cast<ImageHandler*>(png_get_progressive_ptr(pngData));
    handler->rowCallback(pngData, pngRow, rowNum, pass);
}

void endCallback_c(png_structp pngData, png_infop pngInfo)
{
    ImageHandler* handler = reinterpret_cast<ImageHandler*>(png_get_progressive_ptr(pngData));
    handler->endCallback(pngData, pngInfo);
}

ImageLoaderPNG::ImageLoaderPNG()
{
    png_uint_32 pngVersion = png_access_version_number();
    AFTL_LOG_INFO << "ImagePNG: libpng version is " << pngVersion << AFTL_LOG_END;
}

ImageLoaderPNG::~ImageLoaderPNG()
{}

ImageLoaderPNG::ImagePtr ImageLoaderPNG::load(aftfs::FileSystem& fileSystem, aftu::URL const& url)
{
    aftfs::FileSystem::DirectoryEntryPtr entry = fileSystem.directoryEntry(url);
    aftfs::FileSystem::FileReaderPtr fileReader = fileSystem.openFileReader(url);

    char* buffer = new char[entry->size()];
    size_t bytesRead = 0;
    fileReader->read(buffer, entry->size(), &bytesRead);

    if (png_sig_cmp(reinterpret_cast<png_const_bytep>(buffer), 0, 8) != 0) {
        // not a PNG file
        throw aftu::Exception("ImagePNG: Not a PNG file");
    }
    
    // create the structure for reading the PNG data
    png_structp pngData = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!pngData) {
        throw aftu::Exception("ImagePNG: Could not create read struct");
    }
    
    // create the structure for reading the PNG info
    png_infop pngInfo = png_create_info_struct(pngData);

    if (!pngInfo) {
        png_destroy_read_struct(&pngData, NULL, NULL);
        throw aftu::Exception("ImagePNG: Could not create info struct");
    }

    // if there is an error during reading the png, control flow will
    // come to this point, so we should clean up and return null
    if (setjmp(png_jmpbuf(pngData))) {
        png_destroy_read_struct(&pngData, &pngInfo, NULL);
        throw aftu::Exception("ImagePNG: setjmp returned non-zero");
    }

    ImageHandler imageHandler;
    png_set_progressive_read_fn(pngData, &imageHandler, infoCallback_c, rowCallback_c, endCallback_c);
    
    png_process_data(pngData, pngInfo, reinterpret_cast<png_bytep>(buffer), entry->size());
    
    // at this point the imageHandler has all the png data, so we can
    // now create an Image object from the data
    
    ImagePtr image(new Image(
        pngColorTypeToImageFormat(imageHandler.colorType),
        imageHandler.bitDepth,
        agtm::Size2d<unsigned int>(imageHandler.width, imageHandler.height),
        imageHandler.data));

    delete [] buffer;
    
    return image;
}

} // namespace
