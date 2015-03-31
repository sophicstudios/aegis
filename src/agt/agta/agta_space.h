#ifndef INCLUDED_AGTA_SPACE_H
#define INCLUDED_AGTA_SPACE_H

#include <string>
#include <cstdint>

namespace agta {

class Space
{
public:
    Space();

    ~Space();

    uint32_t createEntity(std::string const& name);

    bool deleteEntity(std::string const& name);

    bool deleteEntity(uint32_t entityId);

private:
    class Impl;
    Impl* m_impl;

};

} // namespace

#endif // INCLUDED
