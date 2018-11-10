#ifndef INCLUDED_AGTC_COMPONENT_HANDLE_H
#define INCLUDED_AGTC_COMPONENT_HANDLE_H

#include <cstddef>

namespace agtc {

class BaseComponentHandle
{
protected:
    static size_t _typeId;
};

template<typename T>
class ComponentHandle : public BaseComponentHandle
{
public:
    static size_t typeId();

};

template<typename T>
size_t ComponentHandle<T>::typeId()
{
    static size_t type = _typeId++;
    return type;
}

} // namespace

#endif // INCLUDED
