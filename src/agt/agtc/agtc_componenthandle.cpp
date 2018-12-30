#include <agtc_componenthandle.h>

namespace agtc {
    size_t BaseComponentHandle::_typeId = 0;

    size_t BaseComponentHandle::nextTypeId() {
        size_t result = BaseComponentHandle::_typeId++;
        return result;
    }
}