#include <aunit_testregistry.h>
#include <aunit_testfixture.h>

namespace aegis {
namespace aunit {

TestRegistry* TestRegistry::m_instance = NULL;

TestRegistry& TestRegistry::instance()
{
    if (!TestRegistry::m_instance) {
        TestRegistry::m_instance = new TestRegistry();
    }
    
    return *TestRegistry::m_instance;
}

TestRegistry::TestRegistry()
{}

TestRegistry::~TestRegistry()
{}

bool TestRegistry::registerTest(std::string const& testId, FactoryFunc const& factoryFunc)
{
    // check if the test case id already exists. If so, return an error, otherwise
    // add the test case factory to the list and map the name to the factory.
    if (m_factoryFuncListIteratorMap.find(testId) != m_factoryFuncListIteratorMap.end()) {
        return false;
    }

    FactoryFuncList::iterator it = m_factoryFuncList.insert(m_factoryFuncList.end(), factoryFunc);
    m_factoryFuncListIteratorMap.insert(std::make_pair(testId, it));

    return true;
}

TestRegistry::const_iterator TestRegistry::find(std::string const& testId) const
{
    TestRegistry::const_iterator result = m_factoryFuncList.end();
    
    FactoryFuncListIteratorMap::const_iterator it = m_factoryFuncListIteratorMap.find(testId);
    if (it != m_factoryFuncListIteratorMap.end()) {
        result = it->second;
    }
    
    return result;
}

TestRegistry::const_iterator TestRegistry::begin() const
{
    return m_factoryFuncList.begin();
}

TestRegistry::const_iterator TestRegistry::end() const
{
    return m_factoryFuncList.end();
}

} // namespace
} // namespace
