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

void ConsoleReporter::onSetFixture(std::string const& name)
{
    std::cout << name << std::endl;
}

void ConsoleReporter::onAddResult(std::string const& name, bool success, std::string const& filename, int line)
{
    std::cout << "  " << name;
    if (success) {
        std::cout << " -- SUCCESS" << std::endl;
    }
    else {
        std::cout << " -- FAIL (" << filename << ":" << line << ")" << std::endl;
    }
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

} // namespace
