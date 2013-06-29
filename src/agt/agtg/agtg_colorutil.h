#ifndef INCLUDE_AEGIS_AGTG_COLORUTIL_H
#define INCLUDE_AEGIS_AGTG_COLORUTIL_H

#include <agtg_color.h>

namespace aegis {
namespace agtg {

struct ColorUtil
{
    enum Result {
        Result_OK = 0,
        Result_INVALID_COLOR_STRING,
        Result_UNKNOWN
    };
    
    // Converts a RGBA color object to a 16-bit, 565 color format
    // (RRRR RGGG GGGB BBBB). This is done by dropping the alpha component,
    // then shifting the 8-bit red, green and blue components to the right
    // by 3, 2, and 3 bits, respectively.
    static uint16_t toRGB565(agtg::Color const& inputColor);

    // Converts a 16-bit color in 565 format (RRRR RGGG GGGB BBBB) by
    // first converting each part to an 8-bit value, shifting up by 
    // 3, 2 and 3 bits, respectively, then setting the alpha to 100%
    static agtg::Color fromRGB565(uint16_t inputColor);
    
    // Creates a color object from a string value that follows the CSS
    // specification for color formats as defined in the document
    // http://www.w3.org/TR/css3-color/
    static Result fromString(agtg::Color& output, std::string const& colorString);
};

} // namespace
} // namespace

#endif // INCLUDE
