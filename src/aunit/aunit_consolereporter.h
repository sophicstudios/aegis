#ifndef INCLUDED_AEGIS_AUNIT_CONSOLEREPORTER_H
#define INCLUDED_AEGIS_AUNIT_CONSOLEREPORTER_H

#include <aunit_reporter.h>
#include <aunit_testresult.h>
#include <memory>
#include <vector>

namespace aegis {
namespace aunit {

class Config;

class ConsoleReporter
    : public aunit::Reporter
{
public:
    ConsoleReporter();

    virtual ~ConsoleReporter();

    void setShouldPrintIndividualStatus(bool value);
    
    bool shouldPrintIndividualStatus() const;
    
    void setShouldPrintIndividualSuccess(bool value);

    bool shouldPrintIndividualSuccess() const;
    
    void setShouldPrintIndividualFailure(bool value);

    bool shouldPrintIndividualFailure() const;

    void setShouldReportIndividualStatus(bool value);
    
    bool shouldReportIndividualStatus() const;
    
    void setShouldReportIndividualSuccess(bool value);
    
    bool shouldReportIndividualSuccess() const;
    
    void setShouldReportIndividualFailure(bool value);
    
    bool shouldReportIndividualFailure() const;
    
protected:
    virtual void onAddResult(TestResult const& result);

    virtual void generateAndPublishReport(
        std::vector<TestResult> const& successList,
        std::vector<TestResult> const& failureList);

private:
    Config* m_config;
};

} // namespace
} // namespace

#endif // INCLUDED
