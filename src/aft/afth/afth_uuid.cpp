#include <afth_uuid.h>
#include <limits>
#include <iomanip>
#include <sstream>
#include <random>
//#include <arpa/inet.h>

namespace afth {


UUID UUID::v4()
{
    std::random_device rd;

    uint64_t rangeBegin = 1;
    uint64_t rangeEnd = std::numeric_limits<uint64_t>::max();

    std::uniform_int_distribution<uint64_t> dist(rangeBegin, rangeEnd);

    struct {
        uint64_t a;
        uint64_t b;
    } uuid;

    uuid.a = dist(rd);
    uuid.b = dist(rd);

    uuid.a = (uuid.a & 0xffffffffffff0fffULL) | 0x0000000000004000ULL;
    uuid.b = (uuid.b & 0x3fffffffffffffffULL) | 0x8000000000000000ULL;

    return UUID(uuid.a, uuid.b);
}

UUID::UUID()
{
    m_uuid.a = 0ULL;
    m_uuid.b = 0ULL;
}

UUID::UUID(uint64_t a, uint64_t b)
: m_uuid{a, b}
{}

UUID::~UUID()
{}

std::string UUID::str() const
{
    uint32_t a1 = (m_uuid.a >> 32);
    uint32_t a2 = (m_uuid.a & 0xffffffff);
    uint32_t b1 = (m_uuid.b >> 32);
    uint32_t b2 = (m_uuid.b & 0xffffffff);

    std::stringstream s;
    s << std::hex << std::nouppercase << std::setfill('0');

    s << std::setw(8) << a1                 << "-"
        << std::setw(4) << (a2 >> 16)       << "-"
        << std::setw(4) << (a2 & 0xffff)    << "-"
        << std::setw(4) << (b1 >> 16)       << "-"
        << std::setw(4) << (b1 & 0xffff)
        << std::setw(8) << (b2);

    return s.str();
}

std::vector<char> UUID::bytes() const
{
    std::vector<char> result(16, '\0');
    size_t i = 0;

    for (int j = 7; j >= 0; --j, ++i)
    {
        result[i] = 0xff & (m_uuid.a >> (j * 8));
    }

    for (int j = 7; j >= 0; --j, ++i)
    {
        result[i] = 0xff & (m_uuid.b >> (j * 8));
    }

    return result;
}

bool operator==(UUID const& lhs, UUID const& rhs)
{
    return lhs.m_uuid.a == rhs.m_uuid.a &&
        lhs.m_uuid.b == rhs.m_uuid.b;
}

bool operator!=(UUID const& lhs, UUID const& rhs)
{
    return lhs.m_uuid.a != rhs.m_uuid.a ||
        lhs.m_uuid.b != rhs.m_uuid.b;
}

bool operator<(UUID const& lhs, UUID const& rhs)
{
    return lhs.m_uuid.a < rhs.m_uuid.a ? true :
        lhs.m_uuid.a > rhs.m_uuid.a ? false :
        lhs.m_uuid.b < rhs.m_uuid.b;
}

bool operator<=(UUID const& lhs, UUID const& rhs)
{
    return !(lhs > rhs);
}

bool operator>(UUID const& lhs, UUID const& rhs)
{
    return lhs.m_uuid.a > rhs.m_uuid.a ? true :
        lhs.m_uuid.a < rhs.m_uuid.a ? false :
        lhs.m_uuid.b > rhs.m_uuid.b;
}

bool operator>=(UUID const& lhs, UUID const& rhs)
{
    return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, UUID const& uuid)
{
    os << uuid.str();
    return os;
}

} // namespace
