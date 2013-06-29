#include <aunit.h>
#include <aftu_url.h>
#include <iostream>

namespace aegis {
namespace aftu {

class A
{
public:
    A();
    ~A();
    
private:
    int m_i;
};

A::A()
{
    std::cout << "A:A()" << std::endl;
    m_i = 5;
}

A::~A()
{
}

class TestUrl : public aunit::TestFixture
{
public:
    TestUrl() {}
    
    virtual ~TestUrl() {}
    
protected:
    virtual void runTest();

private:
    void testConstruction();
};

AUNIT_REGISTERTEST(TestUrl);

void TestUrl::runTest()
{
    testConstruction();
}

void TestUrl::testConstruction()
{
    A a;
    
    Url emptyUrl;
    AUNIT_ASSERT(!emptyUrl.isValid());
    
    Url httpUrl1("http://www.google.com");
    AUNIT_ASSERT(httpUrl1.isValid());
    AUNIT_ASSERT(httpUrl1.scheme() == "http");
    
    Url httpUrl2("http://www.google.com/");
    Url httpUrl3("http://www.google.com/search");
    Url httpUrl4("http://www.google.com/search/");
    Url httpUrl5("http://www.google.com/search?term=test");
    Url httpUrl6("http://www.google.com/search?term=test#ref");
}

} // namespace
} // namespace
