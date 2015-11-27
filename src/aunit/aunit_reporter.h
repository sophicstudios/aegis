#ifndef INCLUDED_AEGIS_AUNIT_REPORTER_H
#define INCLUDED_AEGIS_AUNIT_REPORTER_H

#include <aunit_testresult.h>
#include <string>
#include <vector>

namespace aunit {

class Reporter
{
public:
    Reporter();

    virtual ~Reporter();

    void setFixture(std::string const& name);

    void addResult(TestResult const& result);

    void addResult(std::string const& name, bool success, std::string const& filename, int line);
    
protected:
    virtual void onSetFixture(std::string const& name);
    virtual void onAddResult(std::string const& name, bool success, std::string const& filename, int line);
};

} // namespace

#endif // INCLUDED
