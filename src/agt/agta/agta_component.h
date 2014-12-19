#ifndef INCLUDED_AGTA_COMPONENT_H
#define INCLUDED_AGTA_COMPONENT_H

namespace agta {

class Component
{
public:
    Component();

    virtual ~Component() = 0;

    virtual void update() = 0;
};

} // namespace

#endif // INCLUDED
