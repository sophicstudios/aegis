#include <aunit_testresult.h>
#include <iostream>

namespace aunit {

TestResult::TestResult()
{}
    
TestResult::TestResult(
    std::string const& name,
    std::string const& file,
    size_t line,
    std::string const& condition,
    bool success)
: m_name(name),
  m_file(file),
  m_line(line),
  m_condition(condition),
  m_success(success)
{}

TestResult::~TestResult()
{}

std::string const& TestResult::name() const
{
    return m_name;
}

std::string const& TestResult::file() const
{
    return m_file;
}

size_t TestResult::line() const
{
    return m_line;
}

std::string const& TestResult::condition() const
{
    return m_condition;
}

bool TestResult::success() const
{
    return m_success;
}

void TestResult::setName(std::string const& name)
{
    m_name = name;
}

void TestResult::setFile(std::string const& file)
{
    m_file = file;
}

void TestResult::setLine(size_t line)
{
    m_line = line;
}

void TestResult::setCondition(std::string const& condition)
{
    m_condition = condition;
}

void TestResult::setSuccess(bool success)
{
    m_success = success;
}

std::ostream& operator<<(std::ostream& os, TestResult const& result)
{
    os << "["
        << " name: " << result.name()
        << " file: " << result.file()
        << " line: " << result.line()
        << " condition: " << result.condition()
        << " success: " << (result.success() ? "TRUE" : "FALSE")
        << " ]";
        
    return os;
}

} // namespace
