#ifndef INCLUDED_AEGIS_AGTG_COLORRGBA_H
#define INCLUDED_AEGIS_AGTG_COLORRGBA_H

#include <aftm_round.h>
#include <afts_stdint.h>
#include <string>

namespace aegis {
namespace agtg {

template<typename T>
class ColorRGBA
{
public:
    ColorRGBA();

    /**
     * Construct a RGB color object using a string, which can be of any
     * form following the standard CSS string formats, such as:
     *
     * rgba(255, 255, 255, 1.0)
     * rgba(100%, 100%, 100%, 1.0)
     * #aabbccff
     * rgb(255, 255, 255)
     * rgb(100%, 100%, 100%)
     * #aabbcc
     *
     * The last three will default the alpha bit to 1 (fully opaque)
     */
    explicit ColorRGBA(std::string const& str);
    
    /**
     * Construct a color object using a 32-bit integer where each of the four
     * bytes holds the value for red, green, blue and alpha.
     *
     * Examples:
     *  Color red(0xff0000ff);
     *  Color lightGray(0xccccccff);
     */
    explicit ColorRGBA(uint32_t value);

    ColorRGBA(T red, T green, T blue, T alpha = static_cast<T>(1.0));
            
    ColorRGBA(ColorRGBA const& rhs);
    
    ColorRGBA& operator=(ColorRGBA const& rhs);
    
    T red() const;
    
    T green() const;
    
    T blue() const;
    
    T alpha() const;
    
    uint32_t asInt() const;
    
    std::string asCSSString() const;
    
    std::string asCSSHex() const;
    
private:
    double m_red;
    double m_green;
    double m_blue;
    double m_alpha;
};

template<typename T>
ColorRGBA<T>::ColorRGBA()
: m_red(0.0),
  m_green(0.0),
  m_blue(0.0),
  m_alpha(1.0)
{}

template<typename T>
ColorRGBA<T>::ColorRGBA(std::string const& colorStr)
: m_red(0.0),
  m_green(0.0),
  m_blue(0.0),
  m_alpha(1.0)
{
    // parse color string
}

template<typename T>
ColorRGBA<T>::ColorRGBA(uint32_t value)
: m_red(static_cast<T>((value >> 24) & 0xff) / static_cast<T>(255.0)),
  m_green(static_cast<T>((value >> 16) & 0xff) / static_cast<T>(255.0)),
  m_blue(static_cast<T>((value >> 8) & 0xff) / static_cast<T>(255.0)),
  m_alpha(static_cast<T>(value & 0xff) / static_cast<T>(255.0))
{}

template<typename T>
ColorRGBA<T>::ColorRGBA(T red, T green, T blue, T alpha)
: m_red(red > 1.0 ? 1.0 : red < 0.0 ? 0.0 : red),
  m_green(green > 1.0 ? 1.0 : green < 0.0 ? 0.0 : green),
  m_blue(blue > 1.0 ? 1.0 : blue < 0.0 ? 0.0 : blue),
  m_alpha(alpha > 1.0 ? 1.0 : alpha < 0.0 ? 0.0 : alpha)
{}

template<typename T>
ColorRGBA<T>::ColorRGBA(ColorRGBA<T> const& rhs)
: m_red(rhs.m_red),
  m_green(rhs.m_green),
  m_blue(rhs.m_blue),
  m_alpha(rhs.m_alpha)
{}

template<typename T>
ColorRGBA<T>& ColorRGBA<T>::operator=(ColorRGBA<T> const& rhs)
{
    m_red = rhs.m_red;
    m_green = rhs.m_green;
    m_blue = rhs.m_blue;
    m_alpha = rhs.m_alpha;
    return *this;
}

template<typename T>
T ColorRGBA<T>::red() const
{
    return m_red;
}

template<typename T>
T ColorRGBA<T>::green() const
{
    return m_green;
}

template<typename T>
T ColorRGBA<T>::blue() const
{
    return m_blue;
}

template<typename T>
T ColorRGBA<T>::alpha() const
{
    return m_alpha;
}

template<typename T>
uint32_t ColorRGBA<T>::asInt() const
{
    return ((static_cast<unsigned int>(aftm::Round::halfUp(m_red * 255.0, 0)) & 0xff) << 24)
        | ((static_cast<unsigned int>(aftm::Round::halfUp(m_green * 255.0, 0)) & 0xff) << 16)
        | ((static_cast<unsigned int>(aftm::Round::halfUp(m_blue * 255.0, 0)) & 0xff) << 8)
        | (static_cast<unsigned int>(aftm::Round::halfUp(m_alpha * 255.0, 0)) & 0xff);
}

template<typename T>
std::string ColorRGBA<T>::asCSSString() const
{
    return std::string("rgba(0, 0, 0, 1.0)");
}
    
template<typename T>
std::string ColorRGBA<T>::asCSSHex() const
{
    return std::string("#000000ff");
}

} // namespace
} // namespace

#endif // INCLUDED
