#ifndef INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H
#define INCLUDE_AEGIS_ACTP_THREADATTRIBUTES_H

#include <cstdlib>

namespace actp {

class ThreadAttributes
{
public:
    enum CreateType {
        CreateType_DETACHED,
        CreateType_JOINABLE
    };

    ThreadAttributes();

    ~ThreadAttributes();

    void createType(CreateType value);

    CreateType createType() const;

    void stackSize(size_t value);

    size_t stackSize() const;

private:
    CreateType m_createType;
    size_t m_stackSize;
};

} // namespace

#endif // INCLUDE
