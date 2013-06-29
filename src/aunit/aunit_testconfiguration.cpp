#include <aunit_testconfiguration.h>

namespace aegis {
namespace aunit {

TestConfiguration::TestConfiguration()
{}

TestConfiguration::~TestConfiguration()
{}

void TestConfiguration::addTestId(std::string const& testId)
{
    m_testIdList.push_back(testId);
}

std::vector<std::string> const& TestConfiguration::testIdList() const
{
    return m_testIdList;
}

} // namespace
} // namespace
