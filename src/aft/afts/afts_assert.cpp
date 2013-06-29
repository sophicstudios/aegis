#include <afts_assert.h>
#include <iostream>
#include <exception>
#include <cassert>

namespace aegis {
namespace afts {

void defaultAssertFunc(bool value, char const* msg, int line, char const* filename)
{
    assert(value);
}

AssertUtil::AssertFunc g_assertFunc = defaultAssertFunc;

void AssertUtil::assignAssertFunc(AssertFunc const& f)
{
    g_assertFunc = f;
}

void AssertUtil::assertFunc(bool value, char const* msg, int line, char const* filename)
{
    g_assertFunc(value, msg, line, filename);
}

} // namespace
} // namespace
