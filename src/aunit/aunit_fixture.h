#ifndef INCLUDED_AUNIT_FIXTURE_H
#define INCLUDED_AUNIT_FIXTURE_H

#include <aunit_reporter.h>
#include <functional>
#include <string>

namespace aunit {

class Fixture
{
public:
    static Fixture* instance();

    Fixture(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line);

    ~Fixture();

    bool run(Reporter& reporter);

    void doBeforeEach(std::function<void ()> const& func, std::string const& filename, int line);

    void doAfterEach(std::function<void ()> const& func, std::string const& filename, int line);

    void doIt(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line);

private:
    typedef std::pair<std::string, std::function<void ()> > Test;

    static Fixture* m_activeInstance;

    bool m_hasError;
    std::string m_name;
    std::string m_fixtureFilename;
    std::string m_beforeEachFilename;
    int m_beforeEachLine;
    std::string m_afterEachFilename;
    int m_afterEachLine;
    std::function<void ()> m_descFunc;
    std::function<void ()> m_afterEachFunc;
    std::function<void ()> m_beforeEachFunc;
};

} // namespace

#endif // INCLUDED
