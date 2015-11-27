#ifndef INCLUDED_AEGIS_AUNIT_CONSOLEREPORTER_H
#define INCLUDED_AEGIS_AUNIT_CONSOLEREPORTER_H

#include <aunit_reporter.h>
#include <aunit_testresult.h>
#include <memory>
#include <vector>

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
    virtual void onSetFixture(std::string const& name);

    virtual void onAddResult(std::string const& name, bool success, std::string const& filename, int line);

    virtual void onAddResult(TestResult const& result);

private:
    Config* m_config;
};

} // namespace

#endif // INCLUDED
