#include <actp_threadattributes.h>

namespace actp {

ThreadAttributes::ThreadAttributes(CreateType ct, size_t ss)
: createType(ct), stackSize(ss)
{}

} // namespace
