#ifndef INCLUDE_ATLNS_IPV4ADDRESS_H
#define INCLUDE_ATLNS_IPV4ADDRESS_H

#include <afls_os.h>

#if defined(AFLS_OS_POSIX)
#include <atlns_posixipv4address.h>
#elif defined(AFLS_OS_WINDOWS)
#include <atlns_ws2ipv4address.h>
#endif

namespace aegis {
namespace atlns {

#if defined(AFLS_OS_POSIX)
typedef PosixIpv4Address Ipv4AddressImpl;
#elif defined(AFLS_OS_WINDOWS)
typedef Ws2Ipv4Address Ipv4AddressImpl;
#endif

class Ipv4Address
{
public:
    enum Predefined {
        Predefined_ANY = Ipv4AddressImpl::Predefined_ANY,
        Predefined_LOOPBACK = Ipv4AddressImpl::Predefined_LOOPBACK,
    };

    Ipv4Address(Predefined predefined, unsigned short port);

    Ipv4Address(std::string const& address, unsigned short port);

    struct sockaddr const* const sockaddr() const;

private:
    Ipv4AddressImpl m_impl;
};

} // namespace
} // namespace

#endif // INCLUDE
