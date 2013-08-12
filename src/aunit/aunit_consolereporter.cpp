#include <aunit_consolereporter.h>
#include <iostream>

namespace aunit {

namespace {

void printResult(std::ostream& os, TestResult const& result)
{
    os << "[ "
        << result.condition()
        << " ]\n\t" << result.file()
        << " (" << result.line() << ")";
}

} // namespace

class Config
{
public:
    Config();
    
    ~Config();
    
    bool shouldPrintIndividualSuccess;
    bool shouldPrintIndividualFailure;
    bool shouldReportIndividualSuccess;
    bool shouldReportIndividualFailure;
};

Config::Config()
: shouldPrintIndividualSuccess(false),
  shouldPrintIndividualFailure(true),
  shouldReportIndividualSuccess(false),
  shouldReportIndividualFailure(false)
{}

Config::~Config()
{}

ConsoleReporter::ConsoleReporter()
: m_config(new Config())
{}

ConsoleReporter::~ConsoleReporter()
{
    delete m_config;
}

void ConsoleReporter::setShouldPrintIndividualStatus(bool value)
{
    m_config->shouldPrintIndividualSuccess = value;
    m_config->shouldPrintIndividualFailure = value;
}

bool ConsoleReporter::shouldPrintIndividualStatus() const
{
    return m_config->shouldPrintIndividualSuccess && m_config->shouldPrintIndividualFailure;
}

void ConsoleReporter::setShouldPrintIndividualSuccess(bool value)
{
    m_config->shouldPrintIndividualSuccess = value;
}

bool ConsoleReporter::shouldPrintIndividualSuccess() const
{
    return m_config->shouldPrintIndividualSuccess;
}

void ConsoleReporter::setShouldPrintIndividualFailure(bool value)
{
    m_config->shouldPrintIndividualFailure = value;
}

bool ConsoleReporter::shouldPrintIndividualFailure() const
{
    return m_config->shouldPrintIndividualFailure;
}

void ConsoleReporter::setShouldReportIndividualStatus(bool value)
{
    m_config->shouldReportIndividualSuccess = value;
    m_config->shouldReportIndividualFailure = value;
}

bool ConsoleReporter::shouldReportIndividualStatus() const
{
    return m_config->shouldReportIndividualSuccess && m_config->shouldReportIndividualFailure;
}

void ConsoleReporter::setShouldReportIndividualSuccess(bool value)
{
    m_config->shouldReportIndividualSuccess = value;
}

bool ConsoleReporter::shouldReportIndividualSuccess() const
{
    return m_config->shouldReportIndividualSuccess;
}

void ConsoleReporter::setShouldReportIndividualFailure(bool value)
{
    m_config->shouldReportIndividualFailure = value;
}

bool ConsoleReporter::shouldReportIndividualFailure() const
{
    return m_config->shouldReportIndividualFailure;
}

void ConsoleReporter::onAddResult(TestResult const& result)
{
    if (result.success() && m_config->shouldPrintIndividualSuccess) {
        std::cout << "SUCCESS: ";
        printResult(std::cout, result);
        std::cout << std::endl;
    }

    if (!result.success() && m_config->shouldPrintIndividualFailure) {
        std::cout << "FAILURE: ";
        printResult(std::cout, result);
        std::cout << std::endl;
    }
}

void ConsoleReporter::generateAndPublishReport(
    std::vector<TestResult> const& successList,
    std::vector<TestResult> const& failureList)
{
    std::cout << std::endl;
    std::cout << "Test Result Summary\n";
    std::cout << "--------------------\n";

    std::cout << "SUCCEEDED: " << successList.size() << "\n";
    
    std::vector<TestResult>::const_iterator it, end;
    if (m_config->shouldReportIndividualSuccess) {
        for (it = successList.begin(), end = successList.end(); it != end; ++it) {
            std::cout << "  ";
            printResult(std::cout, *it);
            std::cout << std::endl;
        }
    }
    
    std::cout << "FAILED:    " << failureList.size() << "\n";

    if (m_config->shouldReportIndividualFailure) {
        for (it = failureList.begin(), end = failureList.end(); it != end; ++it) {
            std::cout << "  ";
            printResult(std::cout, *it);
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

} // namespace
