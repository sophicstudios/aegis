#ifndef INCLUDED_AEGIS_AUNIT_TESTREGISTRY_H
#define INCLUDED_AEGIS_AUNIT_TESTREGISTRY_H

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>

/**
 * Macro for easily registering a TestFixture with a singleton TestRegistry.
 * @param TestType the test class type.
 */
#define AUNIT_REGISTERTEST(TestFixtureType) \
    aunit::RegisterTest<TestFixtureType > register_##TestFixtureType( \
        aunit::TestRegistry::instance(), \
        #TestFixtureType, \
        aunit::TestRegistry::FactoryFunc(\
            aunit::TestFixtureFactory<TestFixtureType >::create))

#define AUNIT_REGISTERTESTID(TestFixtureType, id) \
    aunit::RegisterTest<TestFixtureType > register_##id( \
        aunit::TestRegistry::instance(), \
        #id, \
        aunit::TestRegistry::FactoryFunc(\
            aunit::TestFixtureFactory<TestFixtureType >::create))

namespace aunit {

class TestFixture;

///
/// TestRegistry represents a collection of TestFixture factory
/// functions. In the common use case, a TestFixture will be registered
/// in the TestRegistry for later creation by a TestManager that
/// is created in the driver for a unit test. A TestFixture is keyed
/// by a string representing the "name" of the TestFixture. This allows
/// a TestFixture to be looked up and created dynamically at runtime depending
/// on the needs of the unit test driver. The TestRegistry also provides
/// iterators that allow the user to access each registered TestFixture
/// in the order they were added to the registry. This is useful when you wish
/// to just create and run all the TestFixtures in a loop.
///
class TestRegistry
{
public:
    typedef boost::shared_ptr<aunit::TestFixture> TestFixturePtr;
    typedef boost::function<TestFixturePtr (void)> FactoryFunc;
    typedef std::vector<FactoryFunc> FactoryFuncList;
    typedef FactoryFuncList::const_iterator const_iterator;
    
    static TestRegistry& instance();

    ~TestRegistry();

    /**
     * Registers the test creation factory, identified by the string
     * 'testId'. If the test already exists with the specified testId, returns
     * false, otherwise returns true.
     * \param testId The string that identifies the test
     * \param testFactory The factory object to create the test
     * \result true on success, false if the testId already exists.
     */
    bool registerTest(std::string const& testId, FactoryFunc const& factoryFunc);
    
    const_iterator find(std::string const& testId) const;

    const_iterator begin() const;
    
    const_iterator end() const;
    
private:
    TestRegistry();
    TestRegistry(TestRegistry const&);
    TestRegistry& operator=(TestRegistry const&);
    
    static TestRegistry* m_instance;

    FactoryFuncList m_factoryFuncList;

    typedef std::map<std::string, FactoryFuncList::iterator> FactoryFuncListIteratorMap;
    FactoryFuncListIteratorMap m_factoryFuncListIteratorMap;
};

/**
 * Helper struct to serve as a default factory func for creating a
 * TestFixture object
 */
template<typename T>
struct TestFixtureFactory
{
    static boost::shared_ptr<TestFixture> create();
};

template<typename T>
boost::shared_ptr<TestFixture> TestFixtureFactory<T>::create()
{
    return boost::shared_ptr<TestFixture>(new T());
}

/**
 * Helper class to that adds a TestFixture to a TestRegistry. Instantiating an instance
 * of this class can be done at file scope, which will register the test class before main()
 * runs.
 */
template<typename T>
class RegisterTest
{
public:
    RegisterTest(
        TestRegistry& testRegistry,
        std::string const& name,
        TestRegistry::FactoryFunc const& factoryFunc);

    ~RegisterTest();
};

template<typename T>
RegisterTest<T>::RegisterTest(
    TestRegistry& testRegistry,
    std::string const& name,
    TestRegistry::FactoryFunc const& factoryFunc)
{
    if (!testRegistry.registerTest(name, factoryFunc)) {
        throw std::exception();
    }
}

template<typename T>
RegisterTest<T>::~RegisterTest()
{}

} // namespace

#endif // INCLUDED
