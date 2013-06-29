#ifndef INCLUDE_ATLS_IPV4ADDRESS_H
#define INCLUDE_ATLS_IPV4ADDRESS_H

#include <string>
#include <netinet/in.h>

namespace aegis {
namespace atls {

class Ipv4Address
{
public:
    enum Predefined {
        Predefined_ANY,
        Predefined_LOOPBACK,
    };

    Ipv4Address(Predefined predefined, unsigned short port);

    Ipv4Address(std::string const& address, unsigned short port);

    struct sockaddr const* const sockaddr() const;

private:
    sockaddr_in m_sockaddr;
};

} // namespace
} // namespace

#endif // INCLUDE
