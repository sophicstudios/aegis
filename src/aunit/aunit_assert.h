#ifndef INCLUDED_AEGIS_AUNIT_ASSERT_H
#define INCLUDED_AEGIS_AUNIT_ASSERT_H

#include <cstddef>

#define AUNIT_ASSERT(x) \
    aegis::aunit::AssertImpl::doAssert(reporter(), x, #x, __LINE__, __FILE__)

namespace aegis {
namespace aunit {

class Reporter;

struct AssertImpl
{
    static void doAssert(
        Reporter& reporter,
        bool statementResult,
        char const* const statement,
        size_t line,
        char const* const fileName);
};

} // namespace
} // namespace

#endif // INCLUDED
