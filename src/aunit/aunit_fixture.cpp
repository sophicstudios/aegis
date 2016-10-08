#include <aunit_fixture.h>
#include <iostream>

namespace aunit {

Fixture* Fixture::m_activeInstance = nullptr;
Reporter* s_activeReporter = nullptr;

Fixture::Fixture(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line)
: m_name(name),
  m_descFunc(func),
  m_fixtureFilename(filename),
  m_fixtureLine(line)
{
}

Fixture::~Fixture()
{
}

Fixture* Fixture::instance()
{
    return m_activeInstance;
}

bool Fixture::run(Reporter& reporter)
{
    m_hasError = false;
    s_activeReporter = &reporter;

    // set the active fixture
    m_activeInstance = this;

    reporter.setFixture(m_name);

    // call the describe func. This will (optionally) set
    // the before and after, then run all the tests
    m_descFunc();

    // unset the current fixture
    m_activeInstance = nullptr;
    s_activeReporter = nullptr;

    return !m_hasError;
}

void Fixture::doBeforeEach(std::function<void ()> const& func, std::string const& filename, int line)
{
    m_beforeEachFilename = filename;
    m_beforeEachLine = line;
    m_beforeEachFunc = func;
}

void Fixture::doAfterEach(std::function<void ()> const& func, std::string const& filename, int line)
{
    m_afterEachFilename = filename;
    m_afterEachLine = line;
    m_afterEachFunc = func;
}

void Fixture::doIt(std::string const& name, std::function<void ()> const& func, std::string const& filename, int line)
{
    try
    {
        if (m_beforeEachFunc)
        {
            m_beforeEachFunc();
        }

        func();

        if (m_afterEachFunc)
        {
            m_afterEachFunc();
        }

        s_activeReporter->addResult(name, true, filename, line);
    }
    catch (...)
    {
        s_activeReporter->addResult(name, false, filename, line);
        m_hasError = true;
    }
}

} // namespace
