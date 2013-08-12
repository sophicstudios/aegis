#ifndef INCLUDED_AEGIS_AUNIT_TESTCONFIGURATION_H
#define INCLUDED_AEGIS_AUNIT_TESTCONFIGURATION_H

#include <string>
#include <vector>

namespace aunit {

class TestConfiguration
{
public:
    TestConfiguration();

    ~TestConfiguration();

    void addTestId(std::string const& testId);
    
    std::vector<std::string> const& testIdList() const;

private:
    std::vector<std::string> m_testIdList;
};

} // namespace

#endif // INCLUDED
