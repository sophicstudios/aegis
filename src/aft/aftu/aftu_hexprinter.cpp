#include <aftu_hexprinter.h>
#include <iomanip>
#include <ostream>

namespace aftu {

namespace {

size_t const DEFAULT_BYTES_PER_LINE = 16;

char const PRINTABLE_CHARS[256] = {
    '.', '.', '.', '.', '.', '.', '.', '.',  //   0
    '.', '.', '.', '.', '.', '.', '.', '.',  //   8
    '.', '.', '.', '.', '.', '.', '.', '.',  //  16
    '.', '.', '.', '.', '.', '.', '.', '.',  //  24
    ' ', '!', '\"','#', '$', '%', '&', '\'', //  32
    '(', ')', '*', '+', ',', '-', '.', '/',  //  40
    '0', '1', '2', '3', '4', '5', '6', '7',  //  48
    '8', '9', ':', ';', '<', '=', '>', '?',  //  56
    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',  //  64
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',  //  72
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',  //  80
    'X', 'Y', 'Z', '[', '\\',']', '^', '_',  //  88
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',  //  96
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',  // 104
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w',  // 112
    'x', 'y', 'z', '{', '|', '}', '~', '.',  // 120
    '.', '.', '.', '.', '.', '.', '.', '.',  // 128
    '.', '.', '.', '.', '.', '.', '.', '.',  // 136
    '.', '.', '.', '.', '.', '.', '.', '.',  // 144
    '.', '.', '.', '.', '.', '.', '.', '.',  // 152
    '.', '.', '.', '.', '.', '.', '.', '.',  // 160
    '.', '.', '.', '.', '.', '.', '.', '.',  // 168
    '.', '.', '.', '.', '.', '.', '.', '.',  // 176
    '.', '.', '.', '.', '.', '.', '.', '.',  // 184
    '.', '.', '.', '.', '.', '.', '.', '.',  // 192
    '.', '.', '.', '.', '.', '.', '.', '.',  // 200
    '.', '.', '.', '.', '.', '.', '.', '.',  // 208
    '.', '.', '.', '.', '.', '.', '.', '.',  // 216
    '.', '.', '.', '.', '.', '.', '.', '.',  // 224
    '.', '.', '.', '.', '.', '.', '.', '.',  // 232
    '.', '.', '.', '.', '.', '.', '.', '.',  // 240
    '.', '.', '.', '.', '.', '.', '.', '.'   // 248
};

inline void printHexBufferLine(std::ostream& os, unsigned char const* const buffer, size_t i, size_t remaining, size_t bytesPerLine)
{
    // print the memory location of the current line of the buffer
    os << std::setfill('0') << std::setw(sizeof(unsigned char*) * 2) << std::hex << i << ": ";
    for (size_t j = 0; j < bytesPerLine; ++j) {
        if (j < remaining) {
            os << std::setw(2) << std::hex << static_cast<unsigned int>(buffer[j]);
        }
        else {
            
            os << "  ";
        }
        
        if ((j + 1) % 2 == 0) {
            os << ' ';
        }
    }
    
    os << ' ';
    
    for (size_t j = 0; j < bytesPerLine && j < remaining; ++j) {
        os << PRINTABLE_CHARS[buffer[j]];
    }
}

void printHexBuffer(std::ostream& os, unsigned char const* const buffer, size_t length, size_t bytesPerLine)
{
    // print the first line
    printHexBufferLine(os, buffer, 0, length, bytesPerLine);
    for (size_t i = bytesPerLine; i < length; i += bytesPerLine) {
        // if not the first line of output, start a new line
        os << "\n";

        printHexBufferLine(os, buffer + i, i, length - i, bytesPerLine);        
    }
}

void printInlineHexBuffer(std::ostream& os, unsigned char const* const buffer, size_t length)
{
    os << std::setfill('0') << std::setw(2) << std::hex;

    for (size_t i = 0; i < length; ++i) {
        os << static_cast<unsigned int>(buffer[i]);
        
        if ((i + 1) % 2 == 0) {
            os << ' ';
        }
    }
}

} // namespace

HexPrinter::HexPrinter(char const* const buffer, size_t length)
: m_buffer(buffer)
, m_length(length)
, m_bytesPerLine(DEFAULT_BYTES_PER_LINE)
{}

HexPrinter::HexPrinter(char const* const buffer, size_t length, size_t bytesPerLine)
: m_buffer(buffer)
, m_length(length)
, m_bytesPerLine(bytesPerLine)
{}

HexPrinter::~HexPrinter()
{}

std::ostream& operator<<(std::ostream& os, HexPrinter const& printer)
{
    printHexBuffer(os, reinterpret_cast<unsigned char const* const>(printer.m_buffer), printer.m_length, printer.m_bytesPerLine);
    return os;
}

InlineHexPrinter::InlineHexPrinter(char const* const buffer, size_t length)
: m_buffer(buffer)
, m_length(length)
{}

InlineHexPrinter::~InlineHexPrinter()
{}

std::ostream& operator<<(std::ostream& os, InlineHexPrinter const& printer)
{
    printInlineHexBuffer(os, reinterpret_cast<unsigned char const* const>(printer.m_buffer), printer.m_length);
    return os;
}

} // namespace

