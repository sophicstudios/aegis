#ifndef INCLUDE_ATLNS_TCPENDPOINT_H
#define INCLUDE_ATLNS_TCPENDPOINT_H

#include <atls_socket.h>

namespace aegis {
namespace atlns {

class TcpEndpoint
{
public:
    TcpEndpoint();

    ~TcpEndpoint();
    
    Socket::Error read(char* buffer, size_t size, size_t* readSize);

    Socket::Error write(char const* const buffer, size_t size, size_t* writeSize);

private:
    Socket::Handle m_sock;
};

} // namespace
} // namespace

#endif // INCLUDE
