#ifndef INCLUDED_AEGIS_AUNIT_REPORTER_H
#define INCLUDED_AEGIS_AUNIT_REPORTER_H

#include <aunit_testresult.h>
#include <vector>

namespace aegis {
namespace aunit {

class Reporter
{
public:
    Reporter();

    virtual ~Reporter();

    void addResult(TestResult const& result);

    void publishReport();

protected:
    virtual void onAddResult(TestResult const& result);

    virtual void generateAndPublishReport(
        std::vector<TestResult> const& successList,
        std::vector<TestResult> const& failureList) = 0;
    
private:
    std::vector<TestResult> m_successList;
    std::vector<TestResult> m_failureList;
};

} // namespace
} // namespace

#endif // INCLUDED
