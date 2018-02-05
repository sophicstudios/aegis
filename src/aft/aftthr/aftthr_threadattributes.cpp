#include <aftthr_threadattributes.h>

namespace aftthr {

ThreadAttributes::ThreadAttributes()
: m_createType(CreateType_JOINABLE),
  m_stackSize(0)
{
}

ThreadAttributes::~ThreadAttributes()
{
}

void ThreadAttributes::createType(ThreadAttributes::CreateType value)
{
    m_createType = value;
}

ThreadAttributes::CreateType ThreadAttributes::createType() const
{
    return m_createType;
}

void ThreadAttributes::stackSize(size_t value)
{
    m_stackSize = value;
}

size_t ThreadAttributes::stackSize() const
{
    return m_stackSize;
}

} // namespace
