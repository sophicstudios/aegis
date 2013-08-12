#ifndef INCLUDED_AEGIS_AFTU_HEXPRINTER_H
#define INCLUDED_AEGIS_AFTU_HEXPRINTER_H

#include <iosfwd>

namespace aftu {

/**
 * An iostreams compatible object to print out the contents
 * of a buffer in hex format
 */
class HexPrinter
{
public:
    HexPrinter(char const* const buffer, size_t length);
    
    HexPrinter(char const* const buffer, size_t length, size_t bytesPerLine);
    
    ~HexPrinter();

private:    
    friend std::ostream& operator<<(std::ostream& os, HexPrinter const& rhs);

    char const* const m_buffer;
    size_t m_length;
    size_t m_bytesPerLine;
};

/**
 * An iostreams compatible object to print out the contents
 * of a buffer in hex format in one continuous stream.
 */
class InlineHexPrinter
{
public:
    InlineHexPrinter(char const* const buffer, size_t length);
    
    ~InlineHexPrinter();
    
private:
    friend std::ostream& operator<<(std::ostream& os, InlineHexPrinter const& rhs);
    
    char const* const m_buffer;
    size_t m_length;
};

std::ostream& operator<<(std::ostream& os, HexPrinter const& rhs);

std::ostream& operator<<(std::ostream& os, InlineHexPrinter const& rhs);

} // namespace

#endif // INCLUDED
