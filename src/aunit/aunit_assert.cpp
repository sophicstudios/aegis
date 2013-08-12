#include <aunit_assert.h>
#include <aunit_reporter.h>
#include <aunit_testresult.h>

namespace aunit {

void AssertImpl::doAssert(
    Reporter& reporter,
    bool value,
    char const* const test,
    size_t line,
    char const* const file)
{
    TestResult result(file, file, line, test, value);
    reporter.addResult(result);
}

} // namespace
