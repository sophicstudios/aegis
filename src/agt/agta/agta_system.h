#ifndef INCLUDED_AEGIS_AGTA_SYSTEM_H
#define INCLUDED_AEGIS_AGTA_SYSTEM_H

namespace agta {

class System
{
public:
    System();

    virtual ~System() = 0;

    virtual void update() = 0;
};

} // namespace

#endif // INCLUDED
