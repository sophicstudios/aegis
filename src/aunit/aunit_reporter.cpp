#include <aunit_reporter.h>

namespace aunit {

Reporter::Reporter()
{}

Reporter::~Reporter()
{}

void Reporter::addResult(TestResult const& result)
{
    if (result.success()) {
        m_successList.push_back(result);
    }
    else {
        m_failureList.push_back(result);
    }

    onAddResult(result);
}

void Reporter::publishReport()
{
    generateAndPublishReport(m_successList, m_failureList);
}

void Reporter::onAddResult(TestResult const& result)
{}

} // namespace
