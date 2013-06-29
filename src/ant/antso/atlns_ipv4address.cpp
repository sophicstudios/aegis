#include <atlns_ipv4address.h>
#include <arpa/inet.h>

namespace aegis {
namespace atls {

namespace {

in_addr_t translatePredefined(Ipv4Address::Predefined predefined)
{
    switch (predefined)
    {
    case Ipv4Address::Predefined_LOOPBACK:
        return static_cast<in_addr_t>(INADDR_LOOPBACK); // 127.0.0.1
        break;
    case Ipv4Address::Predefined_ANY:
        return static_cast<in_addr_t>(INADDR_ANY); // 0.0.0.0
        break;
    default:
        return static_cast<in_addr_t>(INADDR_ANY);
        break;
    }
}

} // namespace

Ipv4Address::Ipv4Address(Predefined predefined, unsigned short port)
{
    memset(&m_sockaddr, 0, sizeof(sockaddr_in));

    m_sockaddr.sin_family = AF_INET;
    m_sockaddr.sin_port = htons(port);
    m_sockaddr.sin_addr.s_addr = htonl(translatePredefined(predefined));
}

Ipv4Address::Ipv4Address(std::string const& address, unsigned short port)
{
    memset(&m_sockaddr, 0, sizeof(sockaddr_in));

    m_sockaddr.sin_family = AF_INET;
    m_sockaddr.sin_port = htons(port);

    int result = inet_pton(AF_INET, address.c_str(), &m_sockaddr.sin_addr.s_addr);
    if (result != 1)
    {
        // need to resolve the address
    }
}

struct sockaddr const* const Ipv4Address::sockaddr() const
{
    return reinterpret_cast<struct sockaddr const*>(&m_sockaddr);
}

} // namespace
} // namespace
