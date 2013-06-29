#include <aftu_url.h>

namespace aegis {
namespace aftu {

namespace {

// URI Characters
//   pct-encoded   = "%" HEXDIG HEXDIG
//   unreserved    = ALPHA / DIGIT / "-" / "." / "_" / "~"
//   reserved      = gen-delims / sub-delims
//   gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
//   sub-delims    = "!" / "$" / "&" / "'" / "(" / ")"
//                    / "*" / "+" / "," / ";" / "="
//
// URI Components
//   scheme        = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
//   authority     = [ userinfo "@" ] host [ ":" port ]
//   userinfo      = *( unreserved / pct-encoded / sub-delims / ":" )
//   host          = IP-literal / IPv4address / reg-name
//   IP-literal    = "[" ( IPv6address / IPvFuture  ) "]"
//   IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
//   IPv6address   =                              6( h16 ":" ) ls32
//                   /                       "::" 5( h16 ":" ) ls32
//                   / [               h16 ] "::" 4( h16 ":" ) ls32
//                   / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
//                   / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
//                   / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
//                   / [ *4( h16 ":" ) h16 ] "::"              ls32
//                   / [ *5( h16 ":" ) h16 ] "::"              h16
//                   / [ *6( h16 ":" ) h16 ] "::"
//   ls32          = ( h16 ":" h16 ) / IPv4address
//                   ; least-significant 32 bits of address                  
//   h16           = 1*4HEXDIG
//                   ; 16 bits of address represented in hexadecimal
//   IPv4address   = dec-octet "." dec-octet "." dec-octet "." dec-octet
//   dec-octet     = DIGIT                 ; 0-9
//                   / %x31-39 DIGIT       ; 10-99
//                   / "1" 2DIGIT          ; 100-199
//                   / "2" %x30-34 DIGIT   ; 200-249
//                   / "25" %x30-35        ; 250-255
//   reg-name      = *( unreserved / pct-encoded / sub-delims )
//   port          = *DIGIT
//   path          = path-abempty    ; begins with "/" or is empty
//                   / path-absolute   ; begins with "/" but not "//"
//                   / path-noscheme   ; begins with a non-colon segment
//                   / path-rootless   ; begins with a segment
//                   / path-empty      ; zero characters
//   path-abempty  = *( "/" segment )
//   path-absolute = "/" [ segment-nz *( "/" segment ) ]
//   path-noscheme = segment-nz-nc *( "/" segment )
//   path-rootless = segment-nz *( "/" segment )
//   path-empty    = 0<pchar>
//   segment       = *pchar
//   segment-nz    = 1*pchar
//   segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
//                   ; non-zero-length segment without any colon ":"
//   pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"
//   query         = *( pchar / "/" / "?" )
//   fragment      = *( pchar / "/" / "?" )

enum CharType {
    CharType_UNRESERVED = 1,
    CharType_RESERVED = 2,
    CharType_GENDELIM = 4,
    CharType_SUBDELIM = 8,
    CharType_SCHEME = 16,
    CharType_PATH = 32,
    CharType_QUERY = 64,
    CharType_FRAGMENT = 128,
    CharType_
};
    
uint16_t CharacterTypes[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00 - 0x0F
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x10 - 0x1F
0,                                              // 0x20 (space)
CharType_RESERVED | CharType_SUBDELIM,          // 0x21 !
0,                                              // 0x22 "
CharType_RESERVED | CharType_GENDELIM,          // 0x23 #
CharType_RESERVED | CharType_SUBDELIM,          // 0x24 $
0,                                              // 0x25 %
CharType_RESERVED | CharType_SUBDELIM,          // 0x26 &
CharType_RESERVED | CharType_SUBDELIM,          // 0x27 '
CharType_RESERVED | CharType_SUBDELIM,          // 0x28 (
CharType_RESERVED | CharType_SUBDELIM,          // 0x29 )
CharType_RESERVED | CharType_SUBDELIM,          // 0x2A *
CharType_RESERVED | CharType_SUBDELIM | CharType_SCHEME,          // 0x2B +
CharType_RESERVED | CharType_SUBDELIM,          // 0x2C ,
CharType_UNRESERVED | CharType_SCHEME, // 0x2D -
CharType_UNRESERVED | CharType_SCHEME, // 0x2E .
CharType_RESERVED | CharType_GENDELIM, // 0x2F /
CharType_UNRESERVED | CharType_SCHEME, // 0x30 0
CharType_UNRESERVED | CharType_SCHEME, // 0x31 1
CharType_UNRESERVED | CharType_SCHEME, // 0x32 2
CharType_UNRESERVED | CharType_SCHEME, // 0x33 3
CharType_UNRESERVED | CharType_SCHEME, // 0x34 4
CharType_UNRESERVED | CharType_SCHEME, // 0x35 5
CharType_UNRESERVED | CharType_SCHEME, // 0x36 6
CharType_UNRESERVED | CharType_SCHEME, // 0x37 7
CharType_UNRESERVED | CharType_SCHEME, // 0x38 8
CharType_UNRESERVED | CharType_SCHEME, // 0x39 9
0, // 0x3A :
0, // 0x3B ;
0, // 0x3C <
0, // 0x3D =
0, // 0x3E >
0, // 0x3F ?
0, // 0x40 @
CharType_UNRESERVED | CharType_SCHEME, // 0x41 A
CharType_UNRESERVED | CharType_SCHEME, // 0x42 B
CharType_UNRESERVED | CharType_SCHEME, // 0x43 C
CharType_UNRESERVED | CharType_SCHEME, // 0x44 D
CharType_UNRESERVED | CharType_SCHEME, // 0x45 E
CharType_UNRESERVED | CharType_SCHEME, // 0x46 F
CharType_UNRESERVED | CharType_SCHEME, // 0x47 G
CharType_UNRESERVED | CharType_SCHEME, // 0x48 H
CharType_UNRESERVED | CharType_SCHEME, // 0x49 I
CharType_UNRESERVED | CharType_SCHEME, // 0x4A J
CharType_UNRESERVED | CharType_SCHEME, // 0x4B K
CharType_UNRESERVED | CharType_SCHEME, // 0x4C L
CharType_UNRESERVED | CharType_SCHEME, // 0x4D M
CharType_UNRESERVED | CharType_SCHEME, // 0x4E N
CharType_UNRESERVED | CharType_SCHEME, // 0x4F O
CharType_UNRESERVED | CharType_SCHEME, // 0x50 P
CharType_UNRESERVED | CharType_SCHEME, // 0x51 Q
CharType_UNRESERVED | CharType_SCHEME, // 0x52 R
CharType_UNRESERVED | CharType_SCHEME, // 0x53 S
CharType_UNRESERVED | CharType_SCHEME, // 0x54 T
CharType_UNRESERVED | CharType_SCHEME, // 0x55 U
CharType_UNRESERVED | CharType_SCHEME, // 0x56 V
CharType_UNRESERVED | CharType_SCHEME, // 0x57 W
CharType_UNRESERVED | CharType_SCHEME, // 0x58 X
CharType_UNRESERVED | CharType_SCHEME, // 0x59 Y
CharType_UNRESERVED | CharType_SCHEME, // 0x5A Z
0, // 0x5B [
0, // 0x5C '\'
0, // 0x5D ]
0, // 0x5E ^
0, // 0x5F _
0, // 0x60 `
CharType_UNRESERVED | CharType_SCHEME, // 0x61 a
CharType_UNRESERVED | CharType_SCHEME, // 0x62 b
CharType_UNRESERVED | CharType_SCHEME, // 0x63 c
CharType_UNRESERVED | CharType_SCHEME, // 0x64 d
CharType_UNRESERVED | CharType_SCHEME, // 0x65 e
CharType_UNRESERVED | CharType_SCHEME, // 0x66 f
CharType_UNRESERVED | CharType_SCHEME, // 0x67 g
CharType_UNRESERVED | CharType_SCHEME, // 0x68 h
CharType_UNRESERVED | CharType_SCHEME, // 0x69 i
CharType_UNRESERVED | CharType_SCHEME, // 0x6A j
CharType_UNRESERVED | CharType_SCHEME, // 0x6B k
CharType_UNRESERVED | CharType_SCHEME, // 0x6C l
CharType_UNRESERVED | CharType_SCHEME, // 0x6D m
CharType_UNRESERVED | CharType_SCHEME, // 0x6E n
CharType_UNRESERVED | CharType_SCHEME, // 0x6F o
CharType_UNRESERVED | CharType_SCHEME, // 0x70 p
CharType_UNRESERVED | CharType_SCHEME, // 0x71 q
CharType_UNRESERVED | CharType_SCHEME, // 0x72 r
CharType_UNRESERVED | CharType_SCHEME, // 0x73 s
CharType_UNRESERVED | CharType_SCHEME, // 0x74 t
CharType_UNRESERVED | CharType_SCHEME, // 0x75 u
CharType_UNRESERVED | CharType_SCHEME, // 0x76 v
CharType_UNRESERVED | CharType_SCHEME, // 0x77 w
CharType_UNRESERVED | CharType_SCHEME, // 0x78 x
CharType_UNRESERVED | CharType_SCHEME, // 0x79 y
CharType_UNRESERVED | CharType_SCHEME, // 0x7A z
0, // 0x7B {
0, // 0x7C |
0, // 0x7D }
0, // 0x7E ~
0, // 0x7F DEL
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x80 - 0x8F
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x90 - 0x9F
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xA0 - 0xAF
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xB0 - 0xBF
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xC0 - 0xCF
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xD0 - 0xDF
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xE0 - 0xEF
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0xF0 - 0xFF
};

// a URI is made of up several components, which all follow this
// general rule, prior to scheme-specific components:
// URI = scheme ':' hier-part [ '?' query ] [ '#' fragment ]
// hier-part = "//" authority path-abempty
struct Components
{
    aftu::StringRef<std::string> scheme;
    aftu::StringRef<std::string> authority;
    aftu::StringRef<std::string> path;
    aftu::StringRef<std::string> query;
    aftu::StringRef<std::string> fragment;
};

bool isCharOfType(uint16_t mask, char c)
{
    uint16_t type = CharacterTypes[static_cast<size_t>(c)];
    return type & mask;
}

// the parse routine takes an input string that supposedly holds a URL,
// transforms the URL into its canonical form and at the same time
// splits the canonical URL into its components. If for any reason,
// the URL is unable to be parsed, the routine returns false
bool parseScheme(
    std::string* canonical,
    Components* components,
    char const* begin,
    char const* end)
{
    // assumes the input is a valid scheme, terminating in a ':' character
    // walks through the characters until it hits the terminator,
    // creates a canonical version of it and assigns the component.
    while (begin != end && *begin != ':') {
        if (isCharOfType(CharType_SCHEME, *begin)) {
            canonical->push_back(tolower(*begin));
        }
        else {
            return false;
        }

        ++begin;
    }
    
    if (*begin == ':') {
        components->scheme.assign(*canonical, 0, canonical->size());
        ++begin; // move to the next spot after the ':'
        return true;
    }
    
    return false;
}

bool parseAuthority(
    std::string* canonical,
    Components* components,
    char const* begin,
    char const* end)
{
    
    return true;
}

bool parse(
    std::string* canonical,
    Components* components,
    char const* begin,
    char const* end)
{
    if (!parseScheme(canonical, components, begin, end)) {
        return false;
    }
    
    if (!parseAuthority(canonical, components, begin, end)) {
        return false;
    }
    
    return true;
}

} // namespace

class Url::Impl
{
public:
    Impl() {}
    
    ~Impl() {}
    
    std::string canonical;
    Components components;
};

Url::Url()
: m_impl(new Impl())
{
}

Url::Url(std::string const& urlString)
: m_impl(new Impl())
{
    parse(
        &m_impl->canonical,
        &m_impl->components,
        &urlString[0],
        &urlString[urlString.size()]);
}

Url::Url(Url const& url)
: m_impl(new Impl(*(url.m_impl)))
{
}

Url::~Url()
{
    delete m_impl;
}

Url& Url::operator=(Url const& url)
{
    Impl* temp = new Impl(*(url.m_impl));
    delete m_impl;
    m_impl = temp;
    return *this;
}

bool Url::isValid()
{
    return !m_impl->canonical.empty();
}

std::string Url::scheme() const
{
    return m_impl->components.scheme.str();
}

bool Url::hasAuthority() const
{
    return !m_impl->components.authority.isEmpty();
}

std::string Url::authority() const
{
    return m_impl->components.authority.str();
}

bool Url::hasPath() const
{
    return !m_impl->components.path.isEmpty();
}

std::string Url::path() const
{
    return m_impl->components.path.str();
}

bool Url::hasQuery() const
{
    return !m_impl->components.query.isEmpty();
}

std::string Url::query() const
{
    return m_impl->components.query.str();
}

bool Url::hasFragment() const
{
    return !m_impl->components.fragment.isEmpty();
}

std::string Url::fragment() const
{
    return m_impl->components.fragment.str();
}

} // namespace
} // namespace
