#ifndef INCLUDED_AEGIS_AUNIT_TESTRESULT_H
#define INCLUDED_AEGIS_AUNIT_TESTRESULT_H

#include <iosfwd>
#include <string>

namespace aegis {
namespace aunit {

class TestResult
{
public:
    /// CONSTRUCTORS
    TestResult();
    
    TestResult(
        std::string const& name,
        std::string const& file,
        size_t line,
        std::string const& condition,
        bool success);

    /// DESTRUCTOR
    ~TestResult();

    /// ACCESSORS
    std::string const& name() const;
    std::string const& file() const;
    size_t line() const;
    std::string const& condition() const;
    bool success() const;

    /// MANIPULATORS
    void setName(std::string const& name);
    void setFile(std::string const& file);
    void setLine(size_t line);
    void setCondition(std::string const& condition);
    void setSuccess(bool success);

private:
    std::string m_name;
    std::string m_file;
    size_t m_line;
    std::string m_condition;
    bool m_success;
};

std::ostream& operator<<(std::ostream& os, TestResult const& result);

} // namespace
} // namespace

#endif // INCLUDED
