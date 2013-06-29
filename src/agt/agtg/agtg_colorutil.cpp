#include <agtg_colorutil.h>
#include <aftu_stringutil.h>

namespace aegis {
namespace agtg {

namespace {

inline bool isHexColor(std::string const& color)
{
    return (color.size() == 4 || color.size() == 7) && color[0] == '#';
}

inline bool isRGBColorString(std::string const& color)
{
    return color.size() > 4
        && color[0] == 'r'
        && color[1] == 'g'
        && color[2] == 'b'
        && color[3] == '('
        && color[color.size()-1] == ')';
}

uint8_t convertHexChar(char c)
{
    switch (c) {
        case 'F':
        case 'E':
        case 'D':
        case 'C':
        case 'B':
        case 'A':
            return (c - 'A') + 10;
            break;
        case 'f':
        case 'e':
        case 'd':
        case 'c':
        case 'b':
        case 'a':
            return (c - 'a') + 10;
            break;
        case '9':
        case '8':
        case '7':
        case '6':
        case '5':
        case '4':
        case '3':
        case '2':
        case '1':
        case '0':
            return (c - '0');
            break;
        default:
            return 0;
            break;
    }
}

uint8_t convertHexByte(char hi, char low)
{
    uint8_t result = (convertHexChar(hi) << 4) | convertHexChar(low);
}

ColorUtil::Result parseHexColor(agtg::Color& output, std::string const& color)
{
    size_t len = color.size();
    if (len == 4) {
        // handles the case where the hex color is represented in
        // the form "#RGB"
        output.set(
            static_cast<float>(convertHexByte(color[1], color[1])) / 255.0f,
            static_cast<float>(convertHexByte(color[2], color[2])) / 255.0f,
            static_cast<float>(convertHexByte(color[3], color[3])) / 255.0f,
            1.0f);
            
        return ColorUtil::Result_OK;
    }

    if (len == 7) {
        // handles the case where the hex color is represented in
        // the form "#RRGGBB"
        output.set(
            static_cast<float>(convertHexByte(color[1], color[2])) / 255.0f,
            static_cast<float>(convertHexByte(color[3], color[4])) / 255.0f,
            static_cast<float>(convertHexByte(color[5], color[6])) / 255.0f,
            1.0f);

        return ColorUtil::Result_OK;
    }
    
    return ColorUtil::Result_INVALID_COLOR_STRING;
}

ColorUtil::Result parseRGBColor(agtg::Color& output, std::string const& color)
{
    // An rgb color is of the form "rgb(red-val, green-val, blue-val)",
    // where 'red-val', 'green-val' and 'blue-val' can be a number in the range
    // [0, 255], a percent (in the form '[0-9]{1, 2}%'), or a decimal in the
    // range [0.0, 1.0].
    
    // we assume the string has been sanitized prior to being fed to this
    // method, so the first 4 characters can be discarded as they are "rgb(" and
    // the last character can be discarded, as it is ')'.
    
    std::string::const_iterator it = color.begin() + 4; // skip "rgb("
    std::string::const_iterator end = color.end() - 1; // skip ")"
    
    std::vector<std::string> tokens;
    aftu::StringUtil::tokenize(&tokens, it, end, ',', false);

    return ColorUtil::Result_INVALID_COLOR_STRING;
}

struct Components
{
    float red;
    float green;
    float blue;
};

ColorUtil::Result parseColorName(agtg::Color& output, std::string const& color)
{
    return ColorUtil::Result_INVALID_COLOR_STRING;
}

} // namespace

uint16_t ColorUtil::toRGB565(agtg::Color const& color)
{
    return (((static_cast<uint16_t>(color.red() * 255.0f) >> 3) & 0x001F) << 11)
        | (((static_cast<uint16_t>(color.green() * 255.0f) >> 2) & 0x003F) << 5)
        | ((static_cast<uint16_t>(color.blue() * 255.0f) >> 3) & 0x001F);
    
}

agtg::Color ColorUtil::fromRGB565(uint16_t color)
{
    return agtg::Color(
        static_cast<float>(((color >> 11) & 0x001F) << 3) / 255.0f,
        static_cast<float>(((color >> 5) & 0x003F) << 2) / 255.0f,
        static_cast<float>((color & 0x001F) << 3) / 255.0f,
        1.0f);
}

ColorUtil::Result ColorUtil::fromString(agtg::Color& output, std::string const& colorString)
{
    std::string trimmedColorString = aftu::StringUtil::toLowerTrimCopy(colorString);

    if (trimmedColorString.empty()) {
        return ColorUtil::Result_INVALID_COLOR_STRING;
    }
    
    size_t length = trimmedColorString.size();
    
    if (isHexColor(trimmedColorString)) {
        return parseHexColor(output, trimmedColorString);
    }    
    else if (isRGBColorString(trimmedColorString))
    {
        return parseRGBColor(output, trimmedColorString);
    }
    else {
        return parseColorName(output, trimmedColorString);
    }
}

} // namespace
} // namespace
