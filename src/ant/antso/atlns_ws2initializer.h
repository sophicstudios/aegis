#ifndef INCLUDE_ATLNS_WS2INITIALIZER_H
#define INCLUDE_ATLNS_WS2INITIALIZER_H

namespace aegis {
namespace atlns {

class Ws2Initializer
{
public:
    static Ws2Initializer& instance();

private:
    static Ws2Initializer& m_instance;
};

} // namespace
} // namespace

#endif // INCLUDE
